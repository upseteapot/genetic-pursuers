#pragma once
#include "genetic/genome.hpp"


class Selector
{
  public:
    Selector() = default;
    ~Selector();
    void setup_shape(std::size_t genomes, std::size_t genes);
    const Genome& get_genome(std::size_t index);
    void evaluate();
  private:
    std::size_t m_size;
    Genome *m_genomes;
};

