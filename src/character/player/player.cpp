//
//  player.cpp
//  ChamberCrawler3000
//
//  Created by Charles Nwodo on 2015-03-29.
//  Copyright (c) 2015 Reel. All rights reserved.
//

#include "player.h"
#include "../../item/treasure/treasure.h"
#include "../../item/potion/potion.h"
#include "../enemy/enemy.h"
#include <list>

player::player(std::vector<int> p, char sym, char t, std::string i, int hp, int atk, int def, int max, int goldn, int floor) : character(p, sym, t, i, hp, atk, def, max), gold(goldn), floor(floor)
{
    std::vector<enemy *> attackers;
}

player::~player() {}

int player::getfloor()
{
    return floor;
}

void player::mutatefloor(int flr)
{
    floor = flr;
}

void player::mutategold(int gld)
{
    gold += gld;
}

int player::getgold()
{
    return gold;
}

void player::attacknotification(enemy *e)
{
    attackers.push_back(e);
}

void player::removenotification(enemy *e)
{
    std::vector<enemy *>::iterator it;
    for (it = attackers.begin(); it != attackers.end();)
    {
        std::vector<int> na = (*it)->getpoint();
        std::vector<int> ee = e->getpoint();
        if (na.at(0) == ee.at(0) && na.at(1) == ee.at(1))
        {
            it = attackers.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

void player::eraseAllNotifications()
{
    std::vector<enemy *>::iterator it;
    for (it = attackers.begin(); it != attackers.end();)
    {
        it = attackers.erase(it);
    }
}
