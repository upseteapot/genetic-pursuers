#include "genetic-algo/genome.hpp"


using namespace genalgo;


Genome::~Genome()
{
  delete[] m_genes;
}


void Genome::setup(std::size_t size)
{
  m_size  = size;
  m_genes = new double[m_size];
  memset(m_genes, '\0', m_size * sizeof(double));
}

void Genome::randomize(std::mt19937 &rng)
{
  std::uniform_real_distribution<double> dist(-1.0, 1.0);
  for (std::size_t i=0; i < m_size; i++)
    m_genes[i] = dist(rng);
}

void Genome::copy_from(const Genome &source)
{
  memcpy(m_genes, source.data(), m_size * sizeof(double));
}


std::size_t Genome::size() const
{
  return m_size;
}

const double *Genome::data() const
{
  return m_genes;
}

double &Genome::operator[](std::size_t index)
{
  return m_genes[index];
}

double Genome::operator[](std::size_t index) const
{
  return m_genes[index];
}


void Genome::set_fitness(double fitness)
{
  m_fitness = fitness;
}

double Genome::get_fitness() const
{
  return m_fitness;
}


void Genome::cross_over(Genome &source, const Genome& parent_a, const Genome& parent_b, std::size_t size, std::mt19937 &rng)
{
  std::uniform_real_distribution<float> dist(0.0f, 1.0f);
  for (std::size_t i=0; i < size; i++) {
    float x = dist(rng);
    if (x < 0.5f)
      source[i] = parent_a[i];
    else
      source[i] = parent_b[i];
  }
}

void Genome::mutate(Genome &source, double rate, double mag, std::mt19937 &rng)
{
  std::uniform_real_distribution<double> dist0(0.0, 1.0);
  std::uniform_real_distribution<double> dist1(-mag, mag);
  for (std::size_t i=0; i < source.size(); i++) {
    float x = dist0(rng);
    if (x < rate)
      source[i] = source[i] + dist1(rng);
  }
}

