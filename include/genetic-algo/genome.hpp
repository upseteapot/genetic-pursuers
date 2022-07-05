#pragma once
#include <random>
#include <cstring>


namespace genalgo 
{

  class Genome
  {
    public:
      Genome() = default;
      ~Genome();

      void setup(std::size_t size);
      void randomize(std::mt19937 &rng);
      void copy_from(const Genome &source);

      std::size_t size() const;
      const double *data() const;
      double &operator[](std::size_t index);
      double operator[](std::size_t index) const;

      void set_fitness(double fitness);
      double get_fitness() const;

      static void cross_over(Genome &source, const Genome& parent_a, const Genome& parent_b, std::size_t size, std::mt19937 &rng);
      static void mutate(Genome &source, double rate, double mag, std::mt19937 &rng); 

    private:
      double m_fitness = 0.0;
      std::size_t m_size = 0;
      double *m_genes;
  };

}

