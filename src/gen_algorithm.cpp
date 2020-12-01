#include "gen_algorithm.hpp"

gen_algorithm::gen_algorithm() = default;

gen_algorithm::~gen_algorithm() = default;

gen_algorithm::gen_algorithm(unsigned p_size, float m_probability, float c_probability, unsigned t, unsigned length_of_vector, unsigned iter_count)
{

    population_size = p_size;
    mutation_probability = m_probability;
    cross_probability = c_probability;
    parm_t = t;
    lengthOfVector = length_of_vector;
    iteration_count = iter_count;
}
void gen_algorithm::crossMethod(int method_number, int changed_element_numberP, int crossed_element_numberP, std::vector<std::vector<unsigned>> &vec, bool isNotSingle)
{
    int a = generate_number() % lengthOfVector;

    std::vector<unsigned> tmp;
    tmp.reserve(lengthOfVector);
    std::vector<unsigned> tmp2;
    tmp2.reserve(lengthOfVector);
    std::vector<unsigned> changed_element_number = population[changed_element_numberP].get_gene();
    std::vector<unsigned> crossed_element_number = population[crossed_element_numberP].get_gene();

    switch (method_number)
    {
    case 0: // Ab

        for (int i = 0; i < a; i++)
        {
            tmp.push_back(crossed_element_number[i]);
            if (isNotSingle)
                tmp2.push_back(crossed_element_number[i]);
        }
        for (unsigned i = a; i < lengthOfVector; i++)
        {
            tmp.push_back(changed_element_number[i]);
            if (isNotSingle)
                tmp2.push_back(changed_element_number[i]);
        }
        break;

    case 1: // aB

        for (int i = 0; i < a; i++)
        {
            tmp.push_back(changed_element_number[i]);
            if (isNotSingle)
                tmp2.push_back(changed_element_number[i]);
        }
        for (unsigned i = a; i < lengthOfVector; i++)
        {
            tmp.push_back(crossed_element_number[i]);
            if (isNotSingle)
                tmp2.push_back(crossed_element_number[i]);
        }
        break;

    default:
        break;
    }

    vec.push_back(tmp);
    if (isNotSingle)
        vec.push_back(tmp2);
}

void gen_algorithm::cross()
{
    std::vector<std::vector<unsigned>> vec;
    vec.reserve(population.size());

    std::vector<int> first_half;
    std::vector<int> second_half;

    first_half.reserve(population.size() / 2 + 1);
    second_half.reserve(population.size() / 2);

    bool first = true;

    for (unsigned i = 0; i < population.size(); i++)
    {
        if (generate_number() % 100 < cross_probability)
        {
            if (first)
            {
                first_half.push_back(i);
                first = false;
            }
            else
            {
                second_half.push_back(i);
                first = true;
            }
        }
        else
        {
            vec.push_back(population[i].get_gene());
        }
    }

    if (second_half.size() == 0)
    {
        int i = generate_number() % population.size();
        while (i == 0)
        {
            i = generate_number() % population.size();
        }
        crossMethod(generate_number() % 2, first_half[0], i, vec, false);
    }
    else
    {
        for (unsigned i = 0; i < first_half.size(); i++)
        {
            if (second_half.size() == 0)
            {
                int i = generate_number() % population.size();
                while (i == first_half[0])
                {
                    i = generate_number() % population.size();
                }
                crossMethod(generate_number() % 2, first_half[0], i, vec, false);
            }
            else
            {
                unsigned x = generate_number() % second_half.size();

                crossMethod(generate_number() % 2, first_half[i], second_half[x], vec, true);

                second_half.erase(second_half.begin() + x);
            }
        }
    }

    for (unsigned i = 0; i < vec.size(); i++)
    {
        population[i].set_gene(vec[i]);
    }
}
/*
void gen_algorithm::mutate()
{
    for(unsigned i = 0; i < population.size(); i++)
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

void gen_algorithm::mutate()
{
    int tmpStart = generate_number() % lengthOfVector;
    int step = 100/mutation_probability;
    for(unsigned i = 0; i < population.size(); i++)
    {
        std::vector<unsigned> tmp = population[i].get_gene();
        unsigned x;
        for (x = tmpStart; x < lengthOfVector; x += step)
        {
            tmp[x] = (tmp[x] + 1) % 2;
        }
        population[i].set_gene(tmp);
        tmpStart = x - lengthOfVector;

    }
}
*/
/*
void gen_algorithm::mutate()
{
    int tmp = generate_number() % 100;
    int step = mutation_probability * lengthOfVector;
    for(int i = 0; i < population.size(); i++)
    {
        std::vector<unsigned> tmpVec = population[i].get_gene();
        std::vector<bool> tmpCheckVec(lengthOfVector, false); 
        while (tmp > 100)
        {
            tmp -= 100;
            unsigned x = generate_number() % lengthOfVector;
            while(tmpCheckVec[x] == true)
            {
                unsigned x = generate_number() % lengthOfVector;
            }
            tmpCheckVec[x] == true;
            tmpVec[x] = (tmpVec[x] + 1) % 2;
        }
        tmp += step;
    }
}*/

