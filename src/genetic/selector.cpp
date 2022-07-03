#include "genetic/selector.hpp"

#define PROB_ARRAY_IMPLEMENTATION
#include "math/prob_array.hpp"

  
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
    m_genomes[i].randomize(15.0f);
  }
}

Genome& Selector::get_genome(std::size_t index)
{
  return m_genomes[index];
}

void Selector::evaluate()
{
  ProbArray<Genome> pool;
  pool.create(m_size);
  
  // Get maximum genome evaluation.
  float max_evaluation = 0.0f; 
  Genome best_genome;
  for (std::size_t i=0; i < m_size; i++)
    if (m_genomes[i].evaluation > max_evaluation) {
      max_evaluation = m_genomes[i].evaluation;
      best_genome = m_genomes[i];
    }
  
  // Push genomes to pool.
  for (std::size_t i=0; i < m_size; i++) {
    std::size_t frequency = std::round(100 * (m_genomes[i].evaluation / max_evaluation));
    pool.push(m_genomes[i], frequency);
  }
  
  // Preserve best genome from previous iteration
  best_genome.reset();
  best_genome.previous_best = true;  
  m_genomes[0] = best_genome;

  // Create new genomes by crossing over their genes and mutating them.
  for (std::size_t i=1; i < m_size; i++) {
    m_genomes[i] = Genome::cross_over(pool.get_random(), pool.get_random());
    m_genomes[i].mutate(0.2f, 1.0f);
  }
}

