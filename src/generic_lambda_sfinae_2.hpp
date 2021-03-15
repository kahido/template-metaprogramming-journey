#pragma once

#include <vector>
#include <deque>
#include <set>

// FIXME[kahido] Does not compile !!!!!!!!!

template<typename T>
struct BoxedType
{
};

// an instance of BoxedType<T>
template<typename T>
constexpr auto BoxedInstance = BoxedType<T>{};

// function without function body
template<typename T>
constexpr T StripBoxedType(BoxedType<T>);

template<typename T>
constexpr auto ElementInstance(BoxedType<T>)
    -> decltype(std::declval<typename T::value_type>());

// SFINAE out using this function without function body
template<typename LambdaType,
    typename... ArgTypes,
    typename = decltype(std::declval<LambdaType>()(std::declval<ArgTypes &&>()...))>
std::true_type is_implemented(void *);

// catch all function without function body
template<typename LmbdaType, typename... ArgTypes>
std::false_type is_implemented(...);

constexpr auto is_implementation_valid = [](auto lambda_instance) {
    return [](auto &&... lambda_args) {
        return decltype(
            is_implemented<decltype(lambda_instance), decltype(lambda_args) &&...>(
                nullptr)){};
    };
};

constexpr auto is_default_constructible_lambda =
    [](auto boxed_instance) -> decltype(decltype(StripBoxedType(boxed_instance))()) {};

constexpr auto is_default_constructible_helper =
    is_implementation_valid(is_default_constructible_lambda);

template<typename T>
constexpr bool is_default_constructible = is_default_constructible_helper(
    BoxedInstance<T>);

constexpr auto is_push_front_supported_lambda = [](auto boxed_instance)
    -> decltype(
        StripBoxedType(boxed_instance).push_front(ElementInstance(boxed_instance))) {};

constexpr auto is_push_front_supported_helper =
    is_implementation_valid(is_push_front_supported_lambda);

template<template<typename> class Cntr, typename T = int>
constexpr bool is_push_front_supported = is_push_front_supported_helper(
    BoxedInstance<Cntr<T>>);

class Constructible
{
public:
    Constructible() = default;
};

class NotConstructible
{
public:
    NotConstructible() = delete;
};

void test_lambda_sfinae_second()
{
    /////////////////////////////////////
    std::cout << std::endl;

    std::cout << "Does std::vector support push_front() ? " << std::boolalpha
              << is_push_front_supported<std::vector> << std::endl;

    std::cout << "Does std::vdeque support push_front() ? " << std::boolalpha
              << is_push_front_supported<std::deque> << std::endl;
}
