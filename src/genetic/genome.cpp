#include "genetic/genome.hpp"


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

Vec2f Genome::next()
{
  if (m_index < m_size) {
    return m_genes[m_index++];
  } else {
    std::cout << "[GENOME::ERROR] Index out of bounds." << std::endl;
    return Vec2f(0.0f, 0.0f);
  }
}