void gen_algorithm::mutate()
{
    int numberOfElementsToChange = mutation_probability * lengthOfVector * population.size() / 1000;
    std::vector<std::vector<bool>> tmpCheckVec;
    std::vector<bool> tmpCheck;

    for (unsigned i = 0; i < population_size; i++)
    {
        for (unsigned j = 0; j < lengthOfVector; j++)
        {
            tmpCheck.push_back(false);
        }
        tmpCheckVec.push_back(tmpCheck);
    }

    for (int i = 0; i < numberOfElementsToChange; i++)
    {
        int x = generate_number() % population.size();
        int y = generate_number() % lengthOfVector;

        while (tmpCheckVec[x][y] == true)
        {
            x = generate_number() % population.size();
            y = generate_number() % lengthOfVector;
        }

        tmpCheckVec[x][y] = true;

        std::vector<unsigned> tmpVec = population[x].get_gene();
        tmpVec[y] = (tmpVec[y] + 1) % 2;

        population[x].set_gene(tmpVec);
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

void gen_algorithm::fintess_calc()
{

    unsigned ones_score = 0;
    unsigned zeros_score = 0;
    unsigned score = 0;
    std::vector<unsigned> a;

    for (unsigned i = 0; i < lengthOfVector; ++i)
        a.push_back(0);

    l_best_so_far.set_fitness(0);
    r_best_so_far.set_fitness(0);
    l_best_so_far.set_gene(a);
    r_best_so_far.set_gene(a);

    for (auto &i : population)
    {

        ones_score = 0;
        zeros_score = 0;
        score = 0;

        for (auto x = i.get_gene().begin(); x != i.get_gene().end(); ++x)
        {

            if (*x == 0)
                break;
            else
                ++ones_score;
        }

        for (auto j = i.get_gene().rbegin(); j != i.get_gene().rend(); ++j)
        {

            if (*j == 1)
                break;
            else
                ++zeros_score;
        }

        if (zeros_score >= parm_t && ones_score >= parm_t)
            score += 100;

        score += std::max(ones_score, zeros_score);

        i.set_fitness(score);

        if (l_best_so_far < i && ones_score > zeros_score)
            l_best_so_far = i;
        if (r_best_so_far < i && zeros_score > ones_score)
            r_best_so_far = i;
        if (best_so_far < i)
            best_so_far = i;
    }
}

// void gen_algorithm::selection()
// {

//     long unsigned number;
//     long unsigned sum;
//     int count;
//     long unsigned fitness_sum = 0;
//     std::vector<individual> temp;

//     for (auto i : population)
//         fitness_sum += i.get_fitness();

//     for (unsigned x = 0; x < population_size; ++x)
//     {

//         number = generate_number() % fitness_sum;
//         sum = 0;
//         count = 0;

//         for (auto &i : population)
//         {

//             if ((sum += i.get_fitness()) > number)
//             {
//                 temp.push_back(population[count]);
//                 break;
//             }
//             count++;
//         }
//     }

//     population.clear();

//     for (auto &i : temp)
//     {

//         population.push_back(i);
//     }
// }

void gen_algorithm::selection() {

    std::vector<individual> temp;

    for( unsigned x = 0; x < population_size; ++x ) {

        unsigned temp1 = generate_number() % population_size;
        unsigned temp2 = generate_number() % population_size;

        if( population[temp1] < population[temp2] )
            temp.push_back(population[temp2]);
        else
            temp.push_back(population[temp1]);
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

individual gen_algorithm::start()
{

    initPopulation();
    fintess_calc();
    for (unsigned i = 0; i < iteration_count; ++i)
    {
        selection();
        cross();
        mutate();
        fintess_calc();
        //std::cout << "lewy: " << l_best_so_far;
        //std::cout << "prawy: " << r_best_so_far;
        //std::cout << best_so_far;
    }
    return best_so_far;
}

individual gen_algorithm::start(std::string &log)
{

    initPopulation();
    fintess_calc();
    for (unsigned i = 0; i < iteration_count; ++i)
    {
        selection();
        cross();
        mutate();
        fintess_calc();

        log += std::to_string(population_size);
        log += ";";
        log += std::to_string(lengthOfVector);
        log += ";";
        log += std::to_string(mutation_probability);
        log += ";";
        log += std::to_string(cross_probability);
        log += ";";
        log += std::to_string(parm_t);
        log += ";";
        log += std::to_string(i);
        log += ";";
        log += std::to_string(best_so_far.get_fitness());
        log += "\n";
        //std::cout << "lewy: " << l_best_so_far;
        //std::cout << "prawy: " << r_best_so_far;
        //std::cout << best_so_far;
    }
    return best_so_far;
}