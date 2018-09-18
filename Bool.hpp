#ifndef OPERATORS_BOOL_HPP
#define OPERATORS_BOOL_HPP

#include "Value.hpp"
#include <tuple>

using Bool = Value<bool>;

static constexpr Bool True = Bool{true};
static constexpr Bool False = Bool{false};

// Derived operator: ?:
// But it is not legal c++ to override it so we must pretend
template<typename T>
constexpr T /*operator?:*/if_else(Bool b, T ifTrue, T ifFalse) {
    if (b)
        return std::forward<T>(ifTrue);
    else
        return std::forward<T>(ifFalse);
};

// Derived operator: Logical negation (NOT)
constexpr Bool operator!(Bool lhs) {
    return lhs ? False : True;
}

// Derived operator: equality
constexpr Bool operator==(Bool lhs, Bool rhs) {
    return lhs ? rhs : !rhs;
}

// Derived operator: inequality
constexpr Bool operator!=(Bool lhs, Bool rhs) {
    return lhs ? !rhs : rhs;
}

// Derived operator: Logical AND
constexpr Bool operator&&(Bool lhs, Bool rhs) {
    return lhs ? rhs : False;
}

// Derived operator: Logical OR
constexpr Bool operator||(Bool lhs, Bool rhs) {
    return lhs ? True : rhs;
}

#endif //OPERATORS_BOOL_HPP
