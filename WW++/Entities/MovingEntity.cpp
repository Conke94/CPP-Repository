#include "MovingEntity.hpp"

namespace Entities
{

    /*CONSTRUCTORS & DESTRUCTORS*/
    MovingEntity::MovingEntity(int ident, double px, double py, double sx, double sy, double vx, double vy, int dam) : Entity(ident, px, py, sx, sy, vx, vy)
    {
        damage = dam;
        leftDirection = false;
    }
    MovingEntity::~MovingEntity()
    {
    }

    /*SETTERS & GETTERS*/
    int MovingEntity::getDamage() const
    {
        return damage;
    }
    bool MovingEntity::getLeftDirection()
    {
        return leftDirection;
    }
    void MovingEntity::setLeftDirection(bool active)
    {
        leftDirection = active;
    }

    /*METHODS*/
    void MovingEntity::collisionMovement(Entity *ent2, double intersection_x, double intersection_y)
    {
        if (intersection_x < intersection_y)
        {
            velocity_x = 0.0;
            if (position_x > ent2->getPosition_x())
                position_x += intersection_x;
            else
                position_x -= intersection_x;
        }
        else
        {
            velocity_y = 0.0;
            if (position_y > ent2->getPosition_y())
                position_y += intersection_y;
            else
                position_y -= intersection_y;
        }
    }
}