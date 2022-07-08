#include "graphics/simulation.hpp"


void Simulation::setup()
{
  m_source_sans_pro.loadFromFile("assets/SourceSansPro-Regular.ttf");
  m_best_fitness.setFont(m_source_sans_pro);
  m_best_fitness.setCharacterSize(20);
  m_best_fitness.setFillColor(sf::Color::White);
  m_best_fitness.setString("Best fitness: N/A");
  m_best_fitness.setPosition(-m_size.x / 2.f + 10, -m_size.y / 2.f + 10);

  m_target.setup(Vec2f(0.0f, -400.0f), sf::Color(250, 100, 80));
  
  genalgo::SelectorStates states;
  states.fitness_exponent = 2.5;
  states.mutation_rate = 0.6;
  states.mutation_mag = 0.00005; 
  
  m_selector.set_states(states);
  m_selector.setup(m_pursuer_size, (m_simulation_time / m_pursuer_cooldown) * 2);
  
  m_pursuers.resize(m_pursuer_size);
  for (std::size_t i=0; i < m_pursuer_size; i++) {
    m_pursuers[i].setup(Vec2f(0.0f, 400.0f), m_pursuer_cooldown);
    m_pursuers[i].reset();
  }

  m_selected_obstacle.set_color();
  
}

void Simulation::run(float dt)
{ 
  if (!m_paused) {
    if ((m_counter += dt) >= m_simulation_time) {
      m_counter = 0.0f;

      for (std::size_t i=0; i < m_pursuer_size; i++) {
        float distance = Vec2f::dist(m_pursuers[i].get_pos(), m_target.get_pos());
        if (!m_pursuers[i].is_alive())
          m_selector[i].set_fitness(1 / (10000.f * std::max((float)pow(distance, 2), 0.0001f)));
        if (m_pursuers[i].is_alive())
          m_selector[i].set_fitness(1 / std::max((float)pow(distance, 2), 0.0001f));
        if (m_pursuers[i].has_reached_target())
          m_selector[i].set_fitness(1000.0f / (std::max((float)pow(distance, 2), 0.0001f) * pow(m_pursuers[i].get_global_counter(), 2)));
        m_pursuers[i].reset();
      }

      m_selector.select();
      m_pursuers[0].set_color(sf::Color(30, 255, 122));
      m_best_fitness.setString("Best fitness: " + std::to_string(m_selector[0].get_fitness()));
    }

    for (std::size_t i=0; i < m_pursuer_size; i++) {
      m_pursuers[i].update(dt, m_selector[i]);
      m_pursuers[i].check_bounds(m_size, i == 0);
      m_pursuers[i].reach_target(m_target, i == 0);
      
      for (auto &obstacle : m_obstacles)
        m_pursuers[i].collided(obstacle.get_bounds(), i ==0);
    }
  }

  m_renderer.clear(sf::Color(20, 22, 33));

  for (auto &pursuer : m_pursuers)
      m_renderer.draw(pursuer);
  m_renderer.draw(m_pursuers[0]);
  
  for (auto &obstacle : m_obstacles)
    m_renderer.draw(obstacle);
  
  m_renderer.draw(m_target);
  m_renderer.draw(m_best_fitness);
  
  if (m_creating) {
    m_selected_obstacle.set_stop(m_renderer.mapPixelToCoords(sf::Mouse::getPosition(m_renderer)));
    m_renderer.draw(m_selected_obstacle);
  }

  m_renderer.display();
}

void Simulation::event()
{
  switch (m_event.type) {
    case sf::Event::MouseButtonPressed:
      if (m_event.mouseButton.button == sf::Mouse::Left) {
        if (m_paused) {
          if (!m_creating) {
            m_creating = true;
            m_selected_obstacle.set_start(m_renderer.mapPixelToCoords(sf::Mouse::getPosition(m_renderer)));
          } else {
            m_creating = false;
            m_obstacles.push_back(m_selected_obstacle);
          }
        }
      } 
      break;

    case sf::Event::KeyPressed:
      switch (m_event.key.code) {
        case sf::Keyboard::Space:
          m_paused = !m_paused && !m_creating;
        default:
          break;
      }
      break;

    case sf::Event::Resized:
      m_best_fitness.setPosition(-m_size.x / 2.f + 10, -m_size.y / 2.f + 10);
      break;

    default:
      break;
  }
}

void Simulation::clear()
{
}

