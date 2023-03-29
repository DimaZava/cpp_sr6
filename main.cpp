#include <stddef.h>
#include <stdio.h>
#include <map>
#include "custom_allocator.h"

#define UNUSED(variable) (void)variable

static void print_map(const std::map<const int, int, std::less<int>, custom_allocator<std::pair<const int, int>>> &m) {
    for (auto element : m)
        std::cout << element.first << ":" << element.second << " ";
    std::cout << std::endl;
}

int main(int argc, char const *argv[])
{    
    std::map<const int, int, std::less<int>, custom_allocator<std::pair<const int, int> > > m;
    m.insert(std::pair<int,int>(1, 6));
    print_map(m);
    m.insert(std::pair<int,int>(2, 7));
    print_map(m);
    m.insert(std::pair<int,int>(3, 8));
    print_map(m);
    m.insert(std::pair<int,int>(4, 9));
    print_map(m);
    m.insert(std::pair<int,int>(5, 10));
    print_map(m);
    UNUSED(argc);
    UNUSED(argv);
    return 0;
}
