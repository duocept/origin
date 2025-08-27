#include <iostream>
#include <set>
#include <functional> // std::greater

int main() {
    std::cout << "[IN]:\n";
    std::cout << "[AMOUNT OF NUMBERS]: ";
    int n;
    if (!(std::cin >> n)) {
        std::cerr << "Ожидалось целое N.\n";
        return 1;
    }

    std::set<long long, std::greater<long long>> uniq_desc;
    for (int i = 0; i < n; ++i) {
        long long x;
        if (!(std::cin >> x)) {
            std::cerr << "Ожидалось число #" << (i + 1) << ".\n";
            return 1;
        }
        uniq_desc.insert(x);
    }

    std::cout << "[OUT]:\n";
    for (long long v : uniq_desc) {
        std::cout << v << '\n';
    }
    return 0;
}
