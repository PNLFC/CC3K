//
//  grid.cc
//  ChamberCrawler3000
//
//  Created by Charles Nwodo on 2015-04-03.
//  Copyright (c) 2015 Reel. All rights reserved.
//

#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <stdlib.h>
#include <time.h>
#include "chamber.h"
#include "grid.h"
#include "character/enemy/enemy.h"
#include "item/potion/potion.h"
#include "character/enemy/vampire.h"
#include "character/enemy/werewolf.h"
#include "character/enemy/goblin.h"
#include "character/enemy/troll.h"
#include "character/enemy/phoenix.h"
#include "character/enemy/merchant.h"
#include "character/enemy/dragon.h"
#include "item/treasure/treasure.h"
#include "character/player/player.h"
#include "character/player/MagicDecorator.h"
#include "item/potion/RH.h"
#include "item/potion/BA.h"
#include "item/potion/BD.h"
#include "item/potion/PH.h"
#include "item/potion/WA.h"
#include "item/potion/WD.h"
#include "item/treasure/NH.h"
#include "item/treasure/MH.h"
#include "item/treasure/SH.h"
#include "item/treasure/DH.h"
#include "utils/util.h"

using namespace std;

grid::grid(string file) : file(file)
{
    controller = NULL;
    chambers = new chamber *[5];
    potionstore = new potion *[10];
    goldchest = new treasure *[10];
    foes = new enemy *[20];
    dead = false;
    ifstream filestream(file);
    string line;
    while (getline(filestream, line))
    {
        vector<char> row;
        int len = (int)line.length();
        row.reserve(len);
        for (int i = 0; i < len; ++i)
        {
            row.emplace_back(line[i]);
        }
        theDisplay.push_back(row);
    }
    preTile = '.';
}

grid::~grid()
{
    this->cleanboard();
    delete[] chambers;
    delete[] potionstore;
    delete[] goldchest;
    delete[] foes;
    MagicDecorator *player = dynamic_cast<MagicDecorator *>(controller);
    if (!!player)
    {
        cout << "here" << endl;
        delete player;
    }
}

void grid::cleanboard()
{
    for (int i = 0; i < 5; i++)
    {
        delete chambers[i];
    }
    for (int i = 0; i < 10; i++)
    {
        delete potionstore[i];
    }
    for (int i = 0; i < 20; i++)
    {
        delete foes[i];
    }
    for (int i = 0; i < dragons.size(); i++)
    {
        delete dragons[i];
    }
    while (!dragons.empty())
    {
        dragons.pop_back();
    }
    for (int i = 0; i < 10; i++)
    {
        delete goldchest[i];
    }
}

void grid::generate_foelist()
{
    for (int i = 0; i < 20; i++)
    {
        enemy *e = foes[i];
        foelist.push_back(e);
    }
}

void grid::generate_potionlist()
{
    for (int i = 0; i < 10; i++)
    {
        potion *p = potionstore[i];
        potionlist.push_back(p);
    }
}

void grid::generate_treaslist()
{
    for (int i = 0; i < 10; i++)
    {
        treasure *t = goldchest[i];
        treaslist.push_back(t);
    }
}

bool grid::isPlayerDead()
{
    return dead;
}

void grid::removefoe(enemy *e)
{
    std::vector<enemy *>::iterator it;
    for (it = foelist.begin(); it != foelist.end();)
    {
        vector<int> na = (*it)->getpoint();
        vector<int> ee = e->getpoint();
        if (na.at(0) == ee.at(0) && na.at(1) == ee.at(1))
        {
            it = foelist.erase(it);
            break;
        }
        else
        {
            ++it;
        }
    }
}

void grid::removepotion(potion *p)
{
    std::vector<potion *>::iterator it;
    for (it = potionlist.begin(); it != potionlist.end();)
    {
        vector<int> na = (*it)->getpoint();
        vector<int> pp = p->getpoint();
        if (na.at(0) == pp.at(0) && na.at(1) == pp.at(1))
        {
            it = potionlist.erase(it);
            cout << "potion removed" << endl;
            break;
        }
        else
        {
            ++it;
        }
    }
}

void grid::removetreas(treasure *t)
{
    for (int i = 0; i < 10; i++)
    {
        vector<int> na = treaslist.at(i)->getpoint();
        vector<int> tt = t->getpoint();
        if (na.at(0) == tt.at(0) && na.at(1) == tt.at(1))
        {
            treaslist.at(i) = NULL;
            break;
        }
    }
}

void grid::print()
{
    for (int i = 0; i < 25; i++)
    {
        string line(theDisplay[i].begin(), theDisplay[i].end());
        printf("%s\n", line.c_str());
    }
    cout << "Race: " << controller->getidentity() << " Gold: " << controller->getgold() << endl;
    cout << "HP: " << controller->gethp() << endl;
    cout << "Atk: " << controller->getatk() << endl;
    cout << "Def: " << controller->getdef() << endl;
}

bool grid::won()
{
    if (controller->getfloor() == 5)
    {
        return true;
    }
    return false;
}

void grid::generateboard()
{
    this->generatechambers();
    this->generatepotions();
    this->generatetreasures();
    this->generateenemies();
    this->generate_foelist();
    this->generate_potionlist();
    this->generate_treaslist();
}

void grid::generatechambers()
{
    for (int i = 0; i < 5; i++)
    {
        chambers[i] = new chamber(i, theDisplay);
    }
}

std::vector<int> grid::createplayerposition()
{
    int num = rand() % 5;
    std::vector<int> cor = chambers[num]->addtochamber('@');
    return cor;
}

void grid::setController(player *p)
{
    controller = p;
}

void grid::addControllerToGrid(player *p)
{
    controller = p;
    int a = rand() % 5;
    std::vector<int> point = controller->getpoint();
    while (chambers[a]->withinRange(point.at(0), point.at(1)))
    {
        a = rand() % 5;
    }
    chambers[a]->addtochamber('/');
    for (int y = 0; y < 20; y++)
    {
        enemy *foe = foelist.at(y);
        if (foe != NULL && controller->withinradius(foe->getpoint()))
        {
            controller->attacknotification(foe);
            cout << "attack notification from " << foe->getidentity() << " to kill player" << endl;
        }
    }
}

void grid::generateenemies()
{
    for (int i = 0; i < 20; i++)
    {
        int c = rand() % 5;
        int race = rand() % 18;
        if (race >= 0 && race < 4)
        {
            std::vector<int> random = chambers[c]->addtochamber('W');
            foes[i] = new werewolf(random);
        }
        else if (race >= 4 && race < 7)
        {
            std::vector<int> random = chambers[c]->addtochamber('V');
            foes[i] = new vampire(random);
        }
        else if (race >= 7 && race < 12)
        {
            std::vector<int> random = chambers[c]->addtochamber('N');
            foes[i] = new goblin(random);
        }
        else if (race >= 12 && race < 14)
        {
            std::vector<int> random = chambers[c]->addtochamber('T');
            foes[i] = new troll(random);
        }
        else if (race >= 14 && race < 16)
        {
            std::vector<int> random = chambers[c]->addtochamber('X');
            foes[i] = new phoenix(random);
        }
        else
        {
            std::vector<int> random = chambers[c]->addtochamber('M');
            foes[i] = new merchant(random);
        }
        // print the enemies in their points on the board
    }
}

void grid::generatepotions()
{
    for (int i = 0; i < 10; i++)
    {
        int c = rand() % 5;
        int race = rand() % 6;
        std::vector<int> random = chambers[c]->addtochamber('P');
        switch (race)
        {
        case 0:
            potionstore[i] = new RH(random);
            break;
        case 1:
            potionstore[i] = new BA(random);
            break;
        case 2:
            potionstore[i] = new BD(random);
            break;
        case 3:
            potionstore[i] = new PH(random);
            break;
        case 4:
            potionstore[i] = new WA(random);
            break;
        case 5:
            potionstore[i] = new WD(random);
            break;
        default:
            break;
        }
    }
}

void grid::generatetreasures()
{
    for (int i = 0; i < 10; i++)
    {
        int c = rand() % 5;
        int race = rand() % 8;
        if (race >= 0 && race <= 4)
        {
            std::vector<int> random = chambers[c]->addtochamber('G');
            goldchest[i] = new NH(random);
        }
        else if (race == 5)
        {
            std::vector<int> random = chambers[c]->addtochamber('G');
            goldchest[i] = new SH(random);
        }
        else
        {
            std::vector<int> dragonLocation;
            std::vector<int> random;
            dragonLocation.reserve(2);
            while (dragonLocation.empty())
            {
                random = chambers[c]->generatePos();
                for (int i = 0; i < 9; ++i)
                {
                    if (i == 4)
                        continue;
                    div_t divresult = div(i, 3);
                    int x = divresult.quot - 1 + random.at(0);
                    int y = divresult.rem - 1 + random.at(1);
                    if (theDisplay[x][y] == '.')
                    {
                        dragonLocation.emplace_back(x);
                        dragonLocation.emplace_back(y);
                        break;
                    }
                }
            }
            theDisplay[random.at(0)][random.at(1)] = 'G';
            theDisplay[dragonLocation.at(0)][dragonLocation.at(1)] = 'D';
            goldchest[i] = new DH(random);
            dragon *d = new dragon(dragonLocation);
            dragons.push_back(d);
        }
        // print the enemies in their points on the board
    }
}

void grid::moveplayer(string a)
{
    std::vector<int> r = controller->getpoint();
    vector<int> newPos = cc3k::movement(a, r);
    char temp = theDisplay[newPos.front()][newPos.back()]; // next char
    if (temp == 'G')
    { // next step is Gold
        int ind;
        for (ind = 0; ind < (int)treaslist.size(); ++ind)
        {
            std::vector<int> point = treaslist[ind]->getpoint();
            if (point.at(0) == newPos.front() && point.at(1) == newPos.back())
            {
                break;
            }
        }
        if (!treaslist[ind]->permanent())
        { // the gold is not dragon hoard or it's a dragon hoard(dragon is dead now)
            treaslist[ind]->usetreasure(controller);
            treaslist.erase(treaslist.begin() + ind);
            temp = '.';
        }
        else
        {
            cout << "The gold is guarded by the Dragon. You can't pick it." << endl;
        }
    }

    theDisplay[r.at(0)][r.at(1)] = preTile;
    controller->setpoint(newPos);
    theDisplay[newPos.at(0)][newPos.at(1)] = '@';
    preTile = temp;

    std::vector<enemy *>::iterator it1;
    for (it1 = foelist.begin(); it1 != foelist.end();)
    {
        if (!controller->withinradius((*it1)->getpoint()))
        {
            controller->removenotification(*it1);
        }
        ++it1;
    }
}

void grid::moveenemy(enemy *e)
{
    int a;
    std::vector<int> r = e->getpoint();
    int x = r.at(0);
    int y = r.at(1);
    for (int i = 0; i < 5; ++i)
    {
        a = rand() % 8;
        std::vector<int> pos = cc3k::movement(a, r);
        if (theDisplay[pos.at(0)][pos.at(1)] == '.')
        {
            e->setpoint(pos);
            theDisplay[pos.at(0)][pos.at(1)] = theDisplay[x][y];
            theDisplay[r.at(0)][r.at(1)] = '.';
            if (e->withinradius(controller->getpoint()))
            {
                controller->attacknotification(e);
                cout << "attack notification from " << e->getidentity() << "to kill player" << endl;
            }
            break;
        }
    }
}

void grid::moveenemies()
{
    std::vector<enemy *>::iterator it;
    std::vector<dragon *>::iterator dt;
    for (it = foelist.begin(); it != foelist.end();)
    {
        this->moveenemy(*it);
        ++it;
    }
    for (dt = dragons.begin(); dt != dragons.end();)
    {
        if ((*dt)->withinradius(controller->getpoint()))
        {
            controller->attacknotification(*dt);
            cout << "attack notification from " << (*dt)->getidentity() << "to kill player" << endl;
        }
        ++dt;
    }
}

void grid::turnmerchant()
{
    for (int i = 0; i < 20; i++)
    {
        if (foes[i]->getidentity() == "merchant")
        {
            foes[i]->turnonhostility();
        }
    }
}

void quitfloor()
{
    cout << endl
         << "You suck at this game \n\
    Go get better and come back next time."
         << endl;
}

void grid::attackbyplayer()
{
    string dir;
    while (!controller->attackers.empty())
    {
        cout << "Enter direction" << endl;
        cin >> dir;
        vector<int> pos = controller->getpoint();
        vector<int> newPos;
        if (cc3k::isCorrectDirection(dir))
        {
            newPos = cc3k::movement(dir, pos);
        }
        else
        {
            continue;
        }
        enemy *en = NULL;
        std::vector<enemy *>::iterator it;
        for (it = controller->attackers.begin(); it != controller->attackers.end();)
        {
            vector<int> apos = (*it)->getpoint();
            if (apos.at(0) == newPos.at(0) && apos.at(1) == newPos.at(1))
            {
                en = *it;
                break;
            }
            else
            {
                ++it;
            }
        }
        if (en != NULL)
        {
            int decrease = controller->attack(en);
            std::cout << "Enemy HP decreased by " << decrease << std::endl;
            decrease = en->attack(controller);
            std::cout << "Player HP decreased by " << decrease << std::endl;
            int enemyhp = en->gethp();
            int controllerhp = controller->gethp();
            if (controllerhp == 0)
            {
                dead = true;
                break;
            }
            if (enemyhp == 0)
            {
                vector<int> enemyPos = en->getpoint();
                theDisplay[pos.at(0)][pos.at(1)] = preTile;
                controller->setpoint(enemyPos);
                theDisplay[enemyPos.at(0)][enemyPos.at(1)] = '@';
                controller->removenotification(en);
                this->removefoe(en);
                break;
            }
        }
    }
    return;
}

void grid::pickPotion(std::vector<int> pos, potion *magic)
{
    theDisplay[pos.at(0)][pos.at(1)] = '@';
    theDisplay[controller->getpoint().at(0)][controller->getpoint().at(1)] = preTile;
    preTile = '.';
    controller->setpoint(pos);
    this->removepotion(magic);
    cout << "potion picked" << endl;
}

potion *grid::getPotion(std::vector<int> position)
{
    std::vector<potion *>::iterator it;
    for (it = potionlist.begin(); it != potionlist.end();)
    {
        bool t = (*it)->potionlocation(position);
        if (t)
        {
            return *it;
        }
        else
        {
            ++it;
        }
    }
    return nullptr;
}

bool grid::isValid(string direction)
{
    if (checkPoint(direction, 'G'))
    {
        for (int i = 0; i < dragons.size(); i++)
        {
            vector<int> pos = cc3k::movement(direction, controller->getpoint());
            if (dragons[i]->withinradius(pos))
            {
                cout << "Gold is guarded by Dragon. Dragon must be slain first" << endl;
                return false;
            }
        }
    }
    return (checkPoint(direction, '.') || checkPoint(direction, '+') || checkPoint(direction, '#') || checkPoint(direction, 'G'));
    // only include pickable gold
}

bool grid::shouldUpdateFloor(std::string direction)
{

    bool isNextTile = checkPoint(direction, '/');
    if (isNextTile)
    {
        int floorNum = controller->getfloor();
        controller->mutatefloor(floorNum + 1);
    }
    return isNextTile;
}

bool grid::checkPoint(string direction, char c)
{
    if (!cc3k::isCorrectDirection(direction))
        return false;
    vector<int> pos = cc3k::movement(direction, controller->getpoint());
    if (c == theDisplay[pos.front()][pos.back()])
        return true;
    return false;
}