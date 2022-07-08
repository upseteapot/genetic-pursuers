#pragma once
#include <SFML/Graphics.hpp>
#include "math/vec2.hpp"
#include "genetic-algo/genome.hpp"
#include "graphics/target.hpp"



class Pursuer : public sf::Drawable
{
  public:
    Pursuer() = default;
    void setup(Vec2f start_pos, float cooldown);
    void set_color(sf::Color color);
    void update(float dt, const genalgo::Genome &genome);
    void reset();
    void reach_target(const Target &target, bool is_best);
    void collided(sf::FloatRect bounds, bool is_best);
    void check_bounds(sf::Vector2f size, bool is_best);
    bool is_alive() const;
    bool has_reached_target() const;
    const Vec2f& get_pos() const;
    float get_global_counter() const;
  private:
    std::size_t m_index = 0;
    float m_global_counter = 0.0f;
    bool m_has_reached_target = false;
    bool m_is_alive = true;
    float m_cooldown;
    float m_counter = 0.0f;
    float m_radius = 15.0f;
    Vec2f m_start_pos, m_pos, m_vel;
    sf::ConvexShape m_shape;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};

