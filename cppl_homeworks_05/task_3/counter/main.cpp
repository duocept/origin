#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>

struct DivBy3Counter {
    long long sum = 0;
    std::size_t count = 0;

    void operator()(int x) {
        if (x % 3 == 0) {
            sum += x;
            ++count;
        }
    }

    long long get_sum() const { return sum; }
    std::size_t get_count() const { return count; }
};

int main() {
    std::cout << "[IN]: ";
    std::string line;
    std::getline(std::cin, line);

    std::istringstream iss(line);
    std::vector<int> nums;
    for (int x; iss >> x; ) nums.push_back(x);

    // std::for_each возвращает функтор по значению — удобно получить итоговое состояние
    DivBy3Counter counter = std::for_each(nums.begin(), nums.end(), DivBy3Counter{});

    std::cout << "[OUT]: get_sum() = " << counter.get_sum() << "\n";
    std::cout << "[OUT]: get_count() = " << counter.get_count() << "\n";

    return 0;
}