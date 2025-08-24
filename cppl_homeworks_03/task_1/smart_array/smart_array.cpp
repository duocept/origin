#include "smart_array.h"
#include <algorithm>   // std::copy, std::swap
#include <stdexcept>   // std::invalid_argument, std::overflow_error, std::out_of_range

smart_array::smart_array(std::size_t capacity)
    : m_size(0), m_capacity(capacity), m_data(nullptr)
{
    if (capacity == 0) {
        throw std::invalid_argument("smart_array: capacity must be > 0");
    }
    m_data = new int[m_capacity];
}

smart_array::smart_array(const smart_array& other)
    : m_size(other.m_size), m_capacity(other.m_capacity), m_data(new int[other.m_capacity])
{
    std::copy(other.m_data, other.m_data + other.m_size, m_data);
}

smart_array::smart_array(smart_array&& other) noexcept
    : m_size(other.m_size), m_capacity(other.m_capacity), m_data(other.m_data)
{
    other.m_size = 0;
    other.m_capacity = 0;
    other.m_data = nullptr;
}

smart_array& smart_array::operator=(const smart_array& other) {
    if (this != &other) {
        smart_array tmp(other); // copy
        swap(tmp);              // and swap (copy-and-swap idiom)
    }
    return *this;
}

smart_array& smart_array::operator=(smart_array&& other) noexcept {
    if (this != &other) {
        delete[] m_data;
        m_data = other.m_data;
        m_size = other.m_size;
        m_capacity = other.m_capacity;

        other.m_data = nullptr;
        other.m_size = 0;
        other.m_capacity = 0;
    }
    return *this;
}

smart_array::~smart_array() {
    delete[] m_data;
}

void smart_array::add_element(int value) {
    if (m_size >= m_capacity) {
        throw std::overflow_error("smart_array: no space left (overflow)");
    }
    m_data[m_size++] = value;
}

int smart_array::get_element(std::size_t index) const {
    if (index >= m_size) {
        throw std::out_of_range("smart_array: index out of range");
    }
    return m_data[index];
}

void smart_array::swap(smart_array& other) noexcept {
    std::swap(m_size, other.m_size);
    std::swap(m_capacity, other.m_capacity);
    std::swap(m_data, other.m_data);
}