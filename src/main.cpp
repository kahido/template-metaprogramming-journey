#include <iostream>
#include <string>
// #include <utility>

// #include "sfinae_modulo.hpp"
// #include "template_recur_sum.hpp"
// #include "template_is_prime.hpp"
// #include "constexpr_is_prime.hpp"
// #include "compile_time_loop.hpp"
// #include "generic_lambda_sfinae_1.hpp"
// #include "generic_lambda_sfinae_2.hpp"
#include "type_name.hpp"

/*
    #include <functional>

    [out = std::ref(std::cout << "Hello ")]() { out.get() << "World\n"; }
    ();
*/

int main()
{
    int a = 0;

    std::cout << kk_GetTypeName<int>() << std::endl;

    // decltype(expression)
    // returns declared type of a expression
    // std::cout << type_to_string<decltype(a)>() << std::endl;
    std::cout << kk_GetTypeCategory(a) << std::endl;

    // decltype((expression))
    // returns value category of a expression
    // std::cout << type_to_string<decltype((a))>() << std::endl;
    std::cout << kk_GetValueCategory(a) << std::endl;

    return 1;
}
