#pragma once
#include <random>
#include <cmath>
#include "genetic-algo/genome.hpp"


namespace genalgo
{

  struct SelectorStates
  {
    double fitness_exponent     = 1;
    bool maintain_previous_best = true;
    double mutation_rate        = 0.1;
    double mutation_mag         = 0.001;
  };


  class Selector
  {
    public:
      Selector();
      ~Selector();

      void setup(std::size_t size, std::size_t genes);
      void select();

      SelectorStates &get_states();
      const SelectorStates &get_states() const;
      void set_states(const SelectorStates &states);

      Genome &operator[](std::size_t index);
      const Genome &operator[](std::size_t index) const;

    private:
      SelectorStates m_states;
      std::mt19937 m_rng;
      std::size_t m_size, m_genes;
      Genome *m_genomes;

      const Genome &m_get_random_genome(std::size_t *frequencies);
  };

}

