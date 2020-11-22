#pragma once
#include <random>
#include <chrono>
#include <vector>
#include <iostream>

class gen_algorithm {
private:
    unsigned population_size;
    float mutation_probability;
    float cross_probability;
    unsigned parm_t;
    std::vector<std::vector<unsigned>> population;
    std::vector<unsigned> fitness;
    std::vector<unsigned> best_so_far;
    unsigned generation;
    unsigned lengthOfVector;
    unsigned best_fitnes_so_far;
    unsigned iteration_count;

    //std::vector<std::vector<unsigned>>* elements_to_new_population;

    void cross();
    void crossMethod(int method_number, int changed_element_number, int crossed_element_number, std::vector<std::vector<unsigned>> &vec);
    void mutate( int m);

    unsigned generate_number();

public:

    gen_algorithm();

    ~gen_algorithm();

    gen_algorithm(unsigned p_size, float m_probability, float c_probability, unsigned t, unsigned length_of_vector, unsigned iter_count);

    void gen_function();

    void fintess_calc();

    void selection();

    void initPopulation();

    void show();

    void test();

    void start();
};