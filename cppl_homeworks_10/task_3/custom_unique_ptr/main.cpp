// кастомный std::unique_ptr
#include <utility>   // std::swap, std::move
#include <iostream>
#include <stdexcept> // добавлено: для выброса исключения при разыменовании nullptr

template <typename T>
class unique_ptr_simplified {
public:
    // Конструктор из сырого указателя
    explicit unique_ptr_simplified(T* p = nullptr) noexcept : ptr_(p) {}

    // Запрет копирования
    unique_ptr_simplified(const unique_ptr_simplified&) = delete;
    unique_ptr_simplified& operator=(const unique_ptr_simplified&) = delete;

    // Разрешаем перемещение
    unique_ptr_simplified(unique_ptr_simplified&& other) noexcept : ptr_(other.ptr_) {
        other.ptr_ = nullptr;
    }
    unique_ptr_simplified& operator=(unique_ptr_simplified&& other) noexcept {
        if (this != &other) {
            delete ptr_;
            ptr_ = other.ptr_;
            other.ptr_ = nullptr;
        }
        return *this;
    }

    // Оператор * для доступа к объекту
    // добавлено: проверка на nullptr + снят noexcept, т.к. бросаем исключение
    T& operator*() const {
        if (!ptr_) {
            // добавлено: предотвращаем UB при разыменовании пустого указателя
            throw std::runtime_error("unique_ptr_simplified: null dereference");
        }
        return *ptr_;
    }

    // Оператор -> как у обычного умного указателя
    T* operator->() const noexcept { return ptr_; }

    // Проверка на непустоту
    explicit operator bool() const noexcept { return ptr_ != nullptr; }

    // Получить сырой указатель без изменения владения
    T* get() const noexcept { return ptr_; }

    // release: отдать владение и обнулить себя
    T* release() noexcept {
        T* tmp = ptr_;
        ptr_ = nullptr;
        return tmp;
    }

    // reset: заменить управляемый указатель
    void reset(T* p = nullptr) noexcept {
        if (ptr_ != p) {
            delete ptr_;
            ptr_ = p;
        }
    }

    // swap
    void swap(unique_ptr_simplified& other) noexcept {
        std::swap(ptr_, other.ptr_);
    }

    // Деструктор освобождает ресурс
    ~unique_ptr_simplified() { delete ptr_; }

private:
    T* ptr_ = nullptr;
};

// Пример использования
struct Foo {
    Foo(int v) : v(v) { std::cout << "Foo(" << v << ")\n"; }
    ~Foo() { std::cout << "~Foo(" << v << ")\n"; }
    int v;
};

int main() {
    unique_ptr_simplified<Foo> p(new Foo(10));
    std::cout << (*p).v << " " << p->v << "\n";

    // Перемещение
    unique_ptr_simplified<Foo> q = std::move(p);
    std::cout << std::boolalpha << static_cast<bool>(p) << " " << static_cast<bool>(q) << "\n";

    // release отдаёт сырой указатель и отключает владение
    Foo* raw = q.release();
    std::cout << "after release, q is " << static_cast<bool>(q) << "\n";
    delete raw; // сами отвечаем за delete

    // reset заменяет управляемый объект
    q.reset(new Foo(42));
    // q разрушится и удалит Foo(42) автоматически

    return 0;
}