#include <fstream>

class Printable
{
public:
    virtual ~Printable() = default;

    virtual std::string printAsHTML() const = 0;
    virtual std::string printAsText() const = 0;
    virtual std::string printAsJSON() const = 0;
};

/* 
Первый нарушенный прнцип LSP — принцип подстановки Лисков
Объект Data нельзя безопасно подставить вместо Printable, хотя он наследуется от него.
Интерфейс Printable подразумевает, что у объекта корректно работают все методы :

printAsHTML()
printAsText()
printAsJSON()

Но Data поддерживает только один формат, а остальные методы кидают исключение :

if (format_ != Format::kText) throw std::runtime_error("Invalid format!");

То есть наследник усиливает предусловия (нужно, чтобы format_ совпал), 
а это классический признак нарушения LSP: код, работающий с Printable, не ожидает, 
что вызов printAsText() у “Printable” внезапно станет недопустимым в зависимости от внутреннего состояния.

Второй нарушенный принцип ISP — принцип разделения интерфейса
У интерфейса Printable слишком много обязанностей сразу.

Любой класс, который хочет быть “Printable”, вынужден реализовать все три:

HTML
Text
JSON

Даже если ему нужен только один формат.

Data, чтобы соответствовать интерфейсу, реализует все методы, 
но два из них фактически становятся “невалидными” и кидают исключение. 
Это типичная проблема из-за нарушения ISP: зависимость от методов, которые не нужны.
*/

class Data : public Printable
{
public:
    enum class Format
    {
        kText,
        kHTML,
        kJSON
    };

    Data(std::string data, Format format)
        : data_(std::move(data)), format_(format) {
    }

    std::string printAsHTML() const override
    {
        if (format_ != Format::kHTML) {
            throw std::runtime_error("Invalid format!");
        }
        return "<html>" + data_ + "<html/>";
    }
    std::string printAsText() const override
    {
        if (format_ != Format::kText) {
            throw std::runtime_error("Invalid format!");
        }
        return data_;
    }
    std::string printAsJSON() const override
    {
        if (format_ != Format::kJSON) {
            throw std::runtime_error("Invalid format!");
        }
        return "{ \"data\": \"" + data_ + "\"}";
    }

private:
    std::string data_;
    Format format_;
};

/*
Третий нарушенный принцип OCP — принцип открытости/закрытости
Чтобы добавить новый формат (например, XML/Markdown), придётся править существующий код, 
а не просто расширять.

Интерфейс Printable жёстко зашит под 3 формата — добавление формата потребует изменять интерфейс 
(добавлять новый виртуальный метод).

saveTo(...) содержит switch(format) — при добавлении формата нужно модифицировать switch:

switch (format) { ... }

Появятся новые функции-обёртки saveToAs....
Система не “закрыта для изменений” — расширение форматов вынуждает переписывать уже написанные части.
*/


void saveTo(std::ofstream& file, const Printable& printable, Data::Format format)
{
    switch (format)
    {
    case Data::Format::kText:
        file << printable.printAsText();
        break;
    case Data::Format::kJSON:
        file << printable.printAsJSON();
        break;
    case Data::Format::kHTML:
        file << printable.printAsHTML();
        break;
    }
}

void saveToAsHTML(std::ofstream& file, const Printable& printable) {
    saveTo(file, printable, Data::Format::kHTML);
}

void saveToAsJSON(std::ofstream& file, const Printable& printable) {
    saveTo(file, printable, Data::Format::kJSON);
}

void saveToAsText(std::ofstream& file, const Printable& printable) {
    saveTo(file, printable, Data::Format::kText);
}