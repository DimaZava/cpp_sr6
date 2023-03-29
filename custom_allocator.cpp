//
//  custom_allocator.cpp
//  main
//
//  Created by Dmitrii Zavadskii on 24.03.2023.
//

#include <typeinfo>
#include <iostream>
#include "custom_allocator.h"

//inline typename std::allocator<T>::pointer custom_allocator::allocate(typename std::allocator<T>::size_type n,
//                                                    typename std::allocator<void>::const_pointer = 0) {
//    std::cout << "Allocating: " << n << " items." << std::endl;
//    return reinterpret_cast<typename std::allocator<T>::pointer>(::operator new(n * sizeof (T)));
//}
//
//inline void custom_allocator::deallocate(typename std::allocator<T>::pointer p,
//                       typename std::allocator<T>::size_type n) {
//    std::cout << "Dealloc: " <<  n << " items." << std::endl;
//    ::operator delete(p);
//}
//
//template<typename U>
//struct rebind {
//    typedef custom_allocator<U> other;
//};
