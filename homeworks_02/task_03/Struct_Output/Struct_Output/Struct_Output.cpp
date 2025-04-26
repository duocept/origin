#include <iostream>
#include <string>
#include <Windows.h>

struct Address {
    std::string city;
    std::string street;
    int bldg_num{};
    int aprt_num{};
    int index{};
};

void print(const Address& address) {
    std::cout << "Город: " << address.city << std::endl;
    std::cout << "Улица: " << address.street << std::endl;
    std::cout << "Номер дома: " << address.bldg_num << std::endl;
    std::cout << "Номер квартиры: " << address.aprt_num << std::endl;
    std::cout << "Индекс: " << address.index << std::endl;
    std::cout << std::endl;
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    Address address1{ "Москва", "Арбат", 12, 8, 123456 };
    Address address2{ "Ижевск", "Пушкина", 59, 143, 953769 };

    print(address1);
    print(address2);

    return EXIT_SUCCESS;
}