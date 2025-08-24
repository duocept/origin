#pragma once
#include <cstddef> // std::size_t

class smart_array {
public:
    explicit smart_array(std::size_t capacity);
    smart_array(const smart_array& other);
    smart_array(smart_array&& other) noexcept;
    smart_array& operator=(const smart_array& other);
    smart_array& operator=(smart_array&& other) noexcept;
    ~smart_array();

    void add_element(int value);
    int  get_element(std::size_t index) const;

    std::size_t size() const noexcept { return m_size; }
    std::size_t capacity() const noexcept { return m_capacity; }

private:
    std::size_t m_size{ 0 };
    std::size_t m_capacity{ 0 };
    int* m_data{ nullptr };

    void swap(smart_array& other) noexcept;
};