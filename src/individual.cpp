#include "individual.hpp"

individual::individual() {

    fitness = 0;
}

individual::individual(const individual & other) {

    this->fitness = other.fitness;
    this->gene = other.gene;
}

individual & individual::operator=(const individual & other) {

    if(&other == this)
            return *this;

    this->fitness = other.fitness;
    this->gene = other.gene;

    return *this;
}

bool individual::operator< ( individual const & other) const {

    return this->fitness < other.fitness;
}

std::vector<unsigned> individual::get_gene() {

    return this->gene;
}

unsigned individual::get_fitness() {

    return this->fitness;
}