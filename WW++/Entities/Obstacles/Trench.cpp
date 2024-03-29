#include "Trench.hpp"
#define TRENCH_SLOWNESS 2

namespace Entities
{
    namespace Obstacles
    {
        Trench::Trench(int ident, double px, double py, double sx, double sy, double vx, double vy) : Obstacle(ident, px, py, sx, sy, vx, vy)
        {
            slowness = TRENCH_SLOWNESS;
            crossable = 1;
            weight = 0.3;
        }
        Trench::~Trench()
        {
        }

        double Trench::getSlowness()
        {
            return slowness + weight;
        }

        void Trench::update(double timeFraction)
        {
            velocity_x = 0.0f;
            velocity_y += 9.8f * timeFraction;
            position_x += (velocity_x);
            position_y += (velocity_y);
            retangulo.setPosition(sf::Vector2f(position_x, position_y));
        }
        void Trench::init()
        {
            text.loadFromFile("Images/trench.png");
            retangulo = sf::RectangleShape(sf::Vector2f(size_x, size_y));
            retangulo.setTexture(&text);
            retangulo.setPosition(sf::Vector2f(position_x, position_y));
        }
        void Trench::collide(Entity *ent2, double inter_x, double inter_y)
        {
            int id = ent2->getId();

            if (id == 3)
                collisionMovement(ent2, inter_x, inter_y);
        }

    }
}
