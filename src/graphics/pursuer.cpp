#include "graphics/pursuer.hpp"


void Pursuer::setup(Vec2f start_pos, float cooldown)
{
  m_start_pos = start_pos;

  m_shape.setPointCount(3);
  m_shape.setPoint(0, sf::Vector2f(-m_radius,  m_radius / 2.f));
  m_shape.setPoint(1, sf::Vector2f(-m_radius, -m_radius / 2.f));
  m_shape.setPoint(2, sf::Vector2f( m_radius,  0.0f));
  
  m_shape.setPosition(vec2_sfml(m_pos));
  m_shape.setFillColor(sf::Color(150, 150, 140, 90));

  m_cooldown = cooldown;
}

void Pursuer::set_color(sf::Color color)
{
  m_shape.setFillColor(color);
}

void Pursuer::update(float dt, const genalgo::Genome &genome)
{
  if (!m_collided && m_is_alive) {
    m_global_counter += dt;
    if ((m_counter += dt) >= m_cooldown) {
      m_counter = 0.0f;
      Vec2f acc = Vec2f::polar((float)genome[m_index] * 50.0f, (float)genome[m_index+1] * 2.f * 3.14159265f);
      m_vel += acc;
      m_index += 2;
    } 

    m_pos += m_vel * dt;
    m_shape.setPosition(vec2_sfml(m_pos));

    if (m_vel.mag() != 0) 
      m_shape.setRotation(rad_degrees(m_vel.angle()));
  }
}

void Pursuer::reset()
{
  m_index = 0;
  m_pos = m_start_pos;
  m_vel = Vec2f(0.0f, 0.0f);
  m_global_counter = 0.0f;
  m_collided = false;
  m_is_alive = true;
  m_shape.setPosition(vec2_sfml(m_pos));
  m_shape.setRotation(90);
  m_shape.setFillColor(sf::Color(150, 150, 140, 90));
}

void Pursuer::collided(const Target &target, bool is_best)
{
  if (Vec2f::dist(target.get_pos(), m_pos) < target.get_radius()) {
    m_collided = true;
    if (!is_best)
      m_shape.setFillColor(sf::Color(42, 157, 143, 90));
  }
}

void Pursuer::check_bounds(sf::Vector2f size, bool is_best)
{
  m_is_alive = -size.x / 2.f < m_pos.x && m_pos.x < size.x / 2.f &&
               -size.y / 2.f < m_pos.y && m_pos.y < size.y / 2.f;
  if (!m_is_alive && !is_best)
      m_shape.setFillColor(sf::Color(42, 157, 143, 90));
}

bool Pursuer::is_alive() const
{
  return m_is_alive;
}

const Vec2f& Pursuer::get_pos() const
{
  return m_pos;
}

float Pursuer::get_global_counter() const
{
  return m_global_counter;
}

void Pursuer::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
  target.draw(m_shape, states);
}

