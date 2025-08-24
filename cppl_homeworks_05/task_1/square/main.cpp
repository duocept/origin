#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include "square.h"

static std::string trim(std::string s) {
    auto not_space = [](int ch) { return !std::isspace(ch); };
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), not_space));
    s.erase(std::find_if(s.rbegin(), s.rend(), not_space).base(), s.end());
    return s;
}

static std::vector<long long> parse_numbers(const std::string& line) {
    std::string normalized = line;
    std::replace(normalized.begin(), normalized.end(), ',', ' ');
    std::istringstream iss(normalized);
    std::vector<long long> nums;
    long long x;
    while (iss >> x) nums.push_back(x);
    return nums;
}

static void print_vector(const std::vector<long long>& v) {
    for (size_t i = 0; i < v.size(); ++i) {
        if (i) std::cout << ", ";
        std::cout << v[i];
    }
    std::cout << '\n';
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    for (;;) {
        std::cout << "[IN]: " << std::flush;   // показываем приглашение
        std::string line;
        if (!std::getline(std::cin, line)) break;

        line = trim(line);
        if (line.empty()) continue;
        if (line == "exit") break;

        auto nums = parse_numbers(line);
        if (nums.empty()) {
            std::cout << "[OUT]: (ошибка ввода)\n";
            continue;
        }

        if (nums.size() == 1) {
            std::cout << "[OUT]: " << square(nums[0]) << '\n';
        }
        else {
            std::cout << "[OUT]: ";
            print_vector(square(nums));
        }
    }
    return 0;
}
