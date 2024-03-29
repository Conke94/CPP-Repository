#include "Player.hpp"
#include "../Projectile.hpp"

#define PLAYER_VELOCITY 1.5
#define PLAYER_JUMP_HEIGHT 83.0
#define PLAYER_ATTACK_RANGE 20
#define PLAYER_DAMAGE_COOLDOWN 0.5
#define PLAYER_ATTACK_COOLDOWN 0.3
#define PLAYER_BULLET_SPEED 6
#define PLAYER_DAMAGE 10

namespace Entities
{
    namespace Characters
    {

        Player::Player(int ident, double px, double py, double sx, double sy, double vx, double vy, int hp) : Character(ident, px, py, sx, sy, vx, vy, hp, PLAYER_DAMAGE, PLAYER_ATTACK_COOLDOWN),
                                                                                                              attackRange(PLAYER_ATTACK_RANGE)
        {
            dead = false;
            Copper_Bullet = nullptr;
            Copper_Bullet = new Projectile(4, 0.0, -65.0, 4, 4, PLAYER_BULLET_SPEED, 0, PLAYER_DAMAGE);
            velocity_x = 0;
            velocity_y = 0;
            damageCooldownTimer = 0;
            aceleration = 1;
            points = 100;
            player2 = false;
        }

        Player::~Player()
        {
            Copper_Bullet = nullptr;
        }

        /*SETTER & GETTERS*/
        bool Player::getPlayerState()
        {
            return dead;
        }

        void Player::setPlayerState(bool condition)
        {
            dead = condition;
        }

        void Player::setVelocity(double vx, double vy)
        {
            velocity_x = vx;
            velocity_y = vy;
        }

        double Player::getVelocity_x()
        {
            return velocity_x;
        }

        double Player::getVelocity_y()
        {
            return velocity_y;
        }

        void Player::setVelocity_x(double vx)
        {
            velocity_x = vx;
        }

        void Player::setVelocity_y(double vy)
        {
            velocity_y = vy;
        }

        void Player::receiveDamage(int dam)
        {
            health -= dam;
            if (health <= 0)
            {
                dead = true;
                position_y = 1000;
            }
        }
        Projectile *Player::getBullet()
        {
            return Copper_Bullet;
        }
        double Player::getPoints()
        {
            return points;
        }
        void Player::setPoints(double pt)
        {
            points = pt;
        }

        bool Player::setPlayer2(bool condition)
        {
            player2 = condition;
        }

        /*METHODS*/
        void Player::init()
        {
            text.loadFromFile("Images/player.png");
            retangulo = sf::RectangleShape(sf::Vector2f(size_x, size_y));
            retangulo.setTexture(&text);
            retangulo.setPosition(sf::Vector2f(position_x, position_y));
            if(player2) 
                retangulo.setFillColor(sf::Color(87,122,228));
        }

        void Player::update(double timeFraction)
        {
            Character::increaseAttackTimer(timeFraction);

            velocity_x = PLAYER_VELOCITY * aceleration;

            if (getLeftDirection())
                velocity_x *= (-1);

            velocity_y += 9.8 * timeFraction; // Aqui.

            position_x += (velocity_x);
            position_y += (velocity_y);

            retangulo.setPosition(sf::Vector2f(position_x, position_y));

            damageCooldownTimer += timeFraction;
        }

        void Player::collide(Entity *ent2, double inter_x, double inter_y)
        {
            int id = ent2->getId();

            if (id == 4)
            {
                Character *pAttacker = static_cast<Character *>(ent2);
                receiveDamage(pAttacker->getDamage());
            }

            if (id == 3)
            {
                collisionMovement(ent2, inter_x, inter_y);
                aceleration = 1;
            }

            if (id == 2)
            {
                collisionMovement(ent2, inter_x, inter_y);
                if (damageCooldownTimer >= PLAYER_DAMAGE_COOLDOWN)
                {
                    Obstacles::Box *pAttacker = static_cast<Obstacles::Box *>(ent2);
                    receiveDamage(pAttacker->getDamage());
                    damageCooldownTimer = 0.0;
                }
            }

            if (id == 6)
            {
                Obstacles::Trench *pAttacker = static_cast<Obstacles::Trench *>(ent2);
                aceleration = 1 / pAttacker->getSlowness();
            }

            if (id == 7)
            {
                Obstacles::Cannon *pAttacker = static_cast<Obstacles::Cannon *>(ent2);
                aceleration = pAttacker->getAcceleration();
            }

            if (id == 1)
            {
                collisionMovement(ent2, inter_x, inter_y);
            }

            if (id == 5)
            {
                collisionMovement(ent2, inter_x, inter_y);
            }

            if (id == 9)
            {
                collisionMovement(ent2, inter_x, inter_y);
            }

            if(id == 0)
                collisionMovement(ent2, inter_x, inter_y);

        }
        void Player::jump(double timeFraction)
        {
            if (!velocity_y)
                velocity_y = -sqrtf(PLAYER_JUMP_HEIGHT / 35 * 2 * 9.8);
            // Divide-se por 35 pois as dimensões do jogo estão numa escala 10x maior que a proporção da velocidade (valores reais).
        }

        void Player::attack()
        {
            if (this->canAttack())
            {
                Copper_Bullet->setActive(1);
                Character::resetAttackTimer();

                if (leftDirection)
                    Copper_Bullet->projectileReset(position_x - 1.0, position_y, -PLAYER_BULLET_SPEED, 0);
                else
                    Copper_Bullet->projectileReset(position_x + size_x + 1.0, position_y, PLAYER_BULLET_SPEED, 0);
            }
        }

        bool Player::canAttack()
        {
            if (!Copper_Bullet->getActive() && cooldownAttackTimer > attackCooldown)
                return 1;
            return 0;
        }

        void Player::operator-(double value)
        {
            points -= value;
        }
        void Player::operator+(double value)
        {
            points += value;
        }
    }
}
