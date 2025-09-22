#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <cctype>
#include <utility>

class big_integer {
public:
    big_integer() : digits_(1, 0) {} // 0
    explicit big_integer(const std::string& s) { from_string(s); }
    explicit big_integer(const char* s) { from_string(std::string(s)); }
    explicit big_integer(unsigned long long v) { from_ull(v); }

    // Копирование
    big_integer(const big_integer&) = default;
    big_integer& operator=(const big_integer&) = default;

    // Перемещение
    big_integer(big_integer&& other) noexcept
        : digits_(std::move(other.digits_)) {}

    big_integer& operator=(big_integer&& other) noexcept {
        if (this != &other) digits_ = std::move(other.digits_);
        return *this;
    }

    // Сложение
    friend big_integer operator+(const big_integer& a, const big_integer& b) {
        big_integer res;
        res.digits_.clear();
        const size_t n = a.digits_.size();
        const size_t m = b.digits_.size();
        const size_t k = (n > m ? n : m);

        unsigned carry = 0;
        for (size_t i = 0; i < k; ++i) {
            unsigned da = (i < n ? a.digits_[i] : 0);
            unsigned db = (i < m ? b.digits_[i] : 0);
            unsigned sum = da + db + carry;
            res.digits_.push_back(static_cast<uint8_t>(sum % 10));
            carry = sum / 10;
        }
        if (carry) res.digits_.push_back(static_cast<uint8_t>(carry));
        return res;
    }

    big_integer& operator+=(const big_integer& rhs) {
        *this = *this + rhs;
        return *this;
    }

    // Умножение на число
    big_integer& operator*=(unsigned int m) {
        if (m == 0 || is_zero()) { digits_.assign(1, 0); return *this; }
        if (m == 1) return *this;

        uint64_t carry = 0;
        for (size_t i = 0; i < digits_.size(); ++i) {
            uint64_t prod = static_cast<uint64_t>(digits_[i]) * m + carry;
            digits_[i] = static_cast<uint8_t>(prod % 10);
            carry = prod / 10;
        }
        while (carry) {
            digits_.push_back(static_cast<uint8_t>(carry % 10));
            carry /= 10;
        }
        trim();
        return *this;
    }

    friend big_integer operator*(const big_integer& a, unsigned int m) {
        big_integer tmp = a;
        tmp *= m;
        return tmp;
    }

    // Вывод
    friend std::ostream& operator<<(std::ostream& os, const big_integer& x) {
        for (size_t i = x.digits_.size(); i-- > 0; ) {
            os << char('0' + x.digits_[i]);
        }
        return os;
    }

private:
    // хранение
    std::vector<uint8_t> digits_;

    bool is_zero() const { return digits_.size() == 1 && digits_[0] == 0; }

    void trim() {
        while (digits_.size() > 1 && digits_.back() == 0) digits_.pop_back();
    }

    void from_ull(unsigned long long v) {
        digits_.clear();
        if (v == 0) { digits_.push_back(0); return; }
        while (v) {
            digits_.push_back(static_cast<uint8_t>(v % 10));
            v /= 10;
        }
    }

    void from_string(const std::string& sraw) {

        size_t l = 0, r = sraw.size();
        while (l < r && std::isspace(static_cast<unsigned char>(sraw[l]))) ++l;
        while (r > l && std::isspace(static_cast<unsigned char>(sraw[r - 1]))) --r;
        if (l == r) throw std::invalid_argument("empty string");

        if (sraw[l] == '+') ++l;
        if (l < r && sraw[l] == '-') throw std::invalid_argument("negative not supported");

        while (l < r&& sraw[l] == '0') ++l;

        digits_.clear();
        if (l == r) { digits_.push_back(0); return; } // число было "0...0"

        for (size_t i = r; i-- > l; ) {
            char c = sraw[i];
            if (!std::isdigit(static_cast<unsigned char>(c)))
                throw std::invalid_argument("invalid digit");
            digits_.push_back(static_cast<uint8_t>(c - '0'));
        }
        trim();
    }
};

int main() {
    big_integer number1("114575");
    big_integer number2("78524");
    big_integer result = number1 + number2;
    std::cout << result << "\n"; // 193099

    // Дополнительно: умножение на число
    big_integer a("9999999999999999999999999");
    std::cout << (a * 7) << "\n"; // 69999999999999999999999993

    // Перемещение
    big_integer tmp("123456");
    big_integer moved = std::move(tmp); // move-конструктор
    moved *= 25;
    std::cout << moved << "\n"; // 3086400

    return 0;
}