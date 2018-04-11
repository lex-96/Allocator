#include <map>
#include <iostream>
#include <algorithm>
#include <iterator>

#include "allocator.h"
#include "container.h"

constexpr int factorial (int n) {
    return n > 0 ? n * factorial(n - 1) : 1;
}

int main()
{
    auto make_factorial_value = [i=0] () mutable
    {
        auto f = factorial(i);
        auto value = std::make_pair(i,f);
        ++i;
        return value;
    };

    auto m1 = std::map<int, int>{ };
    std::generate_n( std::inserter(m1, std::begin(m1)), 10, make_factorial_value );

   auto m2 = std::map<int, int, std::less<int>, my::allocator<std::pair<const int, int>, 10> >{ };
    std::generate_n( std::inserter(m2, std::begin(m2)), 10, make_factorial_value );

    for (const auto& p : m2) {
        std::cout << p.first << ' ' << p.second << std::endl;
    }

    my::container<int> c1;
   // c1.reserve(10);
    for (int i = 0; i < 10; ++i)
        c1.push_back(i);


    my::container<int,  my::allocator< int , 10>> c2;
    for (int i = 0; i < 10; ++i)
        c2.push(i);
    for (const auto& e: c2)
        std::cout << e << std::endl;

    return 0;
}

