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
    std::vector<std::vector<unsigned>>* population;
    std::vector<unsigned>* best_so_far;

    int population_size_to_cross;
    unsigned lengthOfVector;

    //std::vector<std::vector<unsigned>>* elements_to_new_population;

    void cross();
    void crossMethod(int method_number, int changed_element_number, int crossed_element_number);
    void mutate( int m);

    unsigned generate_number();

    void initPopulation();

public:
    gen_algorithm();

    ~gen_algorithm();

    gen_algorithm(unsigned population_size, float mutation_probability, float cross_probability, unsigned t, unsigned lenght_of_vector);

    void gen_function();

    void test();

    void show();

};