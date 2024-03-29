#pragma once
#include "../Enty.hpp"
#include "../Game_State.hpp"
#include "../Levels/FirstLevel.hpp"
#define ITENS_PAUSE_MENU 3

namespace Levels {class SecondLevel;}

namespace Menus
{
    class PauseMenu : public Enty, public Game_State
    {
    private:
        Game *pGame;
        sf::Text text[ITENS_PAUSE_MENU];
        sf::Font font;
        sf::RectangleShape backgroundRectangle;
        sf::Texture backgroundTexture;
        int level;
        Levels::FirstLevel *levelOne;
        Levels::SecondLevel *levelTwo;

    public:
        /*CONSTRUCTORS & DESTRUCTORS*/
        PauseMenu(Game *pg, Levels::FirstLevel *lvl);
        PauseMenu(Game *pg, Levels::SecondLevel *level);
        ~PauseMenu();

        /*SETTERS & GETTERS*/
        sf::RectangleShape getRectangleShape() const;
        void setText();
        void setMenuState(bool menu_state);
        bool getMenuState() const;
        void setBackground();
        void setLevel(int lvl);
        void getLevel();

        /*METHODS*/
        void drawThis(Managers::Graphic_Manager *pGM); // drawItself() -> talvez seja um nome melhor!
        void init();
        void keyPressedAction(sf::Event event);
        void saveGame();
        void saveLevelOne();
        void saveMovingEntities(ofstream *saver);
        void saveStaticEntities(ofstream *saver);
        void saveLevelTwo();

        // Polimorfismo Game_State()!
        /*---------------------------*/
        void draw();
        void update(double timeFraction);
        void input();
    };
}