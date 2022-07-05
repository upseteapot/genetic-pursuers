#include "genetic-algo/selector.hpp"


using namespace genalgo;

  
Selector::Selector()
{
  std::random_device device;
  m_rng = std::mt19937(device());
}
  
Selector::~Selector()
{
  delete[] m_genomes;
}


void Selector::setup(std::size_t size, std::size_t genes)
{
  m_size = size;
  m_genes = genes;
  m_genomes = new Genome[m_size];

  for (std::size_t i=0; i < m_size; i++) {
    m_genomes[i].setup(genes);
    m_genomes[i].randomize(m_rng);
  }
}

void Selector::select()
{
  std::size_t *frequencies = new std::size_t[m_size];

  double max_fitness = 0.0; 
  std::size_t best_genome = 0;
  for (std::size_t i=0; i < m_size; i++) {
    double fitness = m_genomes[i].get_fitness();
    if (fitness > max_fitness) {
      max_fitness = fitness;
      best_genome = i;
    }
  }

  for (std::size_t i=0; i < m_size; i++) {
    frequencies[i] = std::round(100.0 * pow(m_genomes[i].get_fitness() / max_fitness, m_states.fitness_exponent));
    if (i > 0)
      frequencies[i] += frequencies[i - 1];
  }

  std::size_t start = 0;
  if (m_states.maintain_previous_best) {
    start = 1;
    m_genomes[0].copy_from(m_genomes[best_genome]);
    m_genomes[0].set_fitness(max_fitness);
  }

  for (std::size_t i=start; i < m_size; i++) {
    Genome::cross_over(m_genomes[i], m_get_random_genome(frequencies), m_get_random_genome(frequencies), m_genes, m_rng);
    Genome::mutate(m_genomes[i], m_states.mutation_rate, m_states.mutation_mag, m_rng);
  }

  delete[] frequencies;
}


SelectorStates &Selector::get_states()
{
  return m_states;
}

const SelectorStates &Selector::get_states() const
{
  return m_states;
}

void Selector::set_states(const SelectorStates &states)
{
  m_states = states;
}


Genome &Selector::operator[](std::size_t index)
{
  return m_genomes[index];
}

const Genome &Selector::operator[](std::size_t index) const
{
  return m_genomes[index];
}


const Genome &Selector::m_get_random_genome(std::size_t *frequencies)
{
  std::uniform_int_distribution<std::size_t> dist(0, frequencies[m_size - 1]);
  std::size_t x = dist(m_rng);
  for (std::size_t i=0; i < m_size; i++)
    if (x < frequencies[i])
      return m_genomes[i];
  return m_genomes[m_size - 1];
}

