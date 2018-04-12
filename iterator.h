#pragma once

#include <iterator>
namespace my {
template <class Category, class T>
class Iterator 
{
public:
    typedef T value_type;
    typedef T* pointer;
    typedef T& reference;
    typedef Category iterator_category;
    typedef std::ptrdiff_t difference_type;

protected:
    Iterator() {}
    Iterator(const Iterator&) {}
    ~Iterator() {}
};

template<class T>
class RandomAccessIterator : public Iterator<std::random_access_iterator_tag, T> 
{
public:

    RandomAccessIterator() : m_current(nullptr) { }

    RandomAccessIterator(T* current) : m_current(current) { }

    T& operator* () 
    {
        return *m_current;
    }

    RandomAccessIterator& operator++ () 
    {
        ++m_current;
        return *this;
    }

    bool operator!= (const RandomAccessIterator& other) const 
    {
        return (m_current != other.m_current);
    }

private:
    T* m_current;
};
}
