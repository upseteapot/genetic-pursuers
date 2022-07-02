#include <SFML/Graphics.hpp>
#include <random>
#include <time.h>

#include "graphics/target.hpp"
#include "graphics/pursuer.hpp"


int main(void)
{
  srand(time(0));

  sf::Vector2f size = {1920, 1080};

  int style = sf::Style::Resize | sf::Style::Close | sf::Style::Titlebar;
  sf::VideoMode shape(size.x, size.y);
  sf::ContextSettings context;
  context.antialiasingLevel = 4;
  
  sf::RenderWindow renderer(shape, "Target", style, context);
  renderer.setFramerateLimit(60);
  renderer.setKeyRepeatEnabled(false);

  sf::View view;
  view.setSize({size.x, -size.y});
  view.setCenter(sf::Vector2f(0.0f, 0.0f));
  
  float simulation_time = 5.0f;
  float pursuer_cooldown = 0.5f;
  float counter = 0.0f;
  bool paused = true;
  
  Target target;
  target.setup(Vec2f(0.0f, 400.0f), sf::Color::Red);
  
  Genome genome;
  genome.setup((simulation_time - 1) / pursuer_cooldown);
  genome.randomize(50.0f);

  Pursuer pursuer;
  pursuer.setup(Vec2f(0.0f, -400.0f), sf::Color::Green, pursuer_cooldown);
  pursuer.reset();

  sf::Event event;
  sf::Clock clock;
  while (renderer.isOpen()) {
    float dt = clock.restart().asSeconds();

    // Handle window events.
    while (renderer.pollEvent(event)) {
      switch (event.type) {
        case sf::Event::Closed:
          renderer.close();
          break;
        case sf::Event::Resized:
          size = {(float)event.size.width, (float)event.size.height};
          view.setSize({size.x, -size.y});
          renderer.setView(view);
          break;
        case sf::Event::KeyPressed:
          switch (event.key.code) {
            case sf::Keyboard::Space:
              paused = !paused;
            default:
              break;
          }
          break;
        default:
          break;
      }
    }
    
    if ((counter += dt) >= simulation_time) {
      counter = 0.0f;
      paused = true;
      pursuer.reset();
    }

    if (!paused) 
      pursuer.update(dt, genome);

    renderer.clear(sf::Color::Black);
    renderer.draw(target);
    renderer.draw(pursuer);
    renderer.display();

  }

  return 0;

}

