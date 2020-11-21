#include "gen_algorithm.hpp"

gen_algorithm::gen_algorithm() = default;

gen_algorithm::~gen_algorithm() = default;

gen_algorithm::gen_algorithm(unsigned p_size, float m_probability, float c_probability, unsigned t, unsigned length_of_vector) {

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
    int a = generate_number() % population[0][0].size() / 2;
    int b = generate_number() % population[0][0].size() / 2 + population[0][0].size();
    int tmpSize = lengthOfVector;

    switch (method_number)
    {
    case 0: // A b c
        population[changed_element_number].insert(population[changed_element_number].end(), population[crossed_element_number].begin(), population[crossed_element_number].begin() + a);
        population[changed_element_number].insert(population[changed_element_number].end(), population[changed_element_number].begin() + a + 1, population[changed_element_number].end());
        population[changed_element_number].erase(population[changed_element_number].begin(), population[changed_element_number].begin() + tmpSize);
        break;

    case 1: // a B c
        population[changed_element_number].insert(population[changed_element_number].end(), population[changed_element_number].begin(), population[changed_element_number].begin() + a);
        population[changed_element_number].insert(population[changed_element_number].end(), population[crossed_element_number].begin() + a + 1, population[crossed_element_number].begin() + b);
        population[changed_element_number].insert(population[changed_element_number].end(), population[changed_element_number].begin() + b + 1, population[crossed_element_number].end());
        population[changed_element_number].erase(population[changed_element_number].begin(), population[changed_element_number].begin() + tmpSize);      
        break;

    case 2: // a b C
        population[changed_element_number].insert(population[changed_element_number].end(), population[changed_element_number].begin(), population[changed_element_number].begin() + b);
        population[changed_element_number].insert(population[changed_element_number].end(), population[crossed_element_number].begin() + b + 1, population[crossed_element_number].end());
        population[changed_element_number].erase(population[changed_element_number].begin(), population[changed_element_number].begin() + tmpSize);
        break;

    case 3: // A B c
        population[changed_element_number].insert(population[changed_element_number].end(), population[crossed_element_number].begin(), population[crossed_element_number].begin() + b);
        population[changed_element_number].insert(population[changed_element_number].end(), population[changed_element_number].begin() + b + 1, population[changed_element_number].end());
        population[changed_element_number].erase(population[changed_element_number].begin(), population[changed_element_number].begin() + tmpSize);
        break;

    case 4: // A b C
        population[changed_element_number].insert(population[changed_element_number].end(), population[crossed_element_number].begin(), population[crossed_element_number].begin() + a);
        population[changed_element_number].insert(population[changed_element_number].end(), population[changed_element_number].begin() + a + 1, population[changed_element_number].begin() + b);
        population[changed_element_number].insert(population[changed_element_number].end(), population[crossed_element_number].begin() + b + 1, population[crossed_element_number].end());
        population[changed_element_number].erase(population[changed_element_number].begin(), population[changed_element_number].begin() + tmpSize);
        break;

    case 5: // a B C
        population[changed_element_number].insert(population[changed_element_number].end(), population[changed_element_number].begin(), population[changed_element_number].begin() + a);
        population[changed_element_number].insert(population[changed_element_number].end(), population[crossed_element_number].begin() + a + 1, population[crossed_element_number].end());
        population[changed_element_number].erase(population[changed_element_number].begin(), population[changed_element_number].begin() + tmpSize);
        break;
    
    default:
        break;
    }
}

void gen_algorithm::cross()
{
    std::vector<int> parent_to_cross;

    for(int i = 0; i < population_size_to_cross; i++)
    {
        if(generate_number() % 100 < cross_probability)
        {
            parent_to_cross.push_back(i);
        }
    }

    if(parent_to_cross.size () == 1)
    {
        int i = generate_number() % population_size_to_cross;
        crossMethod(generate_number() % 6, parent_to_cross[0], i);
    }
    else if (parent_to_cross.size () > 1)
    {
        for(int i = 0; i < parent_to_cross.size(); i++)
        {
            crossMethod(generate_number() % 6, parent_to_cross[i], parent_to_cross[generate_number() % parent_to_cross.size()]);
        }
    }

}

void gen_algorithm::mutate(int m)
{
    int x;
    for(int i = 0; i < population_size_to_cross; i++)
    {
        //std::cout << "jestem";
        if(generate_number() % 100 < mutation_probability)
        {
            for(int a = 0; a < m; a++)
            {
                x = generate_number() % lengthOfVector;
                population[0][i][x] = (population[0][i][x] + 1 ) % 2;
                //population[0][i][x] += 5;
            }
        }
        //population[0][i][0] += 5;
    }
    //population[0][1][0] += 5;
}


void gen_algorithm::gen_function() {


}

void gen_algorithm::initPopulation()
{
    for(int i = 0; i < population_size; i++)
    {
        std::vector<unsigned> tmp;
        for(int x = 0; x < lengthOfVector; x++)
        {
            tmp.push_back(generate_number() % 2);
        }
        population->push_back(tmp);
    }
}

void gen_algorithm::show()
{
    for(int i = 0; i < population_size; i++)
    {
        for(int x = 0; x < lengthOfVector; x++)
        {
            std::cout << population[0][i][x] << " ";
        }
        std::cout << "   ";
    }
    std::cout << "\n";
}

unsigned gen_algorithm::generate_number() {

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 generator( seed );
    return generator();
}

void gen_algorithm::test()
{
    initPopulation();
    population_size_to_cross = population_size;
    show();
    cross();
    show();
    mutate(3);
    show();
}