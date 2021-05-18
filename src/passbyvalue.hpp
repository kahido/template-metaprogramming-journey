#include <iostream>
#include <type_traits>

template<typename T>
constexpr bool is_const_reference
    = std::is_reference_v<T> && std::is_const_v<std::remove_reference_t<T>>;

template<typename T>
auto sum(T a, T b) // pass by value, but we can control the type of T at call site
{
    if constexpr(std::is_pointer_v<T>)
    {
        std::cout << "Type of T is pointer" << std::endl;
    
        auto s = *a;
        auto e = *b;
        decltype(s) result{};

        for (auto i = s; i <= e; ++i)
        {
            result += i;
        }

        return result;
    }
    else // neither a nor b is pointer
    {
        if constexpr(std::is_reference_v<T>)
        {
            if constexpr(std::is_lvalue_reference_v<T>)
            {
                if constexpr(is_const_reference<T>)
                {
                    std::cout << "T is const lvalue reference" << std::endl;
                }
                else
                {
                    std::cout << "T is non-const lvalue reference" << std::endl;
                }
            }
            else
            {
                std::cout << "T is rvalue reference" << std::endl;
            }
        }
        else
        {
            std::cout << "T is neither pointer nor reference" << std::endl;
        }

        // decltype(a+a) is compile-time expression (or called const expression)
        // this line of code does not cause any overhead at run-time
        auto result = decltype(a+a){};

        for (auto i = a; i <= b; ++i)
        {
            result += i;
        }

        return result;
    }
}

void test_pass_by_value()
{
    int a = 1;
    int b = 10;
    int c = 100;

    std::cout << sum(a, b) << std::endl; // call by value
    std::cout << sum(&a, &b) << std::endl; // call by pointer
    std::cout << sum<int&>(a, b) << std::endl; // call by lvalue reference
    std::cout << sum<const int&>(a, b) << std::endl; // call by const lvalue reference
    std::cout << sum<int&&>(1, 10) << std::endl; // call by rvalue reference
    std::cout << sum<int&&>(std::move(a), std::move(b)) << std::endl; // move local variables
    std::cout << sum<int&&>(1, std::move(c)) << std::endl; // pass prvalue, and move local variable
}
