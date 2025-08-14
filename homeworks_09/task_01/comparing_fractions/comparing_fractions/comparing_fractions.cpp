#include <iostream>
#include <stdexcept>
#include <cstdlib>   //std::abs

class Fraction
{
private:
    long long numerator_;   // ранее был int
    long long denominator_; // то же самое

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
        if (denominator_ == 0) {
            throw std::invalid_argument("Denominator must not be zero");
        }
        // держим знак только в числителе
        if (denominator_ < 0) {
            numerator_ = -numerator_;
            denominator_ = -denominator_;
        }
        // сократим дробь
        int g = gcd(numerator_, denominator_);
        numerator_ /= g;
        denominator_ /= g;
    }

public:
    Fraction(long long numerator = 0, long long denominator = 1)
        : numerator_(numerator), denominator_(denominator)
    {
        normalize();
    }

    // == : a/b == c/d  <=>  a*d == c*b
    friend bool operator==(const Fraction& a, const Fraction& b) {
        return a.numerator_ * b.denominator_
            == b.numerator_ * a.denominator_;
    }

    // < : a/b < c/d  <=>  a*d < c*b
    friend bool operator<(const Fraction& a, const Fraction& b) {
        return a.numerator_ * b.denominator_
            < b.numerator_* a.denominator_;
    }

    // Остальные через == и <
    friend bool operator!=(const Fraction& a, const Fraction& b) { return !(a == b); }
    friend bool operator>(const Fraction& a, const Fraction& b) { return b < a; }
    friend bool operator<=(const Fraction& a, const Fraction& b) { return !(b < a); }
    friend bool operator>=(const Fraction& a, const Fraction& b) { return !(a < b); }
};

int main()
{
    Fraction f1(4, 3);
    Fraction f2(6, 11);

    std::cout << "f1" << ((f1 == f2) ? " == " : " not == ") << "f2" << '\n';
    std::cout << "f1" << ((f1 != f2) ? " != " : " not != ") << "f2" << '\n';
    std::cout << "f1" << ((f1 < f2) ? " < " : " not < ") << "f2" << '\n';
    std::cout << "f1" << ((f1 > f2) ? " > " : " not > ") << "f2" << '\n';
    std::cout << "f1" << ((f1 <= f2) ? " <= " : " not <= ") << "f2" << '\n';
    std::cout << "f1" << ((f1 >= f2) ? " >= " : " not >= ") << "f2" << '\n';
    return 0;
}