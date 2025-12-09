#include <string>
#include <iostream>
#include <algorithm>    // std::reverse

class Text {
public:
    virtual void render(const std::string& data) const {
        std::cout << data;
    }
};


class DecoratedText : public Text {
public:
    explicit DecoratedText(Text* text) : text_(text) {}
    Text* text_;
};

class ItalicText : public DecoratedText {
public:
    explicit ItalicText(Text* text) : DecoratedText(text) {}
    void render(const std::string& data) const {
        std::cout << "<i>";
        text_->render(data);
        std::cout << "</i>";
    }
};

class BoldText : public DecoratedText {
public:
    explicit BoldText(Text* text) : DecoratedText(text) {}
    void render(const std::string& data) const {
        std::cout << "<b>";
        text_->render(data);
        std::cout << "</b>";
    }
};

//НОВЫЕ КЛАССЫ ПО ЗАДАНИЮ

// <p>...</p>
class Paragraph : public DecoratedText {
public:
    explicit Paragraph(Text* text) : DecoratedText(text) {}
    void render(const std::string& data) const {
        std::cout << "<p>";
        text_->render(data);
        std::cout << "</p>";
    }
};

// "Hello world" -> "dlrow olleH"
class Reversed : public DecoratedText {
public:
    explicit Reversed(Text* text) : DecoratedText(text) {}
    void render(const std::string& data) const {
        std::string tmp = data;
        std::reverse(tmp.begin(), tmp.end());
        text_->render(tmp);
    }
};

// <a href=netology.ru>Hello world</a>
class Link : public DecoratedText {
public:
    explicit Link(Text* text) : DecoratedText(text) {}

    // реализация базового интерфейса (чтобы соответствовать Text)
    void render(const std::string& data) const {
        text_->render(data);
    }

    // перегрузка с двумя параметрами
    void render(const std::string& href, const std::string& text) const {
        std::cout << "<a href=" << href << ">";
        text_->render(text);
        std::cout << "</a>";
    }
};

int main() {
    // Проверка Paragraph
    auto p = new Paragraph(new Text());
    p->render("Hello world");          // <p>Hello world</p>
    std::cout << std::endl;

    // Проверка Reversed
    auto r = new Reversed(new Text());
    r->render("Hello world");          // dlrow olleH
    std::cout << std::endl;

    // Проверка Link
    auto l = new Link(new Text());
    l->render("netology.ru", "Hello world"); // <a href=netology.ru>Hello world</a>
    std::cout << std::endl;

    // Пример комбинирования декораторов: <p><b><i>Hello world</i></b></p>
    auto combo = new Paragraph(new BoldText(new ItalicText(new Text())));
    combo->render("Hello world");
    std::cout << std::endl;

    return 0;
}