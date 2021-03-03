#pragma once

// simple primality test
// this algorithm is inefficient
bool is_prime_loop(unsigned p)
{
    bool ret = true;

    if (p < 4)// p = 0, 1, 2, 3
    {
        ret = (p > 1);// p = 2 or 3, then we return true
    } else {
        // p = 4, 5 ,6, ...
        unsigned half_p = p / 2;
        // d = p/2, ..., 3, 2 (the least d is 2)
        for (unsigned d = half_p; d > 1; --d) {
            if (p % d == 0)// p is divisile by d
            {
                return false;// p is not prime
            }
        }

        return true;// p is not divisible by 2, 3, ..., p/2
    }

    return ret;
}

bool _is_prime_recu(unsigned p, unsigned d)
{
    bool ret = true;

    if (d == 2) {// escape clause -> specialization
        ret = (p % d != 0);// p is not divisible by d, then return true
    } else {
        /*
         * Rule 1:
         *
         * if (true_condition)
         *      return true_expr;
         * else
         *      return false_expr;
         *
         * return (true_condition ? true_expr : false_expr);
         *
         *
         */
        // d is greater than 2
        // if (p % d != 0)// p is not divisible by d
        // {
        //     ret = _is_prime_recu(p, --d);
        // } else {
        //     // p is divisible by d
        //     return false;
        // }

        // return (p%d != 0 ? _is_prime_recu(p, --d) : false);

        /*
         * Rule 2:
         *
         * if (true_condition)
         *      return true_expr;
         * elss
         *      return false;
         *
         * return true_condition && true_expr;
         *
         */

        // recursive clause -> primary template
        return (p % d != 0) && _is_prime_recu(p, --d);
    }

    return ret;
    // return (d == 2 ? (p % d != 0) : (p % d != 0) && _is_prime_recu(p, --d));
}

bool is_prime_recursion(unsigned p)
{
    bool ret = true;

    if (p < 4)// excape clause -> specialization
              // p = 0, 1, 2, 3
    {
        ret = (p > 1);// p = 2 or 3, then we return true
    } else {
        // recursive clause -> primary template
        // p is 4, 5, 6, ...
        return _is_prime_recu(p, p / 2);
    }

    return ret;
}

// primary template
// recursive clause of recursive function
template<unsigned p, unsigned d> struct st_is_prime_recu
{
    /*
     * (p%d != 0) && _is_prime_recu(p, --d);
     *
     * p and d are template parameters.
     * we cannot change template parameters
     * so --d is incorerect, instead us d-1
     */
    static const bool value = (p % d) && st_is_prime_recu<p, d - 1>::value;
};

// escape clause to specialization
template<unsigned p> struct st_is_prime_recu<p, 2>
{
    static const bool value = (p % 2 != 0);
};

// primary template
// when we translate recursive function
// to template class, recursive clause becomes primary template
template<unsigned p> struct st_is_prime
{
    static const bool value = st_is_prime_recu<p, p / 2>::value;
};

template<> struct st_is_prime<3>
{
    static const bool value = true;
};

template<> struct st_is_prime<2>
{
    static const bool value = true;
};

template<> struct st_is_prime<1>
{
    static const bool value = true;
};

template<> struct st_is_prime<0>
{
    static const bool value = false;
};

void test_is_prime(unsigned limit)
{
    for (unsigned p = 1; p <= limit; ++p) {
        std::cout << std::setw(3) << p << " is "
                  << (is_prime_loop(p) ? "Yes, Prime" : "No") << std::endl;
    }
}

void test_is_prime_recursion(unsigned limit)
{
    for (unsigned p = 1; p <= limit; ++p) {
        std::cout << std::setw(3) << p << " is "
                  << (is_prime_recursion(p) ? "Yes, Prime" : "No") << std::endl;
    }
}

[[maybe_unused]] constexpr unsigned magic_prime_t = 7;

void test_st_is_prime()
{
    std::cout << std::setw(3) << 1 << " is "
              << (st_is_prime<1>::value ? "Yes, Prime" : "No") << std::endl;
    std::cout << std::setw(3) << magic_prime_t << " is "
              << (st_is_prime<magic_prime_t>::value ? "Yes, Prime" : "No") << std::endl;
}

[[maybe_unused]] constexpr unsigned magic_prime = 25;
