/*
 * 00 - Basic - Function Templates
 *
 * Function Template represents a family of functions.
 *
 */

#include <iostream>
#include <type_traits>

constexpr char nl = '\n';

/*
 * Multiple Template Parameters
 *
 * 1. Template Parameters for Return Type
 */

namespace templ_rt {

// Return Type is set to 'double', T1 and T2 are deduced
template<typename RT, typename T1, typename T2>
RT max(T1 a, T2 b)
{
    return b < a ? a : b;
}

// Simpler version with one template parameter is much better. Return type and
// both parameters has aleready specified the same type!
template<typename T>
T max_simpler(T a, T b)
{
    return b < a ? a : b;
}

}// namespace templ_rt

/*
 * 2. Deducing Return Type
 */

namespace deduc_rt {

// Return Type is declared as 'auto' so compiler dicide what type it is.
// Better way is to declare that the Return Type is derived from trailing return type.
//
// This is a declaration, so that the compiler uses the rules of operator?:. The
// implementation does not necessarily have to match. Using 'true' as the condition for
// operator?: in the declaration is enough!
template<typename T1, typename T2>
auto max(T1 a, T2 b) -> decltype(true ? a : b)
{
    return b < a ? a : b;
}

// It may happen that the return type is a reference type. For this reason, Return Type
// should be decayed from T.
template<typename T1, typename T2>
auto max_decayed(T1 a, T2 b) -> std::decay_t<decltype(true ? a : b)>
{
    return b < a ? a : b;
}

}// namespace deduc_rt

/*
 * 3. Return Type as Common Type
 */

namespace common_rt {

// Note that std::common_type_t also decays, so that the return value can't become
// a reference
template<typename T1, typename T2>
std::common_type_t<T1, T2> max(T1 a, T2 b)
{
    return b < a ? a : b;
}

}// namespace common_rt

/*
 * Default Template Arguments
 */

namespace default_arg {

// You can define default arguments for template parameters. These may refer to prevous
// template parameters and be followed by parameters not having default arguments.
template<typename T1,
    typename T2,
    typename RT = std::decay_t<decltype(true ? T1() : T2())>>
RT max(T1 a, T2 b)
{
    return b < a ? a : b;
}

}// namespace default_arg

int main()
{
    /*
     * Multiple Template Parameters
     */

    // 1. Template Parameters for Return Type
    std::cout << "templ_rt::max<double> of (3, 8.1) = " << templ_rt::max<double>(3, 8.1)
              << nl;

    std::cout << "templ_rt::max_simpler of (3, 8.1) = "
              << templ_rt::max_simpler(static_cast<double>(3), 8.1) << nl;

    // 2. Deducing Return Type
    std::cout << "deduc_rt::max of (17, 2.3) = " << deduc_rt::max(17, 2.3) << nl;

    std::cout << "deduc_rt::max_decayed of (17, 2.3) = " << deduc_rt::max_decayed(17, 2.3)
              << nl;

    // 3. Return Type as Common Type
    std::cout << "common_rt::max of (20.1, 20) = " << common_rt::max(20.1, 20) << nl;

    /*
     * Default Template Arguments
     */
    std::cout << "default_arg::max of (3.0, 4) = " << default_arg::max(3.0, 4) << nl;

    return 0;
}
