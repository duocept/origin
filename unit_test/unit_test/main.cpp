#include <iostream>
#include <string>
#include <stdexcept>
#include <typeinfo>
#include "extended_array.h"

static int g_failed = 0;
static int g_passed = 0;

#define EXPECT_TRUE(expr) do { if (!(expr)) { \
    std::cerr << "[FAIL] " << __FILE__ << ":" << __LINE__ << " EXPECT_TRUE(" #expr ")\n"; ++g_failed; \
} else { ++g_passed; } } while(0)

#define EXPECT_EQ(a,b) do { auto _va=(a); auto _vb=(b); if (!((_va)==(_vb))) { \
    std::cerr << "[FAIL] " << __FILE__ << ":" << __LINE__ << " EXPECT_EQ(" #a "," #b ") got: " << _va << " vs " << _vb << "\n"; ++g_failed; \
} else { ++g_passed; } } while(0)

#define EXPECT_NEAR(a,b,eps) do { double _va=(double)(a); double _vb=(double)(b); \
    if (std::abs(_va-_vb) > (eps)) { \
    std::cerr << "[FAIL] " << __FILE__ << ":" << __LINE__ << " EXPECT_NEAR(" #a "," #b "," #eps ") got: " << _va << " vs " << _vb << "\n"; ++g_failed; \
} else { ++g_passed; } } while(0)

#define EXPECT_THROW(stmt, ex_type) do { bool _thrown=false; try { stmt; } catch (const ex_type&) { _thrown=true; } catch (...) {} \
    if (!_thrown) { std::cerr << "[FAIL] " << __FILE__ << ":" << __LINE__ << " EXPECT_THROW(" #stmt ", " #ex_type ")\n"; ++g_failed; } else { ++g_passed; } } while(0)

#define EXPECT_NO_THROW(stmt) do { try { stmt; ++g_passed; } catch (...) { \
    std::cerr << "[FAIL] " << __FILE__ << ":" << __LINE__ << " EXPECT_NO_THROW(" #stmt ")\n"; ++g_failed; } } while(0)

int main() {
    // ===== Задание 1: пустые массивы =====
    {
        ExtArray<int> ai(0);
        ExtArray<double> ad(0);
        ExtArray<bool> ab(0);

        EXPECT_NEAR(ai.mean(), 0.0, 1e-12);
        EXPECT_NEAR(ad.mean(), 0.0, 1e-12);
        EXPECT_NEAR(ab.mean(), 0.0, 1e-12);

        EXPECT_NEAR(ai.median(), 0.0, 1e-12);
        EXPECT_NEAR(ad.median(), 0.0, 1e-12);
        EXPECT_NEAR(ab.median(), 0.0, 1e-12);

        auto m = ai.mode();
        EXPECT_EQ(m.second, 0);   // частота == 0
        EXPECT_EQ(m.first, 0);    // значение по умолчанию T{} == 0 для int
    }

    // Дополнительно sanity для непустых
    {
        ExtArray<int> a{ 1,3,2,4 };
        EXPECT_NEAR(a.mean(), (1 + 3 + 2 + 4) / 4.0, 1e-12);
        EXPECT_NEAR(a.median(), (2 + 3) / 2.0, 1e-12);

        ExtArray<int> b{ 1,2,2,3,2 };
        auto mo = b.mode();
        EXPECT_EQ(mo.first, 2);
        EXPECT_EQ(mo.second, 3);
    }

    // ===== Задание 2: mean(begin,end) =====
    {
        ExtArray<int> a{ 1,2,3,4,5 };
        // корректный диапазон [1,4) => (2+3+4)/3 = 3
        EXPECT_NEAR(a.mean(1, 4), 3.0, 1e-12);

        // begin >= end -> invalid_argument
        EXPECT_THROW(a.mean(2, 2), std::invalid_argument);
        EXPECT_THROW(a.mean(4, 1), std::invalid_argument);

        // выход за границы -> out_of_range
        EXPECT_THROW(a.mean(0, 6), std::out_of_range);
        EXPECT_THROW(a.mean(10, 11), std::out_of_range);

        // пограничные корректные случаи
        EXPECT_NEAR(a.mean(0, 1), 1.0, 1e-12);
        EXPECT_NEAR(a.mean(4, 5), 5.0, 1e-12);
    }

    // ===== Задание 3: checkSum =====
    {
        // bool
        ExtArray<bool> ab{ true,false,true,false,true };
        EXPECT_EQ(ab.checkSum(), static_cast<std::size_t>(3));

        // int корректный
        ExtArray<int> ai{ 0,1,1,0,1,0,0,1 };
        EXPECT_EQ(ai.checkSum(), static_cast<std::size_t>(4));

        // int с неверным содержимым -> logic_error
        ExtArray<int> bad{ 0,2,1 };
        EXPECT_THROW(bad.checkSum(), std::logic_error);

        // другой тип -> bad_typeid
        ExtArray<double> ad{ 0.0, 1.0, 0.0 };
        EXPECT_THROW(ad.checkSum(), std::bad_typeid);

        // пустые массивы -> 0
        ExtArray<int> ai0(0);
        ExtArray<bool> ab0(0);
        EXPECT_EQ(ai0.checkSum(), static_cast<std::size_t>(0));
        EXPECT_EQ(ab0.checkSum(), static_cast<std::size_t>(0));
    }

    std::cout << "\nPassed: " << g_passed << ", Failed: " << g_failed << "\n";
    return g_failed == 0 ? 0 : 1;
}