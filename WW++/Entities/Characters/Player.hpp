#include "Character.hpp"
#include "../Obstacles/Box.hpp"
#include "../Obstacles/Cannon.hpp"
#include "../Obstacles/Trench.hpp"
#include <math.h>
#pragma once

namespace Entities {class Projectile;}

namespace Entities
{
    namespace Characters
    {

        class Player : public Character
        {
        private:
            const int attackRange;
            double damageCooldownTimer;
            double aceleration;

            bool dead;
            Projectile *Copper_Bullet;

            bool player2;

            double points;

        public:
            /*CONSTRUCTORS & DESTRUCTORS*/
            Player(int ident = 0, double px = 0.0f, double py = 0.0f, double sx = 0.0f, double sy = 0.0f, double vx = 0.0f, double vy = 0.0f, int hp = 10);
            ~Player();

            /*SETTERS & GETTERS*/
            bool getPlayerState();
            void setPlayerState(bool condition);
            void setVelocity(double vx, double vy);
            double getVelocity_y();
            double getVelocity_x();
            void setVelocity_x(double vx);
            void setVelocity_y(double vy);
            void receiveDamage(int dam);
            Projectile *getBullet();
            double getPoints();
            void setPoints(double pt);
            bool setPlayer2(bool condition);

            /*METHODS*/
            bool canAttack();
            void attack();
            void init();
            void update(double timeFraction);
            void collide(Entity *ent2, double inter_x, double inter_y);
            void jump(double timeFraction);

            void operator-(double value);
            void operator+(double value);
        };
    }
}