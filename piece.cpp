#include "piece.hpp"

bool piece::floor = true;

piece::piece(int color, int x) : sf::CircleShape(PIECE_RADIUS), vy{0.f} {
    this->setPosition(x, 0);
    this->setFillColor(color == 1 ? sf::Color::Red : sf::Color::Yellow);
}

piece::~piece() {}

void piece::updatePhysics(std::vector<std::unique_ptr<piece>> &pieces) {
    // update velocity
    vy += GRAVITY;

    // potential new y position
    float py = this->getPosition().y + vy;
    float px = this->getPosition().x;

    // floor collisions
    if (floor && py >= HEIGHT - (2 * HITBOX_RADIUS)) {
        this->setPosition(sf::Vector2f(px, HEIGHT - (2 * HITBOX_RADIUS)));
        vy *= -0.5;
    } else {
        // Other piece collisions
        bool collided = false;
        for (std::unique_ptr<piece> &piece_ptr : pieces) {
            if (piece_ptr.get() != this &&
                piece_ptr->getPosition().x == this->getPosition().x &&
                py >= piece_ptr->getPosition().y - (PADDING) - (2 * HITBOX_RADIUS)) {
                this->setPosition(sf::Vector2f(px, piece_ptr->getPosition().y - (PADDING) - (2 * HITBOX_RADIUS)));
                vy *= -0.5;
                collided = true;
                break;
            }
        }
        if (!collided) {
            this->move(0.f, vy);
        }
    }
}

void piece::drawTo(sf::RenderWindow &window, sf::Font &font) {
    window.draw(*this);
}