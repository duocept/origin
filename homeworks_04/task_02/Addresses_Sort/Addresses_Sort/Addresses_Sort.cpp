#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>

// Класс для хранения адреса
class Address {
private:
    std::string city;
    std::string street;
    int house;
    int apartment;

public:
    // Конструктор с параметрами
    Address(const std::string& city, const std::string& street, int house, int apartment)
        : city(city), street(street), house(house), apartment(apartment) {}

    // Метод для получения строки вывода
    std::string get_output_address() const {
        return city + ", " + street + ", " + std::to_string(house) + ", " + std::to_string(apartment);
    }

    std::string get_city() const {
        return city;
    }
};

// Функция сортировки по названию города (по алфавиту, пузырьком)
void sort(Address** addresses, int size) {
    for (int i = 0; i < size - 1; ++i) {
        for (int j = 0; j < size - 1 - i; ++j) {
            if (addresses[j]->get_city() > addresses[j + 1]->get_city()) {
                std::swap(addresses[j], addresses[j + 1]);
            }
        }
    }
};

int main() {

    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    std::ifstream input("in.txt");
    std::ofstream output("out.txt");

    if (!input || !output) {
        std::cerr << "Ошибка открытия файлов!" << std::endl;
        return 1;
    }

    int n;
    input >> n;
    input.ignore(); // Сбросить перевод строки после числа

    Address** addresses = new Address * [n]; // динамический массив указателей

    for (int i = 0; i < n; ++i) {
        std::string city, street;
        int house, apartment;

        std::getline(input, city);
        std::getline(input, street);
        input >> house >> apartment;
        input.ignore(); // Сбросить перевод строки после номера квартиры

        addresses[i] = new Address(city, street, house, apartment);
    }

    sort(addresses, n);

    output << n << std::endl;
    for (int i = 0; i < n; ++i) {
        output << addresses[i]->get_output_address() << std::endl;
    }

    // Освобождение памяти
    for (int i = 0; i < n; ++i) {
        delete addresses[i];
    }
    delete[] addresses;

    input.close();
    output.close();

    return EXIT_SUCCESS;
}