#pragma once
//
//  make_unique.h
//  Program1
//


#ifndef Program1_make_unique_h
#define Program1_make_unique_h

#include <memory>
#include <utility>

// When assigning a value to type std::unique_ptr<T>, you should
// use
//    make_unique<T>()
// instead of
//    new T()
//
// This will be part of the C++14 standard.

template<typename T, typename ...Args>
std::unique_ptr<T> make_unique(Args&& ...args)
{
	return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

#endif

