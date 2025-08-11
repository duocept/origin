#include <iostream>
#include <stdexcept>
#include <limits>
#include <cstdlib> // std::abs

class Fraction {
private:
    int numerator_;
    int denominator_;

    static int gcd(int a, int b) {
        a = std::abs(a);
        b = std::abs(b);
        while (b) {
            int t = a % b;
            a = b;
            b = t;
        }
        return a == 0 ? 1 : a;
    }

    void normalize() {
        if (denominator_ == 0) throw std::invalid_argument("Denominator must not be zero");
        if (denominator_ < 0) {
            numerator_ = -numerator_;
            denominator_ = -denominator_;
        }
        int g = gcd(numerator_, denominator_);
        numerator_ /= g;
        denominator_ /= g;
    }

public:
    Fraction(int numerator = 0, int denominator = 1)
        : numerator_(numerator), denominator_(denominator) {
        normalize();
    }

    // ----- сравнения (из задачи 1) -----
    friend bool operator==(const Fraction& a, const Fraction& b) {
        return (long long)a.numerator_ * b.denominator_
            == (long long)b.numerator_ * a.denominator_;
    }
    friend bool operator<(const Fraction& a, const Fraction& b) {
        return (long long)a.numerator_ * b.denominator_
            < (long long)b.numerator_* a.denominator_;
    }
    friend bool operator!=(const Fraction& a, const Fraction& b) { return !(a == b); }
    friend bool operator>(const Fraction& a, const Fraction& b) { return b < a; }
    friend bool operator<=(const Fraction& a, const Fraction& b) { return !(b < a); }
    friend bool operator>=(const Fraction& a, const Fraction& b) { return !(a < b); }

    // ----- вывод -----
    friend std::ostream& operator<<(std::ostream& os, const Fraction& f) {
        return os << f.numerator_ << '/' << f.denominator_;
    }

    // ----- арифметика -----
    friend Fraction operator+(const Fraction& a, const Fraction& b) {
        long long num = (long long)a.numerator_ * b.denominator_
            + (long long)b.numerator_ * a.denominator_;
        long long den = (long long)a.denominator_ * b.denominator_;
        return Fraction((int)num, (int)den);
    }
    friend Fraction operator-(const Fraction& a, const Fraction& b) {
        long long num = (long long)a.numerator_ * b.denominator_
            - (long long)b.numerator_ * a.denominator_;
        long long den = (long long)a.denominator_ * b.denominator_;
        return Fraction((int)num, (int)den);
    }
    friend Fraction operator*(const Fraction& a, const Fraction& b) {
        long long num = (long long)a.numerator_ * b.numerator_;
        long long den = (long long)a.denominator_ * b.denominator_;
        return Fraction((int)num, (int)den);
    }
    friend Fraction operator/(const Fraction& a, const Fraction& b) {
        if (b.numerator_ == 0) throw std::domain_error("Division by zero fraction");
        long long num = (long long)a.numerator_ * b.denominator_;
        long long den = (long long)a.denominator_ * b.numerator_;
        return Fraction((int)num, (int)den);
    }

    // унарный минус
    Fraction operator-() const { return Fraction(-numerator_, denominator_); }

    // ----- инкремент/декремент -----
    // префиксные
    Fraction& operator++() { numerator_ += denominator_; normalize(); return *this; } // +1
    Fraction& operator--() { numerator_ -= denominator_; normalize(); return *this; } // -1
    // постфиксные (фиктивный int-параметр)
    Fraction operator++(int) { Fraction tmp(*this); numerator_ += denominator_; normalize(); return tmp; }
    Fraction operator--(int) { Fraction tmp(*this); numerator_ -= denominator_; normalize(); return tmp; }
};

int main() {

    setlocale(LC_ALL, "rus");

    try {
        int n1, d1, n2, d2;

        std::cout << "Введите числитель дроби 1: ";
        std::cin >> n1;
        std::cout << "Введите знаменатель дроби 1: ";
        while (true) {
            std::cin >> d1;
            if (d1 != 0) break;
            std::cout << "Знаменатель не может быть 0. Введите снова: ";
        }

        std::cout << "Введите числитель дроби 2: ";
        std::cin >> n2;
        std::cout << "Введите знаменатель дроби 2: ";
        while (true) {
            std::cin >> d2;
            if (d2 != 0) break;
            std::cout << "Знаменатель не может быть 0. Введите снова: ";
        }

        Fraction f1(n1, d1);
        Fraction f2(n2, d2);

        std::cout << f1 << " + " << f2 << " = " << (f1 + f2) << '\n';
        std::cout << f1 << " - " << f2 << " = " << (f1 - f2) << '\n';
        std::cout << f1 << " * " << f2 << " = " << (f1 * f2) << '\n';
        std::cout << f1 << " / " << f2 << " = " << (f1 / f2) << '\n';

        // Демонстрация префиксного инкремента в выражении
        std::cout << "++" << f1 << " * " << f2 << " = " << (++f1 * f2) << '\n';
        std::cout << "Значение дроби 1 = " << f1 << '\n';

        // Демонстрация постфиксного декремента в выражении
        std::cout << f1 << "-- * " << f2 << " = " << (f1-- * f2) << '\n';
        std::cout << "Значение дроби 1 = " << f1 << '\n';
    }
    catch (const std::exception& ex) {
        std::cerr << "Ошибка: " << ex.what() << '\n';
        return 1;
    }
    return 0;
}