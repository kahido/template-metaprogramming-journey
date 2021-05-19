#pragma once

#include <iomanip>
#include <tuple>

// template<typename T>
// void PrintType()
// {
//     std::cout << std::endl << __PRETTY_FUNCTION__ << std::endl;
// }

// primary template
template<size_t INDEX, size_t LIMIT, typename... Types>
struct st_print_tuple
{
    static void print(std::ostream & os, const std::tuple<Types...> & tpl)
    {
        os << std::get<INDEX>(tpl) << (INDEX + 1 != LIMIT ? ", " : "");
        st_print_tuple<INDEX + 1, LIMIT, Types...>::print(os, tpl);
    }
};

// partial specialization
template<size_t INDEX, typename... Types>
struct st_print_tuple<INDEX, INDEX, Types...>
{
    static void print(std::ostream & /*os*/, const std::tuple<Types...> & /*tpl*/) {}
};

template<size_t INDEX, typename... Types>
void print_tuple(std::ostream & os, const std::tuple<Types...> & tpl)
{
    if constexpr (INDEX < sizeof...(Types)) { os << std::get<INDEX>(tpl); }

    if constexpr (INDEX + 1 < sizeof...(Types)) {
        os << ", ";
        print_tuple<INDEX + 1>(os, tpl);
    }
}

template<typename... Types>
std::ostream & operator<<(std::ostream & os, const std::tuple<Types...> & tpl)
{
    os << "{";
    // st_print_tuple<0, sizeof...(Types), Types...>::print(os, tpl);
    print_tuple<0>(os, tpl);
    os << "}";

    return os;
}

// CT_Loop acts as compile-time loop
template<size_t START, size_t END, typename Opr, typename... Types>
constexpr void CT_Loop(Opr operation, Types &&... args)
{
    if constexpr (START < END) { operation(std::forward<Types>(args)...); }

    if constexpr (START + 1 < END) { CT_Loop<START + 1, END>(operation, args...); }
}

void sum(int a, double b)
{
    std::cout << "sum(" << a << ", " << b << ") is called" << std::endl;
}

void pro(int a, double b, int c)
{
    std::cout << "pro(" << a << ", " << b << ", " << c << ") is called" << std::endl;
}

[[maybe_unused]] constexpr unsigned magic_age = 20;
[[maybe_unused]] constexpr unsigned magic_age_2 = 18;


[[maybe_unused]] constexpr unsigned magic_size_5 = 5;
[[maybe_unused]] constexpr unsigned magic_size_10 = 18;

[[maybe_unused]] constexpr int magic_a = 1;
[[maybe_unused]] constexpr double magic_b = 2.0;
[[maybe_unused]] constexpr int magic_c = 3;

void test_compile_time_loop()
{
    std::tuple<int, const char *> t{ magic_age, "Kahido" };

    std::cout << "age: " << std::get<0>(t) << std::endl;
    std::cout << "name: " << std::get<1>(t) << std::endl;

    std::cout << "age: " << std::get<int>(t) << std::endl;
    std::cout << "name: " << std::get<const char *>(t) << std::endl;

    // decltype(variable) returns the type of the variable
    // devltype(expression) returns the value category of the expression
    std::cout << "the element count of t = "
              << std::tuple_size_v<decltype(t)> << std::endl;

    std::cout << "t is " << t << std::endl;

    auto t2 = std::make_tuple(magic_age, 'F', "Sophie");

    auto [sophie_age, sophie_gender, sophie_name] = t2;

    // std::tuple_size<decltype(t2)::value == std::tuple_size_v<decltype(t2)>
    std::cout << "the element count of t = " << std::tuple_size<decltype(t2)>::value
              << std::endl;

    std::cout << std::endl;
    std::cout << "sophie_age: " << sophie_age << std::endl;
    std::cout << "sophie_gender: " << sophie_gender << std::endl;
    std::cout << "sophie_name: " << sophie_name << std::endl;

    std::cout << "t2 is " << t2 << std::endl;

    // structured binding
    auto & [s_age, s_gender, s_name] = t2;

    s_age = magic_age_2;

    std::cout << std::endl;
    std::cout << "s_age: " << std::get<0>(t2) << std::endl;
    std::cout << "s_gender: " << std::get<1>(t2) << std::endl;
    std::cout << "s_name: " << std::get<2>(t2) << std::endl;

    auto t3 = std::make_tuple("Kahido", "Programmer", "Playing Video Games", magic_age);

    // std::tuple_element_t<INDEX, tuple_type> return type of the INDEX-th element of
    // tuple_type
    //
    // PrintType<std::tuple_element_t<0, decltype(t3)>>();

    std::cout << "the element count of t = " << std::tuple_size<decltype(t3)>::value
              << std::endl;

    const char * t_name{};
    int t_age{};

    std::tie(t_name, std::ignore, std::ignore, t_age) = t3;

    std::cout << t_name << " is " << t_age << " old." << std::endl;

    std::cout << "t3 is " << t3 << std::endl;

    CT_Loop<0, magic_size_5>(sum, magic_a, magic_b);
    CT_Loop<0, magic_size_10>(pro, magic_a, magic_b, magic_c);
}
