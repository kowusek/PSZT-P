#include "gen_algorithm.hpp"

gen_algorithm::gen_algorithm() = default;

gen_algorithm::~gen_algorithm() = default;

gen_algorithm::gen_algorithm(unsigned p_size, float m_probability, float c_probability, unsigned t, unsigned length_of_vector)
{

    population_size = p_size;
    mutation_probability = m_probability;
    cross_probability = c_probability;
    population = new std::vector<std::vector<unsigned>>;
    best_so_far = NULL;
    parm_t = t;
    lengthOfVector = length_of_vector;
}
void gen_algorithm::crossMethod(int method_number, int changed_element_number, int crossed_element_number)
{
    // int a = generate_number() % lengthOfVector;
    // int b = generate_number() % (lengthOfVector - a) + a;

    int a = generate_number() % lengthOfVector/2;
    int b = generate_number() % lengthOfVector/2 + lengthOfVector/2;

    std::cout << " " << a <<" " << b << " " << crossed_element_number<< " tryb: " << method_number<< std::endl;

    std::vector<unsigned> tmp;

    switch (method_number)
    {
    case 0: // A b c

        for (int i = 0; i < a; i++)
        {
            tmp.push_back(population[0][crossed_element_number][i]);
        }
        for (int i = a; i < b; i++)
        {
            tmp.push_back(population[0][changed_element_number][i]);
        }
        for (unsigned i = b; i < lengthOfVector; i++)
        {
            tmp.push_back(population[0][changed_element_number][i]);
        }
        break;

    case 1: // a B c
        for (int i = 0; i < a; i++)
        {
            tmp.push_back(population[0][changed_element_number][i]);
        }
        for (int i = a; i < b; i++)
        {
            tmp.push_back(population[0][crossed_element_number][i]);
        }
        for (unsigned i = b; i < lengthOfVector; i++)
        {
            tmp.push_back(population[0][changed_element_number][i]);
        }
        break;

    case 2: // a b C
        for (int i = 0; i < a; i++)
        {
            tmp.push_back(population[0][changed_element_number][i]);
        }
        for (int i = a; i < b; i++)
        {
            tmp.push_back(population[0][changed_element_number][i]);
        }
        for (unsigned i = b; i < lengthOfVector; i++)
        {
            tmp.push_back(population[0][crossed_element_number][i]);
        }
        break;

    case 3: // A B c
        for (int i = 0; i < a; i++)
        {
            tmp.push_back(population[0][crossed_element_number][i]);
        }
        for (int i = a; i < b; i++)
        {
            tmp.push_back(population[0][crossed_element_number][i]);
        }
        for (unsigned i = b; i < lengthOfVector; i++)
        {
            tmp.push_back(population[0][changed_element_number][i]);
        }
        break;

    case 4: // A b C
        for (int i = 0; i < a; i++)
        {
            tmp.push_back(population[0][crossed_element_number][i]);
        }
        for (int i = a; i < b; i++)
        {
            tmp.push_back(population[0][changed_element_number][i]);
        }
        for (unsigned i = b; i < lengthOfVector; i++)
        {
            tmp.push_back(population[0][crossed_element_number][i]);
        }
        break;

    case 5: // a B C
        for (int i = 0; i < a; i++)
        {
            tmp.push_back(population[0][changed_element_number][i]);
        }
        for (int i = a; i < b; i++)
        {
            tmp.push_back(population[0][crossed_element_number][i]);
        }
        for (unsigned i = b; i < lengthOfVector; i++)
        {
            tmp.push_back(population[0][crossed_element_number][i]);
        }
        break;

    default:
        break;
    }

    population[0].push_back(tmp);
}

void gen_algorithm::cross()
{
    std::vector<int> parent_to_cross;

    for (int i = 0; i < population_size; i++)
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
    for (int i = 0; i < population_size; i++)
    {
        if (generate_number() % 100 < mutation_probability)
        {
            for (int a = 0; a < m; a++)
            {
                x = generate_number() % lengthOfVector;
                population[0][i][x] = (population[0][i][x] + 1) % 2;
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
        population->push_back(tmp);
    }
}

void gen_algorithm::show()
{
    for (unsigned i = 0; i < population_size; i++)
    {
        for (unsigned x = 0; x < lengthOfVector; x++)
        {
            std::cout << population[0][i][x] << " ";
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

void gen_algorithm::test()
{
    initPopulation();
    show();
    cross();
    show();
    mutate(3);
    show();
}