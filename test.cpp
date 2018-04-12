#define BOOST_TEST_MODULE test_main
#include <boost/test/unit_test.hpp>

#include <map>

#include "allocator.h"
#include "container.h"
#include "new_delete.h"
#include "factorial.h"

BOOST_AUTO_TEST_SUITE(allocator_test)

BOOST_AUTO_TEST_CASE(my_container_custom_allocator_10)
{
    my::malloc_counter = 0;
    my::container<int,  my::allocator< int , 10>> c2;

    for (int i = 0; i < 10; ++i) {
        c2.push(i);
    }
    BOOST_CHECK_EQUAL(my::malloc_counter, 2u);
}

 BOOST_AUTO_TEST_CASE(my_container)
 {
     my::malloc_counter = 0;
     my::container<int> c1;

     for (int i = 0; i < 10; ++i) {
         c1.push_back(i);
     }
     int i = 0;
     for(const auto& e : c1) {
         BOOST_CHECK_EQUAL(e, i++);
     }
     BOOST_CHECK_EQUAL(my::malloc_counter, 10u);
 }

 BOOST_AUTO_TEST_CASE(my_container_reserve)
 {
     my::malloc_counter = 0;
     my::container<int> c3;
     c3.reserve(10);

     for (int i = 0; i < 10; ++i) {
         c3.push_back(i);
     }
     int i = 0;
     for(const auto& e : c3) {
         BOOST_CHECK_EQUAL(e, i++);
     }
     BOOST_CHECK_EQUAL(my::malloc_counter, 1u);
 }

 BOOST_AUTO_TEST_CASE(map_with_my_alloc)
 {
     my::malloc_counter = 0;
     auto m = std::map<int, int, std::less<int>, my::allocator<std::pair<const int, int>, 10> >{ };

     int i = 0;
     while( i < 10) {
         m[i] = factorial(i++);
     }
//     i = 0;
//     for(const auto& p : m) {
//         BOOST_CHECK_EQUAL(p.first, i);
//         BOOST_CHECK_EQUAL(p.second, factorial(i++));
//     }
//     BOOST_CHECK_EQUAL(my::malloc_counter, 2u);
 }

BOOST_AUTO_TEST_SUITE_END()
