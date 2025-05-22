#include "math_functions.h"

double add(double a, double b) {
    return a + b;
}

double subtract(double a, double b) {
    return a - b;
}

double multiply(double a, double b) {
    return a * b;
}

double divide(double a, double b) {
    return a / b;
}

double power(double a, double b) {
    if (b == 0)
        return 1;

    bool negative = b < 0;
    if (negative)
        b = -b;

    double result = 1;
    for (int i = 0; i < b; ++i) {
        result *= a;
    }

    return negative ? 1.0 / result : result;
}
