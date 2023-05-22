/*
 * 01 - Basic - Class Templates
 *
 *
 */

#include <cassert>
#include <deque>
#include <iostream>
#include <type_traits>
#include <vector>

template<typename T>
class MyContainer
{
public:
    /*
     * Note taht this operator<< for class MyContainer<> is not a function template.
     * If we trying to 'declare' the friend function and 'define' it afterwards,
     * we have two options:
     *
     * 1. we can implicity declare a new function template, which must use a different
     * template parameter such as U:
     */
    template<typename U>
    friend std::ostream& operator<<(std::ostream&, MyContainer<U> const&);

    /*
     * 2. We can forward declare the output operator for a MyContainer<T> to be template, which,
     * however means that we first have to forward declare MyContainer<T>
     *
     * template<typename T>
     * class MyContainer;
     * template<typename T>
     * std::ostream& operator<<(std::ostream&, MyContainer<T> const&);
     *
     * Then, we can decare this function as friend
     */

    friend std::ostream& operator<<(std::ostream& strm, MyContainer<T> const& s)
    {
        s.printOn(strm);
        return strm;
    }

public:// Interface
    void push(T const& elem);

    void printOn(std::ostream& strm) const
    {
        for (T const& elem : elems)
        {
            strm << elem << ' ';// call '<<' for each element
        }
    }

private:// Members
    std::vector<T> elems;
};

template<typename T>
void MyContainer<T>::push(T const& elem)
{
    elems.push_back(elem);
}

/*
 * Specializations of Class Template
 *
 * Allows to optimize implementation or fix a misbehavior of certain types for an
 * instantation of the class template.
 * If you specialize a class template, you must also specialize all member functions.
 * Although it is possible to specialize a single member function of a class template.
 * Then you can no longer specialize the whole class template instance that the
 * specialized member belongs to.
 */

template<>
class MyContainer<std::string>
{
public:
    void push(std::string const& /*elem*/);

private:
    std::deque<std::string> elems = {};
};

void MyContainer<std::string>::push(std::string const& elem)
{
    elems.push_back(elem);
}

void simple_stack_construction()
{
    auto intStack = MyContainer<int>{};
    auto stringStack = MyContainer<std::string>{};

    intStack.push(42);
    stringStack.push("some-value");
}

/*
 * MyContainer is created as an object that uses a vector of T's as elements
 * and, for all member functions that are `CALLED`, code for this type is instantiated.
 *
 * Code is instantiated only for template (member) functions that are called.
 */

void partial_useage()
{
    // std::pair<> has no operator<< defined
    auto ps = MyContainer<std::pair<int, int>>{};

    ps.push({ 42, 18 });
    ps.push({ 1, 2 });

    // ps.printOn(std::cout); // won't compile!
}

/*
 * Partial Specializations
 *
 * Special implementation for particular circumstances, but some template parameters must
 * still be defined by the user. We can define special implementation of class MyContainer<>
 * for pointers.
 */
template<typename T>
class MyContainer<T*>
{
public:
    void push(T* /*elem*/);
    [[nodiscard]] T* pop();

private:
    std::vector<T*> elems = {};
};

template<typename T>
void MyContainer<T*>::push(T* elem)
{
    elems.push_back(elem);
}
//
// Specialization might provide (slighty) different interface. Here we return last element
// as a pointer.
template<typename T>
T* MyContainer<T*>::pop()
{
    assert(!elems.empty());
    T* p = elems.back();
    elems.pop_back();
    return p;// return last element (unlike in the general code)
}

void partial_specialization()
{
    auto ptrStack = MyContainer<int*>{};

    ptrStack.push(new int{ 42 });
    delete ptrStack.pop();
}

/*
 * Partial Specializations with Multiple Parameters
 *
 */

// Primary Class Template
template<typename T1, typename T2>
class MultiClass
{
};

// Partial Specialization Class Template
template<typename T>
class MultiClass<T, T>
{
};

template<typename T>
class MultiClass<T, int>
{
};

// Two pointers with different type
template<typename T1, typename T2>
class MultiClass<T1*, T2*>
{
};

void partial_specialization_multiple_params()
{
    [[maybe_unused]] auto mif = MultiClass<int, float>{}; // uses <T1, T2>
    [[maybe_unused]] auto mff = MultiClass<float, float>{}; // uses <T, T>
    [[maybe_unused]] auto mfi = MultiClass<float, int>{}; // uses <T, int>
    [[maybe_unused]] auto mp = MultiClass<int*, float*>{}; // uses <T1*, T2*>
}

int main()
{
    simple_stack_construction();
    partial_useage();
    partial_specialization();
    partial_specialization_multiple_params();

    return 0;
}
