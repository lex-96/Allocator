#pragma once

#include "new_delete.h"
#include <memory>
#include <vector>
#include <array>

namespace my {

template <typename T, size_t capacity = 64>
class allocator
{
    static_assert(capacity != 0, "no zero capacity!");

private:
    std::vector<std::vector<std::array<unsigned char, sizeof(T)>>> pool;
    std::size_t index = 0;

public:
    using value_type = T;
    typedef T*         pointer;
    typedef const T*   const_pointer;
    typedef T&         reference;
    typedef const T&   const_reference;

    template <class U> struct rebind { using other =  allocator<U, capacity>; };


    allocator() = default;
    template< class U >
    allocator( const allocator<U, capacity>& other ){};

    T* allocate(std::size_t n)
    {
        pool.resize(1 + index/capacity);
        pool[index/capacity].resize(capacity);
        T* p = reinterpret_cast<T*>(&pool[index/capacity][index%capacity]);
        index += n;
        return p;
    }

    void deallocate(T*, std::size_t)
    {
    }

    template<typename U, typename ... Args>
    void construct( U* p, Args&&... args )
    {
        new(p) U(std::forward<Args>(args)...);
    }

    void destroy(T * p)
    {
        p->~T();
    }
};

}
