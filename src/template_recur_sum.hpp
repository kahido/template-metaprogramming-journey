#pragma once

#include <iostream>

unsigned sum_loop(unsigned n)
{
    unsigned s = 0;
    for (unsigned i = n; i > 0; --i) { s += i; }

    return s;
}

unsigned sum_recursion(unsigned n)
{
    unsigned ret = 1;

    if (n < 2) {// n = 1
        ret = 1;// escape clause
    } else// recursive clause
    {// n = 2, 3, 4, ...
        ret = n + sum_recursion(n - 1);
    }

    return ret;
}

// primary template class
// recursive clause
template<unsigned n> // non-type template parameter
struct st_sum// n = 2, 3, 4, ...
{
    static const unsigned value = n + st_sum<n - 1>::value;
};

// full specialization of template class
// escape clause
template<> struct st_sum<1>// n = 1
{
    static const unsigned value = 1;
};


[[maybe_unused]] constexpr int sum_loop_1 = 10;

void non_type_template_recursion()
{
    std::cout << "Loop function: 1 + ... + 10 = " << sum_loop(sum_loop_1) << std::endl;
    std::cout << "Recursion function: 1 + ... + 10 = " << sum_recursion(sum_loop_1)
              << std::endl;
    std::cout << "Non-type template class: 1 + ... + 10 = " << st_sum<sum_loop_1>::value
              << std::endl;
}
