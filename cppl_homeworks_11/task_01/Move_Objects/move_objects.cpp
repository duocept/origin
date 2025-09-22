#include <iostream>
#include <vector>
#include <string>
#include <iterator>
#include <utility>

template <class T>
void move_vectors(std::vector<T>& from, std::vector<T>& to) {
    if (&from == &to) return;
    to.reserve(to.size() + from.size());
    to.insert(to.end(),
        std::make_move_iterator(from.begin()),
        std::make_move_iterator(from.end()));
    from.clear();
}

template <class T>
void print_vec(std::string_view name, const std::vector<T>& v) {
    std::cout << name << " (size=" << v.size() << ", cap=" << v.capacity() << "): [";
    for (size_t i = 0; i < v.size(); ++i) {
        if (i) std::cout << ", ";
        std::cout << '"' << v[i] << '"';
    }
    std::cout << "]\n";
}

int main() {
    std::vector<std::string> one = { "test_string1", "test_string2" };
    std::vector<std::string> two;

    std::cout << "== BEFORE ==\n";
    print_vec("one", one);
    print_vec("two", two);

    move_vectors(one, two);

    std::cout << "\n== AFTER move_vectors(one, two) ==\n";
    print_vec("one", one);
    print_vec("two", two);

    return 0;
}
