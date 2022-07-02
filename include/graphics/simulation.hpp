#pragma once
#include <random>
#include <ctime>
#include <SFML/Graphics.hpp>
#include "graphics/engine.hpp"

#include "graphics/pursuer.hpp"
#include "graphics/target.hpp"


class Simulation : public Engine
{
  public:
    Simulation() = default;
  private:
    float m_simulation_time = 5.0f;
    float m_pursuer_cooldown = 0.5f;
    float m_counter = 0.0f;
    bool m_paused = true;
  
    Target m_target;
    Pursuer m_pursuer;
    Genome m_genome;

    void setup();
    void run(float dt);
    void event();
    void clear();
};

