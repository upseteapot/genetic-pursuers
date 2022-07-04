#include "graphics/target.hpp"


void Target::setup(Vec2f pos, sf::Color color)
{
  m_pos = pos;

  m_shape.setRadius(m_radius);
  m_shape.setOrigin(sf::Vector2f(m_radius, m_radius));
  m_shape.setPosition(vec2_sfml(m_pos));
  m_shape.setFillColor(color);
}

float Target::get_radius() const
{
  return m_radius;
}

const Vec2f& Target::get_pos() const 
{
  return m_pos;
}

void Target::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
  target.draw(m_shape, states);
}

