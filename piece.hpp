#ifndef PIECE_HPP
#define PIECE_HPP

#include "consts.hpp"
#include <SFML/Graphics.hpp>

// Defines a drawable piece with physics.
class piece : public sf::CircleShape
{
private:
  float vy; // velocity in the y-direction

public:
  bool stopped; // if done falling
  static bool floor;
  piece(int color, int x);
  virtual ~piece();
  void updatePhysics(std::vector<std::unique_ptr<piece>> &);
  void drawTo(sf::RenderWindow &, sf::Font &); // draws this piece to the given window
};

#endif // PIECE_HPP