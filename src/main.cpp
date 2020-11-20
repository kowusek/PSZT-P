#include <iostream>
#include "gen_algorithm.hpp"

int main() {

    int populationSize = 0;
    float mutationPropability = 0;
    float crossPropability = 0;

    //gen_algorithm algorithm;


    ///////

    do
    {
        std::cout << "Podaj rozmiar populacji: " << std::endl;
        std::cin >> populationSize;
        if(populationSize < 1) std::cout << "Rozmiar populacji musi byc wiekszy niz 0" << std::endl;

    } while (populationSize < 1);
    
    do
    {
        std::cout << "Podaj prawdopodobienstwo mutacji: " << std::endl;
        std::cin >> mutationPropability;
        if(mutationPropability < 0 || mutationPropability > 100) std::cout << "Prawdopodobienstwo musi byc z zakresu 0-100" << std::endl;
        
    } while (mutationPropability < 0 || mutationPropability > 100);

    do
    {
        std::cout << "Podaj prawdopodobienstwo krzyzowania: " << std::endl;
        std::cin >> crossPropability;
        if(crossPropability < 0 || crossPropability > 100) std::cout << "Prawdopodobienstwo musi byc z zakresu 0-100" << std::endl;
        
    } while (crossPropability < 0 || crossPropability > 100);

    //algorithm.gen_function(populationSize, mutationPropability, crossPropability);

}