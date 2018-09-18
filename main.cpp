#include "Integer.hpp"

int main() {
    Value<const char*> str = "Which"_S;
    Char c = Char{str[0_I]};

    Pointer<Int> p = new Int{7};
    Int x = *p;
    x = x;
    delete static_cast<Int*>(p);

    return static_cast<int>(x);
}
/*
// Predefined operators:
// Cast
// sizeof
// Dereference
// Ternary
// Subtraction -

template<typename T>
class Unsigned : public Subtract<T>, Assign<T> {
public:
    // Assumes: subtraction, cast to Bool (means test for non-zero), cast from int

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

Signed!!!*/
