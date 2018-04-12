#pragma once

#include <memory>
#include <cassert>
#include <iterator>

#include "iterator.h"

namespace my {


template< class T, class Allocator = std::allocator<T> >
class container 
{
public:
    typedef  T  value_type;
    typedef Allocator allocator_type;
    typedef std::size_t size_type;
    typedef std::ptrdiff_t difference_type;
    typedef typename Allocator::reference reference;
    typedef typename Allocator::const_reference const_reference;
    typedef typename Allocator::pointer pointer;
    typedef typename Allocator::const_pointer const_pointer;
    typedef  RandomAccessIterator<T> iterator;
    typedef  RandomAccessIterator<const T> const_iterator;

    container() : size(0), capacity(0), _begin(nullptr)  { }

    ~container() 
    {
        deallocate();
    }

    void deinitalize (pointer begin_, size_type count) 
    {
        for (; count > 0; --count, ++begin_)
            allocator.destroy(begin_);
    }

    void deallocate ()
    {
        deinitalize(_begin, size);
        allocator.deallocate(_begin, capacity);

        _begin = nullptr;
        size = capacity = 0;
    }

    size_type get_size() const 
    {
        return size;
    }

    size_type get_capacity() const {
        return capacity;
    }

    reference operator[] (size_type index) {
        assert(index < size);
        return _begin[index];
    }

    const_reference at(size_type index) const {
        assert(index < size);
        return _begin[index];
    }

    reference front() {
        assert (size > 0);
        return _begin[0];
    }

    const_reference front() const {
        assert (size > 0);
        return _begin[0];
    }

    reference back() {
        assert (size > 0);
        return _begin[size - 1];
    }

    const_reference back() const 
    {
        assert (size > 0);
        return _begin[size - 1];
    }

    iterator end()
    {
        return iterator(_begin + size);
    }

    iterator begin() 
    {
        return iterator(_begin);
    }

    void unitialized_copy (const_pointer begin, const_pointer end, pointer dest) 
    {
        for(; begin != end; ++begin, ++ dest)
            allocator.construct(dest, *begin);
    }

    void push_back(const T& value) 
    {
        if (size == capacity){
            size_type cap = capacity + 1;
            pointer begin_ = allocator.allocate(cap);

            unitialized_copy(_begin, _begin + size, begin_);

            deinitalize(_begin, size);
            allocator.deallocate(_begin, capacity);

            _begin = begin_;
            capacity = cap;
        }
        allocator.construct(_begin + size, value);
        ++size;
    }

    void push(const T& value) 
    {
        _begin = allocator.allocate(capacity);
        allocator.construct(_begin + size, value);
        ++size;
    }

    void pop_back() 
    {
        assert (size > 0);
        allocator.destroy(_begin + (size - 1));
        --size;
    }

    bool empty() {
        return (size == 0) ? true : false;
    }

    void reserve(size_type capacity_) 
    {
        if (capacity_ > capacity) {
            pointer begin_ = allocator.allocate(capacity_);
            unitialized_copy(_begin , _begin+ size, begin_);
            deallocate();
            _begin = begin_;
            capacity = capacity_;
        }
    }

    void clear () 
    {
        deinitalize(_begin, size);
        size = 0;
    }

private:

    Allocator allocator;
    size_type size = 0;
    size_type capacity = 0;
    pointer _begin = nullptr;

};

}
