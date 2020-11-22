#include <iostream>
#include "gen_algorithm.hpp"

int main() {

    int populationSize = 0;
    int elemSize = 0;
    float mutationPropability = 0;
    float crossPropability = 0;
    int parm_t;
    int gen_count;
    int parent_number;

    do
    {
        std::cout << "Podaj rozmiar populacji: " << std::endl;
        std::cin >> populationSize;
        if(populationSize < 1) std::cout << "Rozmiar populacji musi byc wiekszy niz 0." << std::endl;

    } while (populationSize < 1);

    do
    {
        std::cout << "Podaj rozmiar elementu: " << std::endl;
        std::cin >> elemSize;
        if(elemSize < 1) std::cout << "Rozmiar elementu musi byc wiekszy niz 0." << std::endl;

    } while (elemSize < 1);
    
    do
    {
        std::cout << "Podaj prawdopodobienstwo mutacji: " << std::endl;
        std::cin >> mutationPropability;
        if(mutationPropability < 0 || mutationPropability > 100) std::cout << "Prawdopodobienstwo musi byc z zakresu 0-100." << std::endl;
        
    } while (mutationPropability < 0 || mutationPropability > 100);

    do
    {
        std::cout << "Podaj prawdopodobienstwo krzyzowania: " << std::endl;
        std::cin >> crossPropability;
        if(crossPropability < 0 || crossPropability > 100) std::cout << "Prawdopodobienstwo musi byc z zakresu 0-100." << std::endl;
        
    } while (crossPropability < 0 || crossPropability > 100);

    do
    {
        std::cout << "Podaj wartość parametru t: " << std::endl;
        std::cin >> parm_t;
        if(parm_t < 0 || parm_t > elemSize / 2) std::cout << "Wartość parametru t musi być z zakresu: 0 - rozmiar elementu / 2." << std::endl;
        
    } while (parm_t < 0 || parm_t > elemSize / 2);

    do
    {
        std::cout << "Podaj ilość generacji: " << std::endl;
        std::cin >> gen_count;
        if(gen_count < 0) std::cout << "Ilość generacji musi być większa od zera." << std::endl;
        
    } while (gen_count < 0);

    do
    {
        std::cout << "Podaj ilość rodziców, którzy przedją do następnego pokolenia: " << std::endl;
        std::cin >> parent_number;
        if(parent_number < 0 || parent_number > populationSize) std::cout << "Ilość rodziców musi być z zakresu: 0 - rozmiar populacji." << std::endl;
        
    } while (gen_count < 0);

    gen_algorithm algorithm(populationSize, mutationPropability, crossPropability, parm_t, elemSize, gen_count, parent_number);
    algorithm.start();
}