#include <memory>

// Predefined operators:
// Cast
// sizeof
// Dereference
// Ternary
// Subtraction -

template<typename T, typename U>
U operator,(T, U rhs) { return std::forward(rhs); }

template<typename T>
class Assign {
public:
    // Assumes operators: cast (T* to void*), dereference
    constexpr Assign& operator=(const T& rhs) { return *(new (this) Assign{rhs}); }
    constexpr Assign& operator=(T&& rhs) { return *(new (this) Assign{std::move(rhs)}); }
};

template<typename T>
class Logical : public Assign<T> {
public:
    static constexpr T True = T{true};
    static constexpr T False = T{false};

    // Assumes operators: cast (T to/from bool), ?:
    // Also assumes values True and False defined in scope
    friend constexpr T operator!(T value) { return value ? True : False; }

    friend constexpr T operator&&(T lhs, T rhs) { return lhs ? rhs : False; }
    friend constexpr T operator||(T lhs, T rhs) { return lhs ? True : rhs; }
    friend constexpr T operator==(T lhs, T rhs) { return lhs ? rhs : !rhs; }
    friend constexpr T operator!=(T lhs, T rhs) { return !(lhs == rhs); }
};

class Bool : public Logical<Bool> {
private:
    bool value_;

public:
    Bool() = default;
    constexpr explicit Bool(bool value) : value_{value} {}

    constexpr explicit operator bool() const { return value_; }
};

template<typename T>
class Subtract {
public:
    // Assumes subtraction, cast (int to T)
    // Also assumes copy assignment
    friend constexpr T operator-(T value) { return T{0} - value; }
    friend constexpr T operator+(T value) { return value; }

    template<typename U>
    friend constexpr T& operator-=(T& lhs, U rhs) { return lhs -= rhs; }
    template<typename U>
    friend constexpr T& operator+=(T& lhs, U rhs) { return lhs -= -rhs; }

    template<typename U>
    friend constexpr auto operator+(T lhs, U rhs) { return lhs - -rhs; }

    template<typename U>
    friend constexpr T& operator++(T& value) { return value += T{1}; }
    template<typename U>
    friend constexpr T& operator++(T& value, int) { T temp{value}; ++value; return temp; }

    template<typename U>
    friend constexpr T& operator--(T& value) { return value -= T{1}; }
    template<typename U>
    friend constexpr T& operator--(T& value, int) { T temp{value}; --value; return temp; }
};

template<typename T>
class Unsigned : public Subtract<T>, Assign<T> {
public:
    // Assumes: subtraction, cast to Bool (means test for non-zero), cast from int

    friend constexpr Bool operator<(T lhs, T rhs) {
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

    friend Bool operator>(T lhs, T rhs) {
        return rhs < lhs;
    }
    friend Bool operator<=(T lhs, T rhs) {
        return !(lhs > rhs);
    }
    friend bool operator>=(T lhs, T rhs) {
        return !(lhs < rhs);
    }

    friend constexpr Bool operator==(T lhs, T rhs) {
        // lhs == rhs iff (lhs-1) == (rhs-1).
        // Continue decrementing until one or another is false (i.e. zero)
        while(static_cast<Bool>(lhs) && static_cast<Bool>(rhs)) {
            --lhs;
            --rhs;
        }
        // One or other if lhs and rhs is false (i.e. 0)
        // lhs and rhs are equal iff both are false (i.e. zero)
        return !static_cast<Bool>(lhs) && !static_cast<Bool>(rhs);
    }
    friend constexpr Bool operator!=(T lhs, T rhs) {
        return !(lhs == rhs);
    }

    friend constexpr T operator*(T lhs, T rhs)  {
        T product{0};
        while (rhs > 0) {
            product += lhs;
            --rhs;
        }
        return product;
    }

    friend constexpr T& operator*=(T& lhs, T rhs)  {
        return lhs = (lhs * rhs);
    }

    friend constexpr T operator/(T lhs, T rhs)  {
        T ratio{0};
        while (lhs > rhs) {
            lhs -= rhs;
            ++ratio;
        }
        return ratio;
    }

    friend constexpr T& operator/=(T& lhs, T rhs) {
        return lhs = (lhs / rhs);
    }

    friend constexpr T operator%(T lhs, T rhs) {
        return lhs - rhs * (lhs / rhs);
    }

    friend constexpr T& operator%=(T& lhs, T rhs) {
        return lhs = (lhs % rhs);
    }

    friend constexpr T& operator<<=(T& lhs, T rhs) {
        while (rhs-- > 0)
            lhs *= T{2};

        return lhs;
    }

    friend constexpr T operator<<(T lhs, T rhs) {
        return lhs <<= rhs;
    }

    friend constexpr T& operator>>=(T& lhs, T rhs) {
        while (rhs-- > 0)
            lhs /= T{2};

        return lhs;
    }

    friend constexpr T operator>>(T lhs, T rhs) {
        return lhs >>= rhs;
    }

    friend constexpr T operator~(T value) {
        return T{-1} - value;
    }

    friend constexpr T operator&(T lhs, T rhs) {
        T result{0};
        T bit{1};
        while(lhs && rhs) {
            if ((lhs % T{2}) && (rhs % T{2}))
                result += bit;

            bit <<= 1;
            lhs >>= 1;
            rhs >>= 1;
        }

        return result;
    }

    friend constexpr T& operator&=(T& lhs, T rhs) {
        return lhs = (lhs & rhs);
    }

    friend constexpr T operator|(T lhs, T rhs) {
        T result{0};
        T bit{1};
        while(lhs && rhs) {
            if ((lhs % T{2}) || (rhs % T{2}))
                result += bit;

            bit <<= 1;
            lhs >>= 1;
            rhs >>= 1;
        }

        return result;
    }

    friend constexpr T& operator|=(T& lhs, T rhs) {
        return lhs = (lhs | rhs);
    }

    friend constexpr T operator^(T lhs, T rhs) {
        T result{0};
        T bit{1};
        while(lhs && rhs) {
            if ((lhs % T{2}) != (rhs % T{2}))
                result += bit;

            bit <<= 1;
            lhs >>= 1;
            rhs >>= 1;
        }

        return result;
    }

    friend constexpr T& operator^(T& lhs, T rhs) {
        return lhs = (lhs ^ rhs);
    }
};

Signed!!!