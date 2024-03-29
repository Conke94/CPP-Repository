#include "Menu.hpp"
#include "../Game.hpp"

namespace Menus
{
    /*CONSTRUCTORS & DESTRUCTORS*/
    Menu::Menu(Game *pg) : MenuCore(pg)
    {
        setText();
        setBackground();
    }
    Menu::~Menu()
    {
    }

    /*SETTERS & GETTERS*/
    void Menu::setText()
    {
        if (!font.loadFromFile("Font/PIXEARG_.TTF"))
        {
            cout << "error" << endl;
            exit(1);
        }

        Title.setFont(font);
        Title.setCharacterSize(40);
        Title.setFillColor(sf::Color::White);
        Title.setString("WWII++"); // 1 item
        Title.setPosition(sf::Vector2f(600, 30));

        text[0].setFont(font);
        text[0].setCharacterSize(35);
        text[0].setFillColor(sf::Color::Red);
        text[0].setString("2 - First Level (1 player)"); // 1 item
        text[0].setPosition(sf::Vector2f(380, 220));

        text[1].setFont(font);
        text[1].setCharacterSize(35);
        text[1].setFillColor(sf::Color::Red);
        text[1].setString("3 - Second Level (1 player)"); // 2 item ...
        text[1].setPosition(sf::Vector2f(350, 320));  // Janela 1280 x 720.

        text[2].setFont(font);
        text[2].setCharacterSize(35);
        text[2].setFillColor(sf::Color::Red);
        text[2].setString("6 - Ranking");
        text[2].setPosition(sf::Vector2f(500, 620));

        text[3].setFont(font);
        text[3].setCharacterSize(35);
        text[3].setFillColor(sf::Color::Red);
        text[3].setString("1 - Resume");
        text[3].setPosition(sf::Vector2f(500, 720));

        text[4].setFont(font);
        text[4].setCharacterSize(35);
        text[4].setFillColor(sf::Color::Red);
        text[4].setString("4 - First Leval (2 players)");
        text[4].setPosition(sf::Vector2f(350, 420));

        text[5].setFont(font);
        text[5].setCharacterSize(35);
        text[5].setFillColor(sf::Color::Red);
        text[5].setString("5 - Second Leval (2 players)");
        text[5].setPosition(sf::Vector2f(320, 520));

        text[6].setFont(font);
        text[6].setCharacterSize(35);
        text[6].setFillColor(sf::Color::Red);
        text[6].setString("1 - Resume");
        text[6].setPosition(sf::Vector2f(520, 120));
    }

    /*METHODS*/
    void Menu::drawThis(Managers::Graphic_Manager *pGM)
    {
        pGM->getWindow()->draw(backgroundRectangle);

        pGM->getWindow()->draw(Title);

        for (int i = 0; i < MAX_NUMBER_OF_ITENS; i++)
        {
            pGM->getWindow()->draw(text[i]);
        }
    }
    void Menu::draw()
    {
        drawThis(pGM);
    }
    void Menu::setBackground()
    {
        backgroundTexture.loadFromFile("Images/backgroundPauseMenu.jpg");
        backgroundRectangle = sf::RectangleShape(sf::Vector2f(1280, 720));
        backgroundRectangle.setTexture(&backgroundTexture);
        backgroundRectangle.setPosition(sf::Vector2f(0, 0));
    }
    void Menu::input()
    {
        sf::Event event;
        while ((pGM->getWindow())->pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
            {
                (pGM->getWindow())->close();
            }
            break;

            case sf::Event::KeyPressed:
            {
                keyPressedAction(event);
            }
            break;

            default:
            {
            }
            break;
            }
        }
    }
    void Menu::keyPressedAction(sf::Event event)
    {
        switch (event.key.code)
        {
        case sf::Keyboard::Num1:
        {
            recover();
        }
        break;
        case sf::Keyboard::Num2:
        {
            pGame->pushState(new Levels::FirstLevel(pGame, 1, 1));
        }
        break;
        case sf::Keyboard::Num3:
        {
            pGame->pushState(new Levels::SecondLevel(pGame, 1, 100.0));
        }
        break;
        case sf::Keyboard::Num4:
        {
            pGame->pushState(new Levels::FirstLevel(pGame, 1, 2));
        }
        break;
        case sf::Keyboard::Num6:
        {
            pGame->pushState(new Leaderboard(pGame));
        }
        break;
        case sf::Keyboard::Num5:
        {
            pGame->pushState(new Levels::SecondLevel(pGame, 2, 100.0, 100.0));
        }
        break;
        }
    }
    void Menu::recover()
    {
        int level, nP, diff, id, hp, size;
        double px, py, vx, vy;
        ifstream recover("Data/gameSave.dat", ios::in);

        try
        {
            if (!recover)
                throw 1;
            else
                recover >> level;
        }

        catch (int error)
        {
            if (error == 1)
            {
                cerr << " Arquivo não pode ser aberto " << endl;
                fflush(stdin);
                getchar();
                return;
            }
        }

        

        if (level == 1)
        {
            recover >> diff;
            recover >> nP;
            recover >> size;
            Levels::FirstLevel *fl = new Levels::FirstLevel(pGame, diff, nP, size);
            
            pGame->pushState(fl);
            
        }
        else
        {
            recover >> nP;
            recover >> size;
            
            Levels::SecondLevel *sl = new Levels::SecondLevel(pGame, nP, size);
            
            pGame->pushState(sl);
            
        }

        recover.close();
    }

}
