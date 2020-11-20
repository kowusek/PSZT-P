#include "gen_algorithm.hpp"

gen_algorithm::gen_algorithm() = default;

gen_algorithm::~gen_algorithm() = default;

gen_algorithm::gen_algorithm(unsigned p_size, float m_probability, float c_probability, unsigned t) {

    population_size = p_size;
    mutation_probability = m_probability;
    cross_probability = c_probability;
    population = new std::vector<std::vector<unsigned>>;
    best_so_far = NULL;
    parm_t = t;
}

void gen_algorithm::gen_function() {


}

unsigned gen_algorithm::generate_number() {

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 generator( seed );
    return generator();
}