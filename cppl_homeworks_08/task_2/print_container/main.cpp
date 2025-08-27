#include <iostream>
#include <string_view>
#include <set>
#include <list>
#include <vector>
#include <string>

template <class Container>
void print_container(const Container& c, std::string_view sep = ", ") {
    auto it = c.begin(), it_end = c.end();
    if (it == it_end) { std::cout << '\n'; return; }
    std::cout << *it;
    for (++it; it != it_end; ++it) std::cout << sep << *it;
    std::cout << '\n';
}

int main() {
    std::set<std::string> test_set = { "one","two","three","four" };
    std::list<std::string> test_list = { "one","two","three","four" };
    std::vector<std::string> test_vector = { "one","two","three","four" };

    print_container(test_set, " ");   // four one three two  (set хранит элементы в отсортированном порядке)
    print_container(test_list);       // one, two, three, four
    print_container(test_vector);     // one, two, three, four
}