#define BOOST_TEST_MODULE test_main
#include <boost/test/unit_test.hpp>

#include "allocator.h"
#include "container.h"
#include "new_delete.h"

BOOST_AUTO_TEST_SUITE(allocator_test)



    BOOST_AUTO_TEST_CASE(my_container_custom_allocator_10) {
    my::alloc_counter = 0;
    my::container<int,  my::allocator< int , 10>> c2;
    for (int i = 0; i < 10; ++i) {
        c2.push(i);
    }
//   BOOST_CHECK(my::alloc_counter == 2u);
    BOOST_CHECK_EQUAL(my::alloc_counter, 2u);
}

// BOOST_AUTO_TEST_CASE(sdasd) {

// }


BOOST_AUTO_TEST_SUITE_END()
