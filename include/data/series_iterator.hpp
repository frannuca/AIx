//
// Created by Fran on 03.10.19.
//

#ifndef GLOBAL_SERIES_ITERATOR_HPP
#define GLOBAL_SERIES_ITERATOR_HPP
#include <iterator>

template<class K,class T>
class Series;

template<class K,class T>
class const_iterator{
public:
    typedef const_iterator self_type;
    typedef K value_type;
    typedef K& reference;
    typedef K* pointer;
    typedef ptrdiff_t difference_type;
    typedef std::forward_iterator_tag iterator_category;

    typedef const K& const_reference;

    const_iterator(pointer ptr) : ptr_(ptr) { }
    const_iterator& operator=(const const_iterator& that){
        this->ptr_ = that.ptr_;
        return *this;
    }

    self_type operator++() { self_type i = *this; ptr_++; return i; }
    self_type operator++(int junk) { ptr_++; return *this; }

    const_reference operator*() { return *ptr_; }
    const pointer operator->() { return ptr_; }
    bool operator==(const self_type& rhs) { return ptr_ == rhs.ptr_; }
    bool operator!=(const self_type& rhs) { return ptr_ != rhs.ptr_; }
private:
    pointer ptr_;
};

#endif //GLOBAL_SERIES_ITERATOR_HPP
