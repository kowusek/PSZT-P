#pragma once
#include <random>
#include <chrono>
#include <vector>
#include <iostream>
#include "individual.hpp"

class gen_algorithm {
private:
    unsigned population_size;
    unsigned mutation_probability;
    unsigned cross_probability;
    unsigned parm_t;
    unsigned lengthOfVector;
    unsigned iteration_count;
    std::vector<individual> population;

    void cross();
    void crossMethod(int method_number, int changed_element_number, int crossed_element_number, std::vector<std::vector<unsigned>> &vec);
    void mutate();
    unsigned generate_number();
    void gen_function();
    void fintess_calc();
    void selection();
    void initPopulation();

public:

    gen_algorithm();

    ~gen_algorithm();

    gen_algorithm(unsigned p_size, float m_probability, float c_probability, unsigned t, unsigned length_of_vector, unsigned iter_count);

    void show();

    void test();

    void start();
};