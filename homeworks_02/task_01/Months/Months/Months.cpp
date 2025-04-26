#include <iostream>

enum class Months
{
	Январь = 1,
	Февраль,
	Март,
	Апрель,
	Май,
	Июнь,
	Июль,
	Август,
	Сентябрь,
	Октябрь,
	Ноябрь,
	Декабрь
};

int main()
{
    setlocale(LC_ALL, "rus");

	int num{1};
    while (true) {
        std::cout << "Введите номер месяца: ";
        std::cin >> num;

        if (num == 0) {
            std::cout << "До свидания" << std::endl;
            break;
        }

        Months months = static_cast<Months>(num);

        switch (months)
        {
        case Months::Январь: std::cout << "Январь" << std::endl; break;
        case Months::Февраль: std::cout << "Февраль" << std::endl; break;
        case Months::Март: std::cout << "Март" << std::endl; break;
        case Months::Апрель: std::cout << "Апрель" << std::endl; break;
        case Months::Май: std::cout << "Май" << std::endl; break;
        case Months::Июнь: std::cout << "Июнь" << std::endl; break;
        case Months::Июль: std::cout << "Июль" << std::endl; break;
        case Months::Август: std::cout << "Август" << std::endl; break;
        case Months::Сентябрь: std::cout << "Сентябрь" << std::endl; break;
        case Months::Октябрь: std::cout << "Октябрь" << std::endl; break;
        case Months::Ноябрь: std::cout << "Ноябрь" << std::endl; break;
        case Months::Декабрь: std::cout << "Декабрь" << std::endl; break;
        default:
            std::cout << "Введён неверный номер" << std::endl; break;
        }
    }

	return EXIT_SUCCESS;
}