#pragma once
#include <iostream>
#include <random>
#include "math/vec2.hpp"


class Genome
{
  public:
    Genome() = default;
    void setup(std::size_t size);
    void randomize(float magnitude);
    Vec2f next();
  private:
    std::size_t m_index = 0;
    std::size_t m_size;
    std::vector<Vec2f> m_genes;
};

