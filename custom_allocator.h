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
    
    typename std::allocator<T>::pointer allocate(typename std::allocator<T>::size_type items_count) {
        typename std::allocator<T>::size_type old_size = size;
        size += items_count;
        
        if (old_size == 0)
        {
            std::cout << "sizeof(T) = " << sizeof(T) << std::endl;
        }
        
        if (size > capacity)
        {
            bool is_reallocation = data != nullptr;
            // [[maybe_unused]] std::size_t old_capacity = capacity;
            capacity = 2 * size + 1;
            std::cout << (is_reallocation ? "Reallocating: " : "Allocating ") << old_size + items_count << " items. " <<
            "Reserving " << capacity * sizeof(T) << " Bytes. " <<
            size << "/" << capacity << std::endl;
            
            if (void *reallocated_new_data = std::realloc(data, capacity * sizeof(T)))
            {
                data = reinterpret_cast<typename std::allocator<T>::pointer>(reallocated_new_data);
                reallocated_new_data = nullptr;
                if (is_reallocation)
                {
                    free(data);
                }
            }
            else
            {
                throw std::bad_alloc();
            }
            
            std::cout << "data = " << std::hex << data << std::endl;
            
            new_element_ptr = data + (old_size + items_count - 1); // calculate last element pointer
            for (int i = 0; i < (int)size; ++i)
            {
                [[maybe_unused]] void* current_element = reinterpret_cast<void*>(data + i);
                [[maybe_unused]] std::pair<const int, int>* smth = static_cast<std::pair<const int, int>*>(current_element);
                std::cout << "ptr[" << i << "] = " << std::hex << data + i << " " << smth->first << ":" << smth->second << std::endl;
            }
            std::cout << "new_element_ptr value: " << std::hex << new_element_ptr << std::endl;

            return new_element_ptr;
        }
        else
        {
            std::cout << "No need to reallocate, still in bounds: " << size << "/" << capacity << std::endl;
            new_element_ptr += items_count;
            for (int i = 0; i < (int)size; ++i)
            {
                [[maybe_unused]] void* current_element = reinterpret_cast<void*>(data + i);
                [[maybe_unused]] std::pair<const int, int>* smth = static_cast<std::pair<const int, int>*>(current_element);
                std::cout << "ptr[" << i << "] = " << std::hex << data + i << " " << smth->first << ":" << smth->second << std::endl;
            }
            std::cout << "new_element_ptr = " << std::hex << new_element_ptr << std::endl;
            return new_element_ptr;
        }
    }
    
    void deallocate(typename std::allocator<T>::pointer p, typename std::allocator<T>::size_type n) {
        std::cout << "Dealloc: " <<  n << " items" << std::endl;
        std::cout << "data = " << std::hex << data << " - " << std::hex << p << std::endl;
        if (p)
        {
            free(p);
        }
    }
    
    template<typename U>
    struct rebind {
        typedef custom_allocator<U> other;
    };
    
private:
    std::size_t size = 0;
    std::size_t capacity = 0;
    typename std::allocator<T>::pointer data = nullptr;
    typename std::allocator<T>::pointer new_element_ptr = nullptr;
};

#endif /* custom_allocator_h */
