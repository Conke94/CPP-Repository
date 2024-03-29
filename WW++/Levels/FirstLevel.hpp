#pragma once
#include "Level.hpp"

namespace Levels
{
    class FirstLevel : public Level
    {
    private:
        Managers::Collision_Manager CM; // criar um singleton. -> não faz sentido nenhum. (PENSAR!)
        int *entitiesQuantity;
        int difficulty;

        sf::Sprite backgroundSprite;
        sf::Texture backgroundTexture;

    public:
        /*CONSTRUCTORS & DESTRUCTORS*/
        FirstLevel(Game *pg, int diff, int np);
        FirstLevel(Game *pg, int diff, int np, int rec);
        ~FirstLevel();

        /*SETTERS & GETTERS*/
        int *getEntitiesQuantity();
        int getDifficulty();
        void setBackground();

        /*METHODS*/
        void update(double timeFraction);
        void input();
        void draw(); // Implementar
        void keyPressedAction(sf::Event event);
        void CheckPlayerState();
        void endCurrentState();
        void CheckLevelEnd();
        void goToLevel2();
        /*------------------------------------------------*/
        void init();                                     // pensar!!
        void drawThis(Managers::Graphic_Manager *pGM) {} // pensar!!
        /*------------------------------------------------*/
        void createEnemies();
        void createPlatforms();
        void createTrenchs();
        void createCannons();
        void createBoxes();
        void createSnipers();
        void createPlayers();
        void recoverPlayer(ifstream *recover, int color);

        /*SETTERS & GETTERS*/
        sf::RectangleShape getRectangleShape() const {} // pensar sobre essa função
    };
}