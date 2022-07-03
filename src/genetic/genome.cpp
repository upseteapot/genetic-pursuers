#include "genetic/genome.hpp"


void Genome::reset()
{
  m_index = 0;
}

void Genome::setup(std::size_t size)
{
  m_size = size;
  m_genes.resize(size);
}

void Genome::randomize(float magnitude)
{
  for (std::size_t i=0; i < m_size; i++) {
    float angle = rand() * 2.f * 3.14159265f / RAND_MAX;
    m_genes[i].x = 1.0f;
    m_genes[i].set_angle(angle);
    m_genes[i] *= magnitude;
  }
}

void Genome::set(std::size_t index, const Vec2f &gene)
{
  m_genes[index] = gene;
}


std::size_t Genome::get_size() const
{
  return m_size;
}

Vec2f Genome::get(std::size_t index) const
{
  return m_genes[index];
}

Vec2f Genome::next()
{
  if (m_index < m_size) {
    return m_genes[m_index++];
  } else {
    std::cout << "[Genome][ERROR] Index out of bounds." << std::endl;
    return Vec2f(0.0f, 0.0f);
  }
}


Genome Genome::cross_over(const Genome &a, const Genome &b)
{
  if (a.get_size() != b.get_size()) {
    std::cout << "[Genome][ERROR] Could not crossover genes because genome have different sizes." << std::endl;
    return Genome();
  }
  Genome new_genome;
  new_genome.setup(a.get_size());
  for (std::size_t i=0; i < a.get_size(); i++) {
    float random_number = (float)rand() / RAND_MAX;
    if (random_number < 0.5f)
      new_genome.set(i, a.get(i));
    else
      new_genome.set(i, b.get(i));
  }
  return new_genome;
}

void Genome::mutate(float magnitude, float probability)
{
  for (std::size_t i=0; i < m_size; i++) { 
    float random_number = (float)rand() / RAND_MAX;
    if (random_number <= probability) {
      float delta_x = magnitude * ((2.f * rand() / RAND_MAX) - 1.f);
      float delta_y = magnitude * ((2.f * rand() / RAND_MAX) - 1.f);
      set(i, get(i) + Vec2f(delta_x, delta_y));
    }
  }
}

