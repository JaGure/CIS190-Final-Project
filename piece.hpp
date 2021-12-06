#ifndef PIECE_HPP
#define PIECE_HPP

#include "consts.hpp"
#include <SFML/Graphics.hpp>

// Defines a drawable piece with physics.
class piece : public sf::CircleShape {
  private:
    float vy;

  public:
    static bool floor;
    piece(int color, int x);
    virtual ~piece();
    void updatePhysics(std::vector<std::unique_ptr<piece>> &);
    void drawTo(sf::RenderWindow &, sf::Font &);
};

#endif // PIECE_HPP