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
        
        if (old_size == 0)
        {
            std::cout << "sizeof(T) = " << sizeof(T) << std::endl;
        }
        
        if (size > capacity)
        {
            [[maybe_unused]] std::size_t old_capacity = capacity;
            capacity = 2 * size + 1;
            std::cout << (old_size > 0 ? "Reallocating: " : "Allocating ") << old_size + items_count << " items. " <<
            "Reserving " << capacity * sizeof(T) << " Bytes. " <<
            size << "/" << capacity << std::endl;
            pointer new_data = reinterpret_cast<pointer>(::operator new(capacity));
            std::memmove(new_data, data, old_capacity * sizeof(T)); // Copy existing data to the extended memory region
            // std::memcpy(new_data, data, old_capacity * sizeof(T));
            // std::copy(data, data + old_capacity * sizeof(T), new_data);
            ::operator delete(data); // deallocate unused memory
            
            data = new_data; // move data pointer to the newly marked memory region
            std::cout << "data = " << std::hex << data << std::endl;
            new_data = nullptr; // clean up
            
            new_element_ptr = data + (old_size + items_count - 1); // calculate last element pointer
            for (int i = 0; i < (int)size; ++i)
                std::cout << "ptr[" << i << "] = " << std::hex << data + i << std::endl;
            std::cout << "new_element_ptr value: " << std::hex << new_element_ptr << std::endl;

            return new_element_ptr;
        }
        else
        {
            std::cout << "No need to reallocate, still in bounds: " << size << "/" << capacity << std::endl;
            new_element_ptr += items_count;
            for (int i = 0; i < (int)size; ++i)
                std::cout << "ptr[" << i << "] = " << std::hex << data + i << std::endl;
            std::cout << "new_element_ptr = " << std::hex << new_element_ptr << std::endl;
            return new_element_ptr;
        }
    }
    
    void deallocate(pointer p, size_type n) {
        std::cout << "Dealloc: " <<  n << " items" << std::endl;
        std::cout << "data = " << std::hex << data << " - " << std::hex << p << std::endl;
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
    pointer new_element_ptr = nullptr;
};

#endif /* custom_allocator_h */
