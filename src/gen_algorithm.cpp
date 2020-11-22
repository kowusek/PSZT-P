#include "gen_algorithm.hpp"

gen_algorithm::gen_algorithm() = default;

gen_algorithm::~gen_algorithm() = default;

gen_algorithm::gen_algorithm(unsigned p_size, float m_probability, float c_probability, unsigned t, unsigned length_of_vector, unsigned iter_count, unsigned p_number ) {

    population_size = p_size;
    mutation_probability = m_probability;
    cross_probability = c_probability;
    parm_t = t;
    lengthOfVector = length_of_vector;
    iteration_count = iter_count;
    parent_number = p_number;
}
void gen_algorithm::crossMethod(int method_number, int changed_element_numberP, int crossed_element_numberP, std::vector<std::vector<unsigned>> &vec)
{
    int x = generate_number() % lengthOfVector;
    int y, a, b;
    do
    {
        y = generate_number() % lengthOfVector;
    } while (y == x);
    
    if(x > y)
    {
        a = y;
        b = x;
    }
    else
    {
        a = x;
        b = y;
    }

    //int a = generate_number() % lengthOfVector/2;
    //int b = (generate_number() % lengthOfVector/2) + lengthOfVector/2;

    //std::cout << " " << a <<" " << b << " " << crossed_element_number<< " tryb: " << method_number<< std::endl;

    std::vector<unsigned> tmp;
    std::vector<unsigned> changed_element_number = population[changed_element_numberP].get_gene();
    std::vector<unsigned> crossed_element_number = population[crossed_element_numberP].get_gene();

    switch (method_number)
    {
    case 0: // A b c

        for (int i = 0; i < a; i++)
        {
            tmp.push_back(crossed_element_number[i]);
        }
        for (int i = a; i < b; i++)
        {
            tmp.push_back(changed_element_number[i]);
        }
        for (unsigned i = b; i < lengthOfVector; i++)
        {
            tmp.push_back(changed_element_number[i]);
        }
        break;

    case 1: // a B c
        for (int i = 0; i < a; i++)
        {
            tmp.push_back(changed_element_number[i]);
        }
        for (int i = a; i < b; i++)
        {
            tmp.push_back(crossed_element_number[i]);
        }
        for (unsigned i = b; i < lengthOfVector; i++)
        {
            tmp.push_back(changed_element_number[i]);
        }
        break;

    case 2: // a b C
        for (int i = 0; i < a; i++)
        {
            tmp.push_back(changed_element_number[i]);
        }
        for (int i = a; i < b; i++)
        {
            tmp.push_back(changed_element_number[i]);
        }
        for (unsigned i = b; i < lengthOfVector; i++)
        {
            tmp.push_back(crossed_element_number[i]);
        }
        break;

    case 3: // A B c
        for (int i = 0; i < a; i++)
        {
            tmp.push_back(crossed_element_number[i]);
        }
        for (int i = a; i < b; i++)
        {
            tmp.push_back(crossed_element_number[i]);
        }
        for (unsigned i = b; i < lengthOfVector; i++)
        {
            tmp.push_back(changed_element_number[i]);
        }
        break;

    case 4: // A b C
        for (int i = 0; i < a; i++)
        {
            tmp.push_back(crossed_element_number[i]);
        }
        for (int i = a; i < b; i++)
        {
            tmp.push_back(changed_element_number[i]);
        }
        for (unsigned i = b; i < lengthOfVector; i++)
        {
            tmp.push_back(crossed_element_number[i]);
        }
        break;

    case 5: // a B C
        for (int i = 0; i < a; i++)
        {
            tmp.push_back(changed_element_number[i]);
        }
        for (int i = a; i < b; i++)
        {
            tmp.push_back(crossed_element_number[i]);
        }
        for (unsigned i = b; i < lengthOfVector; i++)
        {
            tmp.push_back(crossed_element_number[i]);
        }
        break;

    default:
        break;
    }

    vec.push_back(tmp);
}

void gen_algorithm::cross()
{
    std::vector<int> parent_to_cross;
    std::vector<std::vector<unsigned>> vec;

    for (unsigned i = 0; i < population.size(); i++)
    {
        if (generate_number() % 100 < cross_probability)
        {
            parent_to_cross.push_back(i);
        }
        else
        {
            vec.push_back(population[i].get_gene());
        }
        population[0].get_gene();
    }

    if (parent_to_cross.size() == 1)
    { 
        int i = generate_number() % population.size();
        while(i == 0)
        {
            i = generate_number() % population.size();
        }
        crossMethod(generate_number() % 6, parent_to_cross[0], i, vec);
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
            
            crossMethod(generate_number() % 6, parent_to_cross[i], x, vec);
        }
    }

    for(int i = 0; i < vec.size(); i++)
    {
        population[i].set_gene(vec[i]);
    }

    //population.clear();
    //population = vec;
    //for()

}

void gen_algorithm::mutate()
{
    for(unsigned i = 0; i < population_size; i++)
    {
        std::vector<unsigned> tmp = population[i].get_gene();
        for (unsigned x = 0; x < lengthOfVector; x++)
        {
            if (generate_number() % 100 < mutation_probability)
            {
                tmp[x] = (tmp[x] + 1) % 2;
            }
        }
        population[i].set_gene(tmp);
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
        individual ind;
        ind.set_gene(tmp);
        population.push_back(ind);
    }
}

void gen_algorithm::show() // don't work
{
    for (unsigned i = 0; i < population_size; i++)
    {
        for (unsigned x = 0; x < lengthOfVector; x++)
        {
            //std::cout << population[i][x] << " ";
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
        
        for( auto i = individual.get_gene().begin(); i != individual.get_gene().end(); ++i ) {

            if( *i == 0 )
                break; 
            else 
                ++ones_score;        
        }
    
        for( auto j = individual.get_gene().rbegin(); j != individual.get_gene().rend(); ++j ) {
        
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
    std::sort(population.begin(), population.end());
}

void gen_algorithm::selection() {

    unsigned number;
    unsigned sum;
    int count;
    std::vector<std::vector<unsigned>> temp;
    
    for( unsigned x = 0; x < population_size - parent_number; ++x ) {

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

    for( unsigned x = 0; x < parent_number; ++x ) {

        parents.push_back(population[x]);
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
    mutate();
    show();
}

void gen_algorithm::start() {

    initPopulation();
    fintess_calc();
    for( unsigned i = 0; i < iteration_count; ++i ) {

        selection();
        cross();
        //show();
        mutate();
        prepare_next_gen();
        fintess_calc();
        std::cout << population[0];
    }
}

void gen_algorithm::prepare_next_gen() {

    for( auto & i : parents ) {

        population.push_back(i);
    }

    parents.clear();
}