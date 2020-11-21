#pragma once
#include <random>
#include <chrono>
#include <vector>
#include <iostream>

class gen_algorithm {
private:
    void cross();
    void mutate();

    unsigned population_size;
    float mutation_probability;
    float cross_probability;
    unsigned parm_t;
    std::vector<std::vector<unsigned>>* population;
    std::vector<unsigned>* fitness;
    std::vector<unsigned>* best_so_far;
    unsigned generation;

public:
    gen_algorithm();

    ~gen_algorithm();

    gen_algorithm(unsigned population_size, float mutation_probability, float cross_probability, unsigned t);

    void gen_function();

    unsigned generate_number();

    void fintess_calc();
};