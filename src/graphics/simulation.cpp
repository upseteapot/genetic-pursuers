#include "graphics/simulation.hpp"


void Simulation::setup()
{
  m_target.setup(Vec2f(0.0f, 400.0f), sf::Color::Red);
  
  m_genome.setup((m_simulation_time - 1) / m_pursuer_cooldown);
  m_genome.randomize(50.0f);

  m_pursuer.setup(Vec2f(0.0f, -400.0f), sf::Color::Green, m_pursuer_cooldown);
  m_pursuer.reset();
}

void Simulation::run(float dt)
{
  if ((m_counter += dt) >= m_simulation_time) {
    m_counter = 0.0f;
    m_paused = true;
    m_pursuer.reset();
  }

  if (!m_paused) 
    m_pursuer.update(dt, m_genome);
  
  m_renderer.clear(sf::Color::Black);
  m_renderer.draw(m_target);
  m_renderer.draw(m_pursuer);
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

