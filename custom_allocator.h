//
//  custom_allocator.hpp
//  main
//
//  Created by Dmitrii Zavadskii on 24.03.2023.
//

#ifndef custom_allocator_hpp
#define custom_allocator_hpp

#include <stdio.h>
#include <typeinfo>
#include <iostream>
#include <algorithm>
#include <map>

template <typename T>
class custom_allocator : public std::allocator<T> {
public:
    typedef T value_type;
    typedef size_t size_type;
    typedef T* pointer;
    typedef const T* const_pointer;
    typedef T& reference;
    typedef const T& const_reference;
    
    pointer allocate(size_type items_count) {
        size_type old_size = size;
        size += items_count;
        
        if (size > capacity)
        {
            [[maybe_unused]] std::size_t old_capacity = capacity;
            capacity = 2 * size + 1;
            std::cout << (old_size > 0 ? "Reallocating: " : "Allocating ") << old_size << " items. " <<
            "Reserving " << capacity * sizeof(T) << " Bytes. " <<
            size << "/" << capacity << std::endl;
            pointer new_data = reinterpret_cast<pointer>(::operator new(capacity));
            std::memmove(new_data, data, old_capacity * sizeof(T)); // Copy existing data to the extended memory region
            // std::copy(data, data + old_capacity * sizeof(T), new_data);
            ::operator delete(data); // deallocate unused memory
            
            data = new_data; // move data pointer to the newly marked memory region
            std::cout << "Pointer value: " << std::hex << data << std::endl;
            new_data = nullptr; // clean up
            
            last_element = data + (old_size + items_count) * sizeof(T); // calculate last element pointer
            std::cout << "last_element value: " << std::hex << last_element << std::endl;
            return last_element;
        }
        else
        {
            std::cout << "No need to reallocate, still in bounds: " << size << "/" << capacity << std::endl;
            last_element += items_count * sizeof(T);
            std::cout << "last_element value: " << std::hex << last_element << std::endl;
            return last_element;
        }
    }
    
    void deallocate(pointer p, size_type n) {
        std::cout << "Dealloc: " <<  n << " items" << std::endl;
        std::cout << "Pointer value: " << std::hex << data << " - " << std::hex << p << std::endl;
        ::operator delete(p);
    }
    
    template<typename U>
    struct rebind {
        typedef custom_allocator<U> other;
    };
    
private:
    std::size_t size = 0;
    std::size_t capacity = 0;
    pointer data = nullptr;
    pointer last_element = nullptr;
};

#endif /* custom_allocator_h */
