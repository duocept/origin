#include <iostream>
#include <fstream>
#include <ostream>
#include <string>
#include <string_view>
#include <utility>

// Узкие интерфейсы (ISP)
struct ITextPrintable {
    virtual ~ITextPrintable() = default;
    virtual std::string printAsText() const = 0;
};

struct IHtmlPrintable {
    virtual ~IHtmlPrintable() = default;
    virtual std::string printAsHTML() const = 0;
};

struct IJsonPrintable {
    virtual ~IJsonPrintable() = default;
    virtual std::string printAsJSON() const = 0;
};

// Базовые данные (без знания форматов)
class Data {
public:
    explicit Data(std::string data) : data_(std::move(data)) {}
    virtual ~Data() = default;

protected:
    const std::string& raw() const noexcept { return data_; }

private:
    std::string data_;
};

// Наследники по форматам (логика форматирования здесь)
class TextData final : public Data, public ITextPrintable {
public:
    using Data::Data;

    std::string printAsText() const override {
        return raw();
    }
};

class HtmlData final : public Data, public IHtmlPrintable {
public:
    using Data::Data;

    std::string printAsHTML() const override {
        return "<html>" + raw() + "</html>";
    }
};

class JsonData final : public Data, public IJsonPrintable {
public:
    using Data::Data;

    std::string printAsJSON() const override {
        return "{ \"data\": \"" + raw() + "\" }";
    }
};

// saveTo НЕ знает о формате, он просто пишет байты (как и требуется)
inline void saveTo(std::ostream& out, std::string_view bytes) {
    out << bytes;
}

// Функции сохранения по форматам (сохранились)
inline void saveToAsText(std::ostream& out, const ITextPrintable& printable) {
    const std::string s = printable.printAsText();
    saveTo(out, s);
}

inline void saveToAsHTML(std::ostream& out, const IHtmlPrintable& printable) {
    const std::string s = printable.printAsHTML();
    saveTo(out, s);
}

inline void saveToAsJSON(std::ostream& out, const IJsonPrintable& printable) {
    const std::string s = printable.printAsJSON();
    saveTo(out, s);
}

int main() {
    std::ofstream f1("a.txt"), f2("a.html"), f3("a.json");

    TextData t("hello");
    HtmlData h("hello");
    JsonData j("hello");

    saveToAsText(f1, t);
    saveToAsHTML(f2, h);
    saveToAsJSON(f3, j);

    std::cout << "Task completed!" << std::endl;

    return 0;

}
