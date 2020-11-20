#include <iostream>
#include "../include/gen_algorithm.hpp"

int main() {
    
    gen_algorithm gen(10, 01, 05, 1);
    std::cout << gen.generate_number() << std::endl;
}