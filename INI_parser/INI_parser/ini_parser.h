#pragma once
#include <string>
#include <string_view>
#include <unordered_map>
#include <stdexcept>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cctype>
#include <optional>

namespace ini {

    // Exceptions
    struct ini_error : std::runtime_error {
        using std::runtime_error::runtime_error;
    };

    struct parse_error : ini_error {
        size_t line = 0;
        parse_error(size_t ln, const std::string& msg)
            : ini_error("INI parse error at line " + std::to_string(ln) + ": " + msg), line(ln) {}
    };

    struct key_error : ini_error {
        using ini_error::ini_error;
    };

    // Helpers
    inline bool is_space(char c) {
        return c == ' ' || c == '\t' || c == '\r' || c == '\n';
    }

    inline std::string ltrim(std::string_view sv) {
        size_t i = 0;
        while (i < sv.size() && is_space(sv[i])) ++i;
        return std::string(sv.substr(i));
    }

    inline std::string rtrim(std::string_view sv) {
        if (sv.empty()) return {};
        size_t j = sv.size();
        while (j > 0 && is_space(sv[j - 1])) --j;
        return std::string(sv.substr(0, j));
    }

    inline std::string trim(std::string_view sv) {
        return rtrim(ltrim(sv));
    }

    inline bool starts_with_comment_or_empty(std::string_view sv) {
        // пропустить начальные пробелы
        size_t i = 0;
        while (i < sv.size() && is_space(sv[i])) ++i;
        return (i == sv.size()) || sv[i] == ';';
    }

    // проста€ обрезка инлайн-комментари€: всЄ после первого ';'
    inline std::string strip_inline_comment(std::string_view sv) {
        size_t pos = sv.find(';');
        if (pos == std::string_view::npos) return std::string(sv);
        return std::string(sv.substr(0, pos));
    }

    inline std::vector<std::string> split_section_dot_key(const std::string& path) {
        // ищем последний '.'
        auto pos = path.rfind('.');
        if (pos == std::string::npos || pos == 0 || pos + 1 >= path.size())
            throw key_error("Use \"section.key\" format (got \"" + path + "\")");
        return { path.substr(0, pos), path.substr(pos + 1) };
    }

    inline std::string to_lower(std::string s) {
        std::transform(s.begin(), s.end(), s.begin(), [](unsigned char c) { return (char)std::tolower(c); });
        return s;
    }

    // перечислим доступные ключи секции
    inline std::string make_suggestion_message(const std::string& section,
        const std::unordered_map<std::string, std::string>& kv) {
        std::ostringstream oss;
        oss << "Available keys in section [" << section << "]: ";
        bool first = true;
        for (auto& p : kv) {
            if (!first) oss << ", ";
            oss << p.first;
            first = false;
        }
        return oss.str();
    }

    // Parser
    class ini_parser {
    public:
        using section_type = std::unordered_map<std::string, std::string>;
        using storage_type = std::unordered_map<std::string, section_type>;

        explicit ini_parser(const std::string& filename) {
            parse_file(filename);
        }

        // "section.key"
        template <class T>
        T get_value(const std::string& section_dot_key) const {
            auto parts = split_section_dot_key(section_dot_key);
            return get_value<T>(parts[0], parts[1]);
        }

        // секци€ + ключ
        template <class T>
        T get_value(const std::string& section, const std::string& key) const {
            auto s_it = data_.find(section);
            if (s_it == data_.end())
                throw key_error("Section [" + section + "] not found");

            auto& sec = s_it->second;
            auto k_it = sec.find(key);
            if (k_it == sec.end()) {
                std::string hint = make_suggestion_message(section, sec);
                throw key_error("Key \"" + key + "\" not found in section [" + section + "]. " + hint);
            }
            return convert<T>(k_it->second, section, key);
        }

        // опционально Ч проверить, есть ли ключ
        bool has(const std::string& section, const std::string& key) const {
            auto s_it = data_.find(section);
            if (s_it == data_.end()) return false;
            return s_it->second.count(key) != 0;
        }

    private:
        storage_type data_;

        void parse_file(const std::string& filename) {
            std::ifstream in(filename);
            if (!in)
                throw ini_error("Cannot open file: " + filename);

            std::string line;
            size_t lineno = 0;
            std::string current_section;

            while (std::getline(in, line)) {
                ++lineno;

                // убрать UTF-8 BOM в первой строке
                if (lineno == 1 && line.size() >= 3 &&
                    (unsigned char)line[0] == 0xEF && (unsigned char)line[1] == 0xBB && (unsigned char)line[2] == 0xBF) {
                    line.erase(0, 3);
                }

                std::string raw = trim(line);
                if (starts_with_comment_or_empty(raw)) continue;

                if (!raw.empty() && raw.front() == '[') {
                    // секци€
                    auto close = raw.find(']');
                    if (close == std::string::npos)
                        throw parse_error(lineno, "Missing closing ']' in section header");

                    // до '[' должны быть только пробелы Ч но мы уже trim сделали
                    // им€ секции Ч внутри скобок
                    std::string name = trim(std::string_view(raw).substr(1, close - 1));

                    // после ']' могут быть пробелы и/или комментарий
                    std::string after = trim(std::string_view(raw).substr(close + 1));
                    if (!after.empty() && after[0] != ';')
                        throw parse_error(lineno, "Unexpected characters after section header");

                    current_section = name;
                    (void)data_[current_section]; // создать секцию при первом упоминании
                    continue;
                }

                // присваивание key = value
                {
                    auto eq = raw.find('=');
                    if (eq == std::string::npos)
                        throw parse_error(lineno, "Expected assignment \"key = value\"");

                    if (current_section.empty())
                        throw parse_error(lineno, "Assignment outside of any section");

                    std::string key = trim(std::string_view(raw).substr(0, eq));
                    if (key.empty())
                        throw parse_error(lineno, "Empty key name");

                    std::string val_with_comment = raw.substr(eq + 1);
                    // допускаем произвольные пробелы вокруг '='
                    std::string value = trim(strip_inline_comment(std::string_view(val_with_comment)));
                    // пустое значение допустимо (пример: Mode=)


                    data_[current_section][key] = value;
                    continue;
                }
            }
        }

        // Conversions
        template <class T>
        static T convert(const std::string& s, const std::string& section, const std::string& key) {
            // ќбщий шаблон Ч дл€ неподдержанных типов
            static_assert(sizeof(T) == 0, "Unsupported type for ini_parser::get_value<T>");
            (void)s; (void)section; (void)key; // подавить warning
            return T{};
        }
    };

    // std::string
    template <>
    inline std::string ini_parser::convert<std::string>(const std::string& s,
        const std::string&, const std::string&) {
        return s;
    }

    // целые
    template <>
    inline int ini_parser::convert<int>(const std::string& s,
        const std::string& section, const std::string& key) {
        try {
            size_t idx = 0;
            int v = std::stoi(s, &idx, 10);
            if (idx != s.size()) throw std::invalid_argument("trailing");
            return v;
        }
        catch (...) {
            throw key_error("Cannot convert [" + section + "]." + key + "=\"" + s + "\" to int");
        }
    }

    template <>
    inline long long ini_parser::convert<long long>(const std::string& s,
        const std::string& section, const std::string& key) {
        try {
            size_t idx = 0;
            long long v = std::stoll(s, &idx, 10);
            if (idx != s.size()) throw std::invalid_argument("trailing");
            return v;
        }
        catch (...) {
            throw key_error("Cannot convert [" + section + "]." + key + "=\"" + s + "\" to long long");
        }
    }

    // вещественные
    template <>
    inline double ini_parser::convert<double>(const std::string& s,
        const std::string& section, const std::string& key) {
        try {
            size_t idx = 0;
            double v = std::stod(s, &idx);
            if (idx != s.size()) throw std::invalid_argument("trailing");
            return v;
        }
        catch (...) {
            throw key_error("Cannot convert [" + section + "]." + key + "=\"" + s + "\" to double");
        }
    }

    template <>
    inline float ini_parser::convert<float>(const std::string& s,
        const std::string& section, const std::string& key) {
        try {
            size_t idx = 0;
            float v = std::stof(s, &idx);
            if (idx != s.size()) throw std::invalid_argument("trailing");
            return v;
        }
        catch (...) {
            throw key_error("Cannot convert [" + section + "]." + key + "=\"" + s + "\" to float");
        }
    }

    // bool (true/false/yes/no/on/off/1/0 –егистр неважен)
    template <>
    inline bool ini_parser::convert<bool>(const std::string& s,
        const std::string& section, const std::string& key) {
        auto v = to_lower(s);
        if (v == "1" || v == "true" || v == "yes" || v == "on")  return true;
        if (v == "0" || v == "false" || v == "no" || v == "off") return false;
        throw key_error("Cannot convert [" + section + "]." + key + "=\"" + s + "\" to bool "
            "(supported: true/false/yes/no/on/off/1/0)");
    }

}