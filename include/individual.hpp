#pragma once
#include <vector>
#include <iostream>

class individual {

    std::vector<unsigned> gene;
    unsigned fitness;

    public:

    individual();
    ~individual() = default;
    individual(const individual & other);
    individual & operator=(const individual & other);
    bool operator< ( individual const & other) const;
    std::vector<unsigned>  const & get_gene() const;
    unsigned get_fitness() const;
    void set_fitness( unsigned f );
    void set_gene( std::vector<unsigned> & g );

};