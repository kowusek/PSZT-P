#include <iostream>
#include "gen_algorithm.hpp"
#include <chrono>
#include <fstream>
#include <sstream>

int main() {

    int populationSize = 500;
    int elemSize = 50;
    int mutationPropability = 30;
    int crossPropability = 80;
    int parm_t = 15;
    int gen_count = 500;
    std::string log;

    // do
    // {
    //     std::cout << "Podaj rozmiar populacji: " << std::endl;
    //     std::cin >> populationSize;
    //     if(populationSize < 1) std::cout << "Rozmiar populacji musi byc wiekszy niz 0." << std::endl;

    // } while (populationSize < 1);

    // do
    // {
    //     std::cout << "Podaj rozmiar elementu: " << std::endl;
    //     std::cin >> elemSize;
    //     if(elemSize < 1) std::cout << "Rozmiar elementu musi byc wiekszy niz 0." << std::endl;

    // } while (elemSize < 1);
    
    // do
    // {
    //     std::cout << "Podaj prawdopodobienstwo mutacji: " << std::endl;
    //     std::cin >> mutationPropability;
    //     if(mutationPropability < 0 || mutationPropability > 100) std::cout << "Prawdopodobienstwo musi byc z zakresu 0-100." << std::endl;
        
    // } while (mutationPropability < 0 || mutationPropability > 100);

    // do
    // {
    //     std::cout << "Podaj prawdopodobienstwo krzyzowania: " << std::endl;
    //     std::cin >> crossPropability;
    //     if(crossPropability < 0 || crossPropability > 100) std::cout << "Prawdopodobienstwo musi byc z zakresu 0-100." << std::endl;
        
    // } while (crossPropability < 0 || crossPropability > 100);

    // do
    // {
    //     std::cout << "Podaj wartość parametru t: " << std::endl;
    //     std::cin >> parm_t;
    //     if(parm_t < 0 || parm_t > elemSize / 2) std::cout << "Wartość parametru t musi być z zakresu: 0 - rozmiar elementu / 2." << std::endl;
        
    // } while (parm_t < 0 || parm_t > elemSize / 2);

    // do
    // {
    //     std::cout << "Podaj ilość generacji: " << std::endl;
    //     std::cin >> gen_count;
    //     if(gen_count < 0) std::cout << "Ilość generacji musi być większa od zera." << std::endl;
        
    // } while (gen_count < 0);

    //gen_algorithm algorithm(populationSize, mutationPropability, crossPropability, parm_t, elemSize, gen_count );

    log += "Rozmiar populacji;Rozmiar genu;Prawdopodobienstwo mutacji;Prawdopodobienstwo krzyzowania;parametr t;ilosc generacji;Najlepsze rozwiazanie;Czas;Wartosc funkcji celu\n";
    //log += "Rozmiar populacji;Rozmiar genu;Prawdopodobienstwo mutacji;Prawdopodobienstwo krzyzowania;parametr t;Numer generacji;Wartosc funkcji celu\n";

    for(int j = 0; j < 10; ++j ) {

        for(int i = 0; i < 35; ++i ) {

            std::cout << "j: " << j << "   i: " << i << std::endl;
    
            gen_algorithm algorithm( populationSize, mutationPropability, crossPropability, 3 + 2 * j, elemSize, gen_count);

            auto start = std::chrono::system_clock::now();
            std::time_t time2 = std::chrono::system_clock::to_time_t( start );

            individual temp = algorithm.start();

            auto end = std::chrono::system_clock::now();
            std::time_t time1 = std::chrono::system_clock::to_time_t( end );

            auto seconds = time1 - time2;
            std::stringstream ss;
            ss << seconds;
            std::string ts = ss.str();
            
            log += std::to_string(populationSize);
            log += ";";
            log += std::to_string(elemSize);
            log += ";";
            log += std::to_string(mutationPropability);
            log += ";";
            log += std::to_string(crossPropability);
            log += ";";
            log += std::to_string(3 + 2 * j);
            log += ";";
            log += std::to_string(gen_count);
            log += ";";
            log += "'";
            log += temp;
            log += "'";
            log += ";";
            log += ts;
            log += ";";
            log += std::to_string(temp.get_fitness());
            log += "\n";
            
        }
        log += "\n";
        log += "\n";
    }

    std::fstream file;

    file.open( "./log.csv", std::ios::out );
    file << log;
    file.close();
}