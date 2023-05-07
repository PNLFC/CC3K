//
//  main.cpp
//  ChamberCrawler3000
//
//  Created by Charles Nwodo on 2015-03-29.
//  Copyright (c) 2015 Reel. All rights reserved.
//

#include <iostream>
#include <string>
#include <cstdlib>

#include "grid.h"
#include "character/player/player.h"
#include "character/player/human.h"
#include "character/player/elf.h"
#include "character/player/orc.h"
#include "character/player/dwarf.h"
#include "character/player/MagicDecorator.h"
#include "utils/util.h"

using namespace std;

void passage()
{
    cout << endl
         << "CHAMBER CRAWLER 3000\n\
    Designed and produced by Charles Nwodo.\n\
    The commands are as follows:\n\
    Movement: (no,so,ea,we,nw,ne,sw,se)\n\
    Attack: a + direction\n\
    Potion: u + direction\n\
    To Attack and collect item you must be within 1 block\n\
    Restart: r, Quit: q"
         << endl
         << endl;
}

void win()
{
    cout << "CONGRATULATIONS!\n"
         << endl;
}

void quit()
{
    cout << endl
         << "You suck at this game \n\
    Go get better and come back next time."
         << endl;
}

char selectplayer()
{
    char p;
    cout << "Please select a race: " << endl;
    cout << "   human: 'h', orc: 'o', elf: 'e', dwarf " << endl;
    cin >> p;
    while (p != 'h' && p != 'o' && p != 'e' && p != 'd')
    {
        cout << "Bad Selection. Try again" << endl;
        cin >> p;
    }
    return p;
}

player *generateplayer(char race, std::vector<int> r)
{
    switch (race)
    {
    case 'h':
        return new human(r);
    case 'e':
        return new elf(r);
    case 'o':
        return new orc(r);
    case 'd':
        return new dwarf(r);
    default:
        cerr << "Wrong input";
        return NULL;
    }
}

int main(int argc, char *argv[])
{
    string file;
    if (argc == 2)
    {
        file = argv[1];
        srand(time(NULL));
    }
    else
    {
        file = "map.txt";
    }
    srand(static_cast<unsigned int>(time(NULL))); //  using the time seed from srand
    passage();
    grid *floor = new grid(file);
    char race = selectplayer();
    floor->generateboard();
    std::vector<int> position = floor->createplayerposition();
    player *controller = generateplayer(race, position);
    floor->addControllerToGrid(controller);
    floor->print();

    string d;
    cin >> d;
    while (controller->getfloor() != 5)
    {
        cout << controller->getfloor() << "floor" << endl;
        while (!cin.eof())
        {
            if (d == "q")
            {
                break;
            }
            else if (d == "a")
            {
                d.erase(0, 1);
                floor->attackbyplayer();
            }
            else if (d == "u")
            {
                d.erase(0, 1);
                cout << "Enter direction" << endl;
                cin >> d;
                if (cc3k::isCorrectDirection(d))
                {
                    std::vector<int> newPosition = cc3k::movement(d, floor->controller->getpoint());
                    potion *potionInTile = floor->getPotion(newPosition);
                    if (!!potionInTile)
                    {
                        if (potionInTile->permanent())
                        {
                            cout << "potion permanent" << potionInTile->getmutator() << potionInTile->gettype() << endl;
                            potionInTile->usepotion(floor->controller);
                            floor->pickPotion(newPosition, potionInTile);
                        }
                        else
                        {
                            // singleton pattern
                            cout << "potion non-permanent" << endl;
                            player *decoratedPlayer = new MagicDecorator(floor->controller, potionInTile);
                            floor->setController(decoratedPlayer);
                            floor->pickPotion(newPosition, potionInTile);
                        }
                    }
                    d.erase(0, 1);
                }
            }
            else
            {
                while (!(cc3k::isCorrectDirection(d) || d == "r" || floor->isPlayerDead()))
                {
                    cin.clear();
                    cout << "Enter a valid command: ";
                    cin >> d;
                }
            }

            if (floor->isPlayerDead())
            {
                cout << "You have been defeated in battle" << endl;
                d = "q";
                break;
            }

            if (floor->shouldUpdateFloor(d))
            {
                controller->eraseAllNotifications();
                delete floor;
                break;
            }

            if (floor->isValid(d))
            {
                floor->moveplayer(d);
                floor->moveenemies();
            }

            floor->print();
            cin >> d;
        }
        cout << d << endl;
        if (d == "q")
        {
            quit();
            break;
        }
        floor = new grid(file);
        floor->generateboard();
        position = floor->createplayerposition();
        controller->setpoint(position);
        floor->addControllerToGrid(controller);
        floor->print();
        d.erase(0, 2);
        cin >> d;
    }
    if (d != "q")
    {
        win();
    }
    cout << "here" << endl;
    delete floor;
    delete controller;
    return 0;
}