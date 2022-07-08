#pragma once
#include <vector>
#include <random>
#include <ctime>
#include <string>
#include <cmath>

#include <SFML/Graphics.hpp>

#include "graphics/engine.hpp"
#include "graphics/pursuer.hpp"
#include "graphics/target.hpp"
#include "graphics/obstacle.hpp"

#include "genetic-algo/selector.hpp"


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
    bool m_creating = false;

    sf::Font m_source_sans_pro;

    Target m_target;
    std::vector<Pursuer> m_pursuers;
    sf::Text m_best_fitness;
   
    Obstacle m_selected_obstacle;
    std::vector<Obstacle> m_obstacles;

    genalgo::Selector m_selector;

    void setup() override;
    void run(float dt) override;
    void event() override;
    void clear() override;
};

