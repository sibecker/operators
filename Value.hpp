#ifndef OPERATORS_VALUE_H
#define OPERATORS_VALUE_H

#include <iostream>
#include <memory>

template<typename T>
struct Value {
    T value;

    // For convenience
    constexpr Value(T v) :
        value{v} {
    }

    constexpr Value(Value&&) = default;
    constexpr Value(const Value&) = default;

    // Basis operator: cast
    explicit constexpr operator T() const {
        return value;
    }
    template<typename U>
    explicit constexpr operator Value<U>() const {
        return Value<U>{static_cast<U>(value)};
    }

    // Basis operator: subtraction
    template<typename U>
    auto constexpr operator-(Value<U> rhs) const {
        return Value<decltype(value - rhs.value)>{value - rhs.value};
    }

    // Basis operator: dereference
    constexpr auto &operator*() { return *value; }
    constexpr const auto &operator*() const { return *value; }


    // Derived operator: new
    static constexpr void* operator new(std::size_t count) { std::cout << "new" ; return malloc(count); }
    static constexpr void* operator new[](std::size_t count) { std::cout << "new[]";  return malloc(count); }
    static constexpr void* operator new(std::size_t count, void* ptr) { std::cout << "new()"; return ptr; }
    static constexpr void operator delete(void* ptr) { std::cout << "delete"; return free(ptr); }
    static constexpr void operator delete[](void* ptr) { std::cout << "delete[]"; return free(ptr); }

    // Derived operator: comma
    template<typename U>
    constexpr Value<U> operator,(Value<U> rhs) const { return rhs; }

    // Derived operator: address-of
    constexpr Value<T*> operator&() { return Value<T*>{reinterpret_cast<T*>(this)}; }
    constexpr Value<const T*> operator&() const { return Value<T*>{reinterpret_cast<const T*>(this)}; }

    // Derived operator: assignment
    constexpr Value &operator=(Value rhs) { return *(new (this) Value{rhs}); }
    constexpr Value &operator=(T rhs) { return *this = Value{rhs}; }

    // Derived operator: positive
    constexpr Value operator+() const {
        return *this;
    }

    // Derived operator: negative
    constexpr Value operator-() const {
        return Value{0} - *this;
    }

    // Derived operator: self-subtraction
    template<typename U>
    constexpr Value &operator-=(Value<U> rhs) {
        return *this = (*this - rhs);
    }

    // Derived operator: self-addition
    template<typename U>
    constexpr Value &operator+=(Value<U> rhs) {
        return *this -= -rhs;
    }

    // Derived operator: addition
    template<typename U>
    constexpr auto operator+(Value<U> rhs) {
        return *this - -rhs;
    }
    template<typename U>
    constexpr auto operator+(Value<U*> rhs) {
        return rhs - -*this;
    }

    // Derived operator: increment
    constexpr Value &operator++() {
        return *this += Value{1};
    }
    constexpr Value operator++(int) {
        Value temp{*this};
        ++(*this);
        return temp;
    }

    // Derived operator: decrement
    constexpr Value &operator--() {
        return *this -= Value{1};
    }
    constexpr Value operator--(int) {
        Value temp{*this};
        --(*this);
        return temp;
    }

    // Derived operator: subscript
    template<typename U>
    constexpr auto &operator[](Value<U> rhs) {
        return *(*this + rhs);
    }
};

template<typename T>
using Pointer = Value<T*>;

#endif //OPERATORS_VALUE_H
