#pragma once
#include <SFML/Graphics.hpp>


class Obstacle : public sf::Drawable
{
  public:
    Obstacle() = default;
    void set_color();
    void set_start(sf::Vector2f start);
    void set_stop(sf::Vector2f stop);
    sf::FloatRect get_bounds() const;
  private:
    sf::FloatRect m_bounds;
    sf::RectangleShape m_shape;
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};

