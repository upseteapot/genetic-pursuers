#pragma once
#include <vector>
#include <random>
#include <ctime>
#include <cmath>

#include <SFML/Graphics.hpp>

#include "graphics/engine.hpp"
#include "graphics/pursuer.hpp"
#include "graphics/target.hpp"
#include "genetic/selector.hpp"


class Simulation : public Engine
{
  public:
    Simulation() = default;
  private:
    std::size_t m_pursuer_size = 200;
    float m_simulation_time = 6.0f;
    float m_pursuer_cooldown = 0.1f;
    float m_counter = 0.0f;
    bool m_paused = true;

    Target m_target;
    std::vector<Pursuer> m_pursuers;
    Selector m_selector;

    void setup() override;
    void run(float dt) override;
    void event() override;
    void clear() override;
};

