#include "graphics/obstacle.hpp"

void Obstacle::set_color()
{
  m_shape.setFillColor(sf::Color(127, 127, 127));
}

void Obstacle::set_start(sf::Vector2f start)
{
  m_shape.setPosition(start);
}

void Obstacle::set_stop(sf::Vector2f stop)
{
  m_shape.setSize(stop - m_shape.getPosition());
}

sf::FloatRect Obstacle::get_bounds() const
{
  return m_shape.getGlobalBounds();
}


void Obstacle::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
  target.draw(m_shape, states);
}

