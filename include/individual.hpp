#pragma once
#include <vector>

class individual {

    std::vector<unsigned> gene;
    unsigned fitness;

    public:

    individual();
    ~individual() = default;
    individual(const individual & other);
    individual & operator=(const individual & other);
    bool operator< ( individual const & other) const;
    std::vector<unsigned> get_gene();
    unsigned get_fitness();
};