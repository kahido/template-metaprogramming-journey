#include <iostream>
#include "typefunc.hpp"

/*
 *
 * Immediate Context
 *   Function template - Validity of the template parameter list
 *                       Validity of the function signature
 *
 */

template<typename T, typename = integer_t<T>>// this SFINAE out any non-integral types
class Modulo
{
private:
    T m_mem = T{};

public:
    explicit Modulo(T m = T{}) : m_mem{ m } {}

    /*
     * We want to impelement operator % only for integral type
     * We have to break the tie between the class template and operator% member function
     */

    // SFINAE out any non-integral type of S
    // or, if S is not integral type,
    // then this function disappears at compile time
    // template<typename S, typename = integer_t<S>>
    // same_t<S, T> operator%(S m)
    // {
    //     return (this->m_mem % m);
    // }

    template<typename S, typename = integer_t<S>>
    enable_true_t<is_same_v<S, T>, S> operator%(S m)
    {
        return (this->m_mem % m);
    }

    friend std::ostream & operator<<(std::ostream & os, const Modulo & m)
    {
        os << m.m_mem;
        return os;
    }
};

[[maybe_unused]] constexpr int magic_1 = 5;
[[maybe_unused]] constexpr int magic_2 = 3;
[[maybe_unused]] constexpr double magic_3 = 3.0;
[[maybe_unused]] constexpr unsigned int magic_4 = 3;

void sfinae_modulo()
{
    auto mod = Modulo{ magic_1 };

    std::cout << mod << "%" << magic_2 << "=" << (mod % magic_2) << std::endl;
}
