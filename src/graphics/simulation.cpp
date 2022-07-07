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
  
  m_selector.setup(m_pursuer_size, (m_simulation_time / m_pursuer_cooldown) * 2);
  
  m_pursuers.resize(m_pursuer_size);
  for (std::size_t i=0; i < m_pursuer_size; i++) {
    m_pursuers[i].setup(Vec2f(0.0f, 400.0f), m_pursuer_cooldown);
    m_pursuers[i].reset();
  }

}

void Simulation::run(float dt)
{ 
  if (!m_paused) {
    if ((m_counter += dt) >= m_simulation_time) {
      m_counter = 0.0f;

      for (std::size_t i=0; i < m_pursuer_size; i++) {
        float distance = Vec2f::dist(m_pursuers[i].get_pos(), m_target.get_pos());
        m_selector[i].set_fitness(1 / (std::max((float)pow(distance, 2), 0.0001f) * pow(m_pursuers[i].get_global_counter(), 2)));
        if (!m_pursuers[i].is_alive())
          m_selector[i].set_fitness(m_selector[i].get_fitness() / 10.0f);  
        m_pursuers[i].reset();
      }

      m_selector.select();
      m_pursuers[0].set_color(sf::Color(30, 255, 122));
      m_best_fitness.setString("Best fitness: " + std::to_string(m_selector[0].get_fitness()));
    }

    for (std::size_t i=0; i < m_pursuer_size; i++) {
      m_pursuers[i].update(dt, m_selector[i]);
      m_pursuers[i].check_bounds(m_size, i == 0);
      m_pursuers[i].collided(m_target, i == 0);
    }
  }

  m_renderer.clear(sf::Color(20, 22, 33));

  for (std::size_t i=1; i < m_pursuer_size; i++)
      m_renderer.draw(m_pursuers[i]);
  m_renderer.draw(m_pursuers[0]);
  m_renderer.draw(m_target);
  m_renderer.draw(m_best_fitness);
  
  m_renderer.display();
}

void Simulation::event()
{
  switch (m_event.type) {
    case sf::Event::KeyPressed:
      switch (m_event.key.code) {
        case sf::Keyboard::Space:
          m_paused = !m_paused;
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

