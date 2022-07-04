#pragma once
#include <SFML/Graphics.hpp>
#include "math/vec2.hpp"
#include "genetic/genome.hpp"
#include "graphics/target.hpp"


class Pursuer : public sf::Drawable
{
  public:
    Pursuer() = default;
    void setup(Vec2f start_pos, float cooldown);
    void set_color(sf::Color color);
    void update(float dt, Genome &genome);
    void reset();
    void collided(const Target &target, bool is_best);
    bool has_collided() const;
    const Vec2f& get_pos() const;
    float get_global_counter() const;
  private:
    float m_global_counter = 0.0f;
    bool m_collided = false;
    float m_cooldown;
    float m_counter = 0.0f;
    float m_radius = 15.0f;
    Vec2f m_start_pos, m_pos, m_vel;
    sf::ConvexShape m_shape;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};

