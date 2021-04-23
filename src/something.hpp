
struct ObjectA
{};

struct ObjectB
{};

// constexpr ObjectA ObjectAInstance = ObjectA{};

template<typename T>
struct is_object_A
{
    static const bool value = false;
};

template<>
struct is_object_A<ObjectA>
{
    static const bool value = true;
    using type = ObjectA;
};

template<typename T>
using object_A_t = typename is_object_A<T>::type;

template<typename T, typename = typename is_object_A<T>::type>
void printOk()
{
    std::cout << "Hey! We got print for ObjectA!\n";
    std::cout << "Blah\n";
}
