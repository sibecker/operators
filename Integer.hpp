#ifndef OPERATORS_INTEGER_HPP
#define OPERATORS_INTEGER_HPP

#include "Bool.hpp"

using UnsignedInt = Value<unsigned int>;
using Int = Value<int>;
using UnsignedChar = Value<unsigned char>;
using Char = Value<char>;

constexpr UnsignedInt operator "" _U(unsigned long long l) { return static_cast<UnsignedInt>(Value{l}); }
constexpr Int operator "" _I(unsigned long long l) { return static_cast<Int>(Value{l}); }
constexpr UnsignedChar operator "" _U(char c) { return static_cast<UnsignedChar>(Value{c}); }
constexpr Char operator "" _C(char c) { return Char{c}; }
constexpr Value<const char*> operator "" _S(const char* s, std::size_t) { return Value<const char*>{s}; }

// Derived operator: less-than (unsigned types)
template<typename T>
constexpr std::enable_if_t<std::is_unsigned_v<T>, Bool>
operator<(Value<T> lhs, Value<T> rhs) {
    // lhs < rhs iff (lhs-1) < (rhs-1).
    // Continue decrementing until one or another is false (i.e. zero)
    while(static_cast<Bool>(lhs) && static_cast<Bool>(rhs)) {
        --lhs;
        --rhs;
    }

    // One or other of lhs and rhs is 0.
    // If rhs == 0 then lhs cannot be < rhs
    // If rhs != 0 then rhs > 0 (unsigned) therefore lhs == 0 and so lhs < rhs
    return static_cast<Bool>(rhs);
}

// Derived operator: greater-than
template<typename T>
constexpr std::enable_if_t<std::is_integral_v<T>, Bool>
operator>(Value<T> lhs, Value<T> rhs) {
    return rhs < lhs;
}

// Derived operator: less-than-or-equal
template<typename T>
constexpr std::enable_if_t<std::is_integral_v<T>, Bool>
operator<=(Value<T> lhs, Value<T> rhs) {
    return !(lhs > rhs);
}

// Derived operator: greater-than-or-equal
template<typename T>
constexpr std::enable_if_t<std::is_integral_v<T>, Bool>
operator>=(Value<T> lhs, Value<T> rhs) {
    return !(lhs < rhs);
}

// Derived operator: equal
template<typename T>
constexpr std::enable_if_t<std::is_integral_v<T>, Bool>
operator==(Value<T> lhs, Value<T> rhs) {
    // lhs < rhs iff (lhs-1) < (rhs-1).
    // Continue decrementing until one or another is false (i.e. zero)
    while(static_cast<Bool>(lhs) && static_cast<Bool>(rhs)) {
        --lhs;
        --rhs;
    }

    // One or other of lhs and rhs is 0.
    // If rhs == 0 then lhs cannot be < rhs
    // If rhs != 0 then rhs > 0 (unsigned) therefore lhs == 0 and so lhs < rhs
    return static_cast<Bool>(lhs) == static_cast<Bool>(rhs);
}

// Derived operator: not-equal
template<typename T>
constexpr std::enable_if_t<std::is_integral_v<T>, Bool>
operator!=(Value<T> lhs, Value<T> rhs) {
    return !(lhs == rhs);
}

#endif //OPERATORS_INTEGER_HPP
