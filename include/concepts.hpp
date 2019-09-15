#ifndef CONCEPTS_H
#define CONCEPTS_H
#include <utility>
#include <utility>
#include <boost/concept_check.hpp>
namespace AIX{namespace Concepts{

template<class T> struct HasLessThanOp;
template <class T>
struct HasLessThanOp {T a,b; BOOST_CONCEPT_USAGE(HasLessThanOp) { a < b; }};

template<class T> struct HasLessOrEqualThanOp;
template <class T>
struct HasLessOrEqualThanOp {T a,b; BOOST_CONCEPT_USAGE(HasLessOrEqualThanOp) { a <= b; }};


template<class T> struct HasGreaterThanOp;
template <class T>
struct HasGreaterThanOp {T a,b; BOOST_CONCEPT_USAGE(HasGreaterThanOp) { a > b; }};

template<class T> struct HasGreaterOrEqualThanOp;
template <class T>
struct HasGreaterOrEqualThanOp {T a,b; BOOST_CONCEPT_USAGE(HasGreaterOrEqualThanOp) { a >= b; }};

template<class T> struct HasAritmeticOp;
template <class T>
struct HasAritmeticOp {T a,b; BOOST_CONCEPT_USAGE(HasAritmeticOp) { a + b - a; }};

template<class T> struct HasProdandDivOp;
template <class T>
struct HasProdandDivOp {T a,b; BOOST_CONCEPT_USAGE(HasProdandDivOp) { a/b*a; }};


}}

#endif