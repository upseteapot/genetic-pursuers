#pragma once
#include <SFML/Graphics.hpp>
#include "math/vec2.hpp"
#include "genetic/genome.hpp"


class Pursuer : public sf::Drawable
{
  public:
    Pursuer() = default;
    void setup(Vec2f start_pos, sf::Color color, float cooldown);
    void set_color(sf::Color color);
    void update(float dt, Genome &genome);
    void reset();
    const Vec2f& get_pos() const;
  private:
    float m_cooldown;
    float m_counter = 0.0f;
    float m_radius = 15.0f;
    Vec2f m_start_pos, m_pos, m_vel;
    sf::ConvexShape m_shape;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};

