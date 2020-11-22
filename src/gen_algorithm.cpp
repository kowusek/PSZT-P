#include "gen_algorithm.hpp"

gen_algorithm::gen_algorithm() = default;

gen_algorithm::~gen_algorithm() = default;

gen_algorithm::gen_algorithm(unsigned p_size, float m_probability, float c_probability, unsigned t, unsigned length_of_vector, unsigned iter_count) {

    population_size = p_size;
    mutation_probability = m_probability;
    cross_probability = c_probability;
    parm_t = t;
    generation = 0;
    lengthOfVector = length_of_vector;
    best_fitnes_so_far = 0;
    iteration_count = iter_count;
}
void gen_algorithm::crossMethod(int method_number, int changed_element_number, int crossed_element_number)
{
    // int a = generate_number() % lengthOfVector;
    // int b = generate_number() % (lengthOfVector - a) + a;

    int a = generate_number() % lengthOfVector/2;
    int b = generate_number() % lengthOfVector/2 + lengthOfVector/2;

    //std::cout << " " << a <<" " << b << " " << crossed_element_number<< " tryb: " << method_number<< std::endl;

    std::vector<unsigned> tmp;

    switch (method_number)
    {
    case 0: // A b c

        for (int i = 0; i < a; i++)
        {
            tmp.push_back(population[crossed_element_number][i]);
        }
        for (int i = a; i < b; i++)
        {
            tmp.push_back(population[changed_element_number][i]);
        }
        for (unsigned i = b; i < lengthOfVector; i++)
        {
            tmp.push_back(population[changed_element_number][i]);
        }
        break;

    case 1: // a B c
        for (int i = 0; i < a; i++)
        {
            tmp.push_back(population[changed_element_number][i]);
        }
        for (int i = a; i < b; i++)
        {
            tmp.push_back(population[crossed_element_number][i]);
        }
        for (unsigned i = b; i < lengthOfVector; i++)
        {
            tmp.push_back(population[changed_element_number][i]);
        }
        break;

    case 2: // a b C
        for (int i = 0; i < a; i++)
        {
            tmp.push_back(population[changed_element_number][i]);
        }
        for (int i = a; i < b; i++)
        {
            tmp.push_back(population[changed_element_number][i]);
        }
        for (unsigned i = b; i < lengthOfVector; i++)
        {
            tmp.push_back(population[crossed_element_number][i]);
        }
        break;

    case 3: // A B c
        for (int i = 0; i < a; i++)
        {
            tmp.push_back(population[crossed_element_number][i]);
        }
        for (int i = a; i < b; i++)
        {
            tmp.push_back(population[crossed_element_number][i]);
        }
        for (unsigned i = b; i < lengthOfVector; i++)
        {
            tmp.push_back(population[changed_element_number][i]);
        }
        break;

    case 4: // A b C
        for (int i = 0; i < a; i++)
        {
            tmp.push_back(population[crossed_element_number][i]);
        }
        for (int i = a; i < b; i++)
        {
            tmp.push_back(population[changed_element_number][i]);
        }
        for (unsigned i = b; i < lengthOfVector; i++)
        {
            tmp.push_back(population[crossed_element_number][i]);
        }
        break;

    case 5: // a B C
        for (int i = 0; i < a; i++)
        {
            tmp.push_back(population[changed_element_number][i]);
        }
        for (int i = a; i < b; i++)
        {
            tmp.push_back(population[crossed_element_number][i]);
        }
        for (unsigned i = b; i < lengthOfVector; i++)
        {
            tmp.push_back(population[crossed_element_number][i]);
        }
        break;

    default:
        break;
    }

    population.push_back(tmp);
}

void gen_algorithm::cross()
{
    std::vector<int> parent_to_cross;

    for (unsigned i = 0; i < population_size; i++)
    {
        if (generate_number() % 100 < cross_probability)
        {
            parent_to_cross.push_back(i);
        }
    }

    if (parent_to_cross.size() == 1)
    { 
        int i = generate_number() % population_size;
        while(i == 0)
        {
            i = generate_number() % population_size;
        }
        crossMethod(generate_number() % 6, parent_to_cross[0], i);
    }
    else if (parent_to_cross.size() > 1)
    {
        for (unsigned i = 0; i < parent_to_cross.size(); i++)
        {
            unsigned x = parent_to_cross[generate_number() % parent_to_cross.size()];
            while(x == i)
            {
                x = parent_to_cross[generate_number() % parent_to_cross.size()];
            }
            
            crossMethod(generate_number() % 6, parent_to_cross[i], x);
        }
    }

    for (unsigned i = 0; i < parent_to_cross.size(); i++)
    {
        population[0].erase(population[0].begin() + parent_to_cross[i] - i);
    }
}

void gen_algorithm::mutate(int m)
{
    int x;
    for (unsigned i = 0; i < population_size; i++)
    {
        if (generate_number() % 100 < mutation_probability)
        {
            for (int a = 0; a < m; a++)
            {
                x = generate_number() % lengthOfVector;
                population[i][x] = (population[i][x] + 1) % 2;
            }
        }
    }
}

void gen_algorithm::gen_function()
{
}

void gen_algorithm::initPopulation()
{
    for (unsigned i = 0; i < population_size; i++)
    {
        std::vector<unsigned> tmp;
        for (unsigned x = 0; x < lengthOfVector; x++)
        {
            tmp.push_back(generate_number() % 2);
        }
        population.push_back(tmp);
    }
}

void gen_algorithm::show()
{
    for (unsigned i = 0; i < population_size; i++)
    {
        for (unsigned x = 0; x < lengthOfVector; x++)
        {
            std::cout << population[i][x] << " ";
        }
        std::cout << "   ";
    }
    std::cout << "\n";
}

unsigned gen_algorithm::generate_number()
{

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 generator(seed);
    return generator();
}

void gen_algorithm::fintess_calc() {

    std::vector<unsigned>::iterator i;
    std::vector<unsigned>::reverse_iterator j;
    std::vector<unsigned> temp;
    unsigned ones_score = 0;
    unsigned zeros_score = 0;
    unsigned score = 0;
    

    for( auto & individual : population ) {

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

            best_so_far = individual;
            best_fitnes_so_far = score;
        }

        temp.push_back(score);
    }

    fitness.clear();

    for( auto & i : temp ) {

        fitness.push_back(i);
    }
}

void gen_algorithm::selection() {

    unsigned number;
    unsigned sum;
    int count;
    std::vector<std::vector<unsigned>> temp;
    
    for( unsigned x = 0; x < population_size; ++x ) {

        number = generate_number() % population_size;
        sum = 0;
        count = 0;

        for( auto & i : fitness ) {

            if( ( sum += i ) > number ) {
                temp.push_back(population[count]);
                break;
            }
            count++;
        }
    }

    population.clear();

    for( auto & i : temp ) {

        population.push_back(i);
    }
}

void gen_algorithm::test()
{
    initPopulation();
    show();
    cross();
    show();
    mutate(3);
    show();
}

void gen_algorithm::start() {

    initPopulation();
    fintess_calc();
    for( unsigned i = 0; i < iteration_count; ++i ) {

        selection();
        //cross();
        mutate(2);
        fintess_calc();
        for (unsigned x = 0; x < lengthOfVector; x++)
        {
            std::cout << best_so_far[x] << " ";
        }
        std::cout << best_fitnes_so_far <<"\n";
    }
}