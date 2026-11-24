#include "matrix/layout.hpp"
#include <iostream>

void print_offset(){
std::cerr << "Naive" << sizeof(Naive)
              << offsetof(Naive, a)
              << offsetof(Naive, b)
              << offsetof(Naive, c)
              << offsetof(Naive, d)
              << offsetof(Naive, e) << '\n';
std::cerr << "Packed sizeof " << sizeof(Packed)
              << offsetof(Packed, b)
              << offsetof(Packed, e)
              << offsetof(Packed, c)
              << offsetof(Packed, a)
              << offsetof(Packed, d) << '\n';
std::cerr << "Forced sizeof " << sizeof(Forced)
              << offsetof(Forced, a)
              << offsetof(Forced, b)
              << offsetof(Forced, c)
              << offsetof(Forced, d)
              << offsetof(Forced, e) << '\n';
}

