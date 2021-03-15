#pragma once

#include <type_traits>

// primary template class
template<typename T>
struct st_integer
{
    static const bool value = false;
};

// full specialization for template class
template<>// "full spacialization" means template<> is used
struct st_integer<int>
{
    static const bool value = true;
    using type = int;
};

// full specialization for template class
template<>// "full spacialization" means template<> is used
struct st_integer<unsigned int>
{
    static const bool value = true;
    using type = unsigned int;
};

// value template using constexpr keyword
template<typename T>
constexpr bool is_integer = st_integer<T>::value;

// using tempalte - type alias
template<typename T>
using integer_t = typename st_integer<T>::type;

// primary class type
template<typename T1, typename T2>
struct st_same_type
{
    static const bool value = false;
};

// partial specialization
template<typename T>// "partial" means we still need template parameter
struct st_same_type<T, T>
{
    static const bool value = true;
    using type = T;
};

// value template
template<typename T1, typename T2>
constexpr bool is_same_v = st_same_type<T1, T2>::value;

// using template - type alias
template<typename T1, typename T2>
using same_t = typename st_same_type<T1, T2>::type;

// primary class template
// if we want to initialize template parameter
// then we have to provide default parameter
// at primary class template
template<bool TEST, typename RType>
struct st_enable_true
{
    static const bool value = TEST;
};

// partial specialization
template<typename RType>
struct st_enable_true<true, RType>
{
    static const bool value = true;
    using type = RType;
};

template<bool TEST, typename RType>
using enable_true_t = typename st_enable_true<TEST, RType>::type;
