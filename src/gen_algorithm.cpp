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
    generation = 0;
}

void gen_algorithm::cross()
{

}

void gen_algorithm::mutate()
{
    
}


void gen_algorithm::gen_function() {


}

unsigned gen_algorithm::generate_number() {

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 generator( seed );
    return generator();
}

void gen_algorithm::fintess_calc() {

    std::vector<unsigned>::iterator i;
    std::vector<unsigned>::reverse_iterator j;
    unsigned ones_score = 0;
    unsigned zeros_score = 0;
    unsigned score = 0;
    

    for( auto & individual : *population ) {

        ones_score = 0;
        zeros_score = 0;
        score = 0;
        
        for( i = individual.begin(); i != individual.end(); ++i ) {

            if( *i == 0 )
                break; 
            else 
                ++ones_score;        
        }
    
        for( j = individual.rbegin(); j != individual.rend(); ++j ) {
        
            if( *j == 1 )
                break; 
            else 
                ++zeros_score; 
        }

        if( zeros_score >= parm_t && ones_score >= parm_t )
            score += 100;

        score += std::max(ones_score, zeros_score);

        fitness->push_back(score);
    }
}