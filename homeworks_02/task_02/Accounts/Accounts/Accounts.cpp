#include <iostream>
#include <string>
#include <Windows.h>

struct Account {
    int account_number{};
    std::string name{};
    double balance{};
};

void print(Account& account){
    std::cout << "Ваш счёт : " << account.name << ", " << account.account_number << ", " << account.balance << std::endl;
}

void change_balance(Account& account) {
    std::cin >> account.balance;
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    Account person_account;

    std::cout << "Введите номер счёта : ";
    std::cin >> person_account.account_number;

    std::cout << "Введите имя владельца : ";
    getline(std::cin >> std::ws, person_account.name);

    std::cout << "Введите баланс : ";
    std::cin >> person_account.balance;

    std::cout << "Введите новый баланс :";
    change_balance(person_account);

    print(person_account);

    return EXIT_SUCCESS;
}