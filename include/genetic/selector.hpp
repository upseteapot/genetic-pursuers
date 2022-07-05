#pragma once
#include <random>
#include <vector>
#include "genetic/genome.hpp"


class Selector
{
  public:
    Selector();
    ~Selector();

    void setup(std::size_t size, std::size_t genes);
    void select(float mutation_rate, float mutation_mag);

    Genome &operator[](std::size_t index);
    const Genome &operator[](std::size_t index) const;
  private:
    std::mt19937 m_rng;
    std::size_t m_size, m_genes;
    Genome *m_genomes;
  
    const Genome &m_get_random_genome(std::size_t *frequencies);
};

