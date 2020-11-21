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
    unsigned lengthOfVector;

public:
    unsigned best_fitnes_so_far;
    gen_algorithm();

    ~gen_algorithm();

    gen_algorithm(unsigned p_size, float m_probability, float c_probability, unsigned t, unsigned length_of_vector);

    void gen_function();

    unsigned generate_number();

    void fintess_calc();

    void selection();

    void initPopulation();

    void show();
};