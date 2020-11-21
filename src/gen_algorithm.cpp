#include "gen_algorithm.hpp"

gen_algorithm::gen_algorithm() = default;

gen_algorithm::~gen_algorithm() = default;

gen_algorithm::gen_algorithm(unsigned p_size, float m_probability, float c_probability, unsigned t, unsigned length_of_vector) {

    population_size = p_size;
    mutation_probability = m_probability;
    cross_probability = c_probability;
    population = new std::vector<std::vector<unsigned>>;
    fitness = new std::vector<unsigned>;
    best_so_far = NULL;
    parm_t = t;
    generation = 0;
    lengthOfVector = length_of_vector;
    best_so_far = new std::vector<unsigned>;
    best_fitnes_so_far = 0;
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

        if( best_fitnes_so_far < score ) {

            *best_so_far = individual;
            best_fitnes_so_far = score;
        }

        fitness->push_back(score);
    }
}

void gen_algorithm::selection() {

    unsigned number;
    std::vector<std::vector<unsigned>>::iterator i;
    std::vector<unsigned>::iterator j;
    unsigned sum;
    std::vector<std::vector<unsigned>>* temp = new std::vector<std::vector<unsigned>>;
    
    for( unsigned x = 0; x < population_size - 1; ++x ) {

        number = generate_number();
        //std::cout << number << std::endl;
        number = number % population_size;
        sum = 0;


        for( i = population->begin(), j = fitness->begin(); i != population->end(); ++i, ++j ) {

                if( ( sum += *j ) > number )
                    temp->push_back(*i);
        }
    }

    temp->push_back(*best_so_far);
    population = temp;
}

void gen_algorithm::initPopulation()
{
    for(unsigned i = 0; i < population_size; i++)
    {
        std::vector<unsigned> tmp;
        for(unsigned x = 0; x < lengthOfVector; x++)
        {
            tmp.push_back(generate_number() % 2);
        }
        population->push_back(tmp);
    }
}

void gen_algorithm::show()
{
    for(unsigned i = 0; i < population_size; i++)
    {
        for(unsigned x = 0; x < lengthOfVector; x++)
        {
            std::cout << population[0][i][x] << " ";
        }
        std::cout << "   ";
    }
    std::cout << "\n";
}