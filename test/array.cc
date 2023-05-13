#include "array.hpp"
#include <iostream>
#include <vector>
#include <ranges>

#define iterate(name, arr) \
    std::cout << name << ": "; \
    for (auto x : arr) std::cout << x << " ";\
    std::cout << "\n";

int main()
{
    // Test default constructor
    Array<int, 5> arr1;
    static_assert(std::ranges::range<decltype(arr1)>); //Is it iterable? 

    iterate("arr1", arr1);

    // Test fill() function
    arr1.fill(42);
    iterate("arr1", arr1);

    // Test single-value constructor
    Array<double, 3> arr2(1.23);
    iterate("arr2", arr2);

    // Test initializer list constructor
    Array<std::string, 4> arr3{"hello", "world", "foo", "bar"};
    iterate("arr3", arr3);

    // Test indexing and range checking
    std::cout << "arr3[0]: " << arr3[0] << "\n";
    std::cout << "arr3[3]: " << arr3[3] << "\n";
    try
    {
        std::cout << "arr3[4]: " << arr3[4] << "\n";
    }
    catch (const std::out_of_range& e)
    {
        std::cerr << "Caught exception: " << e.what() << "\n";
    }

    // Test const correctness
    const Array<int, 2> arr4{10, 20};
    iterate("arr4", arr4);

    try
    {
        // arr4[0] = 5; // should fail to compile
    }
    catch (const std::out_of_range& e)
    {
        std::cerr << "Caught exception: " << e.what() << "\n";
    }

    // Test iterator-based algorithms
    std::vector<int> vec{1, 2, 3, 4, 5};
    Array<int, 5> arr5;

    std::copy(vec.begin(), vec.end(), arr5.begin());
    iterate("arr5", arr5);

    std::reverse(arr5.begin(), arr5.end());
    iterate("arr5 (rev)", arr5);

    return 0;
}