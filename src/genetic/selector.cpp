#include "genetic/selector.hpp"

  
Selector::~Selector()
{
  delete[] m_genomes;
}

void Selector::setup_shape(std::size_t genomes, std::size_t genes)
{
  m_size = genomes;
  m_genomes = new Genome[m_size];

  for (std::size_t i=0; i < m_size; i++) {
    m_genomes[i].setup(genes);
    m_genomes[i].randomize(50.0f);
  }
}

const Genome& Selector::get_genome(std::size_t index)
{
  return m_genomes[index];
}

void Selector::evaluate()
{
}

