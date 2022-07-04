#include "graphics/simulation.hpp"


void Simulation::setup()
{
  m_target.setup(Vec2f(0.0f, 400.0f), sf::Color(250, 100, 80));

  m_selector.setup_shape(m_pursuer_size, m_simulation_time / m_pursuer_cooldown);
  
  m_pursuers.resize(m_pursuer_size);
  for (std::size_t i=0; i < m_pursuer_size; i++) {
    m_pursuers[i].setup(Vec2f(0.0f, -400.0f), m_pursuer_cooldown);
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
        m_selector.get_genome(i).evaluation = 1 / (std::max(distance * distance, 0.0001f) * m_pursuers[i].get_global_counter());
        m_pursuers[i].reset();
      }

      m_selector.evaluate();
      m_pursuers[0].set_color(sf::Color(30, 255, 122));
    }

    for (std::size_t i=0; i < m_pursuer_size; i++) {
      m_pursuers[i].update(dt, m_selector.get_genome(i));
      m_pursuers[i].collided(m_target, i == 0);
    }
  }

  m_renderer.clear(sf::Color(20, 22, 33));

  for (std::size_t i=1; i < m_pursuer_size; i++)
      m_renderer.draw(m_pursuers[i]);
  m_renderer.draw(m_pursuers[0]);
  m_renderer.draw(m_target);
  
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

    default:
      break;
  }
}

void Simulation::clear()
{
}

