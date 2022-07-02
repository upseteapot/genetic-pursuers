#include "graphics/pursuer.hpp"


void Pursuer::setup(Vec2f start_pos, sf::Color color, float cooldown)
{
  m_start_pos = start_pos;

  m_shape.setPointCount(3);
  m_shape.setPoint(0, sf::Vector2f(-m_radius,  m_radius / 2.f));
  m_shape.setPoint(1, sf::Vector2f(-m_radius, -m_radius / 2.f));
  m_shape.setPoint(2, sf::Vector2f( m_radius,  0.0f));
  
  m_shape.setPosition(vec2_sfml(m_pos));
  m_shape.setFillColor(color);

  m_cooldown = cooldown;
}

void Pursuer::update(float dt, Genome &genome)
{
  if ((m_counter += dt) >= m_cooldown) {
    m_counter = 0.0f;
    Vec2f acc = genome.next();
    m_vel += acc;
  } 

  m_pos += m_vel * dt;
  m_shape.setPosition(vec2_sfml(m_pos));
  
  if (m_vel.mag() != 0) 
    m_shape.setRotation(rad_degrees(m_vel.angle()));
}

void Pursuer::reset()
{
  m_pos = m_start_pos;
  m_vel = Vec2f(0.0f, 0.0f);
  m_shape.setPosition(vec2_sfml(m_pos));
  m_shape.setRotation(90);
}

void Pursuer::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
  target.draw(m_shape, states);
}

