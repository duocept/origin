#include <iostream>
#include "smart_array.h"

int main() {
    try {
        smart_array arr(5);
        arr.add_element(1);
        arr.add_element(4);
        arr.add_element(155);

        smart_array new_array(2);
        new_array.add_element(44);
        new_array.add_element(34);

        arr = new_array;

        std::cout << arr.size() << " elems, cap = " << arr.capacity() << "\n";
        std::cout << arr.get_element(0) << ", " << arr.get_element(1) << "\n"; // 44, 34
    }
    catch (const std::exception& ex) {
        std::cout << "Error: " << ex.what() << "\n";
    }
}
