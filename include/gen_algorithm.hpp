#pragma once
#include <random>
#include <chrono>
#include <vector>
#include <iostream>
#include <algorithm>
#include "individual.hpp"

class gen_algorithm {
private:
    unsigned population_size;
    unsigned mutation_probability;
    unsigned cross_probability;
    unsigned parm_t;
    unsigned lengthOfVector;
    unsigned iteration_count;
    unsigned parent_number;
    individual best_so_far;
    std::vector<individual> population;
    std::vector<individual> parents;

    void cross();
    void crossMethod(int method_number, int changed_element_number, int crossed_element_number, std::vector<std::vector<unsigned>> &vec);
    void mutate();
    unsigned generate_number();
    void gen_function();
    void fintess_calc();
    void selection();
    void initPopulation();
    void prepare_next_gen();

public:

    gen_algorithm();

    ~gen_algorithm();

    gen_algorithm(unsigned p_size, float m_probability, float c_probability, unsigned t, unsigned length_of_vector, unsigned iter_count, unsigned p_number);

    void show();

    void test();

    void start();
};