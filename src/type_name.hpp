#ifndef _KAHIDO_TYPE_NAME_HPP
#define _KAHIDO_TYPE_NAME_HPP

#include <type_traits>
#include <typeinfo>

namespace kahido {

template<typename T>
std::string type_to_string()
{
#if defined(_MSC_VER)
    std::string type_name(__FUNSIG__);
    auto start_pos =
        type_name.find_first_of('<', std::string(typeid(std::string).name()).size());
    auto end_pos = type_name.find_last_of('>');
    return type_name.substr(start_pos, (end_pos - start_pos));
#elif defined(__clang__)
    std::string type_name(static_cast<const char *>(__PRETTY_FUNCTION__));
    auto start_pos = type_name.find_first_of('=') + 2;
    auto end_pos = type_name.find_first_of(']', start_pos);
    return type_name.substr(start_pos, (end_pos - start_pos));
#elif defined(__GNUC__)
    std::string type_name(static_cast<const char *>(__PRETTY_FUNCTION__));
    auto start_pos = type_name.find_first_of('=') + 2;
    auto end_pos = type_name.find_first_of(';', start_pos);
    return type_name.substr(start_pos, (end_pos - start_pos));
#else
    return "Failed to Convert to String";
#endif
}

} // namespace kahido

// #define kk_GetTypeName(type_name) type_to_string<type_name>()
// #define kk_GetTypeCategory(type_instance) type_to_string<decltype(type_instance)>();
// #define kk_GetValueCategory(type_instance) type_to_string<decltype((type_instance))>();

template<typename T>
constexpr auto kk_GetTypeName()
{
    return kahido::type_to_string<T>();
}

template<typename T>
constexpr auto kk_GetTypeCategory(T type_instance)
{
    return kahido::type_to_string<decltype(type_instance)>();
}

template<typename T>
constexpr auto kk_GetValueCategory(T type_instance)
{
    return kahido::type_to_string<decltype((type_instance))>();
}

#endif // _KAHIDO_TYPE_NAME_HPP
