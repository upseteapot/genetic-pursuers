#pragma once
#include <iostream>
#include <random>
#include "math/vec2.hpp"


class Genome
{
  public:
    float evaluation = 0;
    bool previous_best = false;

    Genome() = default;
    void reset();
    void setup(std::size_t size);
    void randomize(float magnitude);
    void set(std::size_t index, const Vec2f &gene);

    std::size_t get_size() const;
    Vec2f get(std::size_t index) const;
    Vec2f next(); 
   
    static Genome cross_over(const Genome &a, const Genome &b);
    void mutate(float magnitude, float probability);
  
  private:
    std::size_t m_index = 0;
    std::size_t m_size;
    std::vector<Vec2f> m_genes;
};

