//
//  player.h
//  ChamberCrawler3000
//
//  Created by Charles Nwodo on 2015-03-29.
//  Copyright (c) 2015 Reel. All rights reserved.
//

#ifndef __ChamberCrawler3000__player__
#define __ChamberCrawler3000__player__

#include <stdio.h>
#include <string>
#include "../character.h"
class enemy;
class treasure;
class potion;

class player : public character
{

protected:
    int gold;
    int floor;

public:
    player(std::vector<int> p, char sym, char t, std::string i, int hp, int atk, int def, int max, int goldn, int floor);
    virtual ~player();
    std::vector<enemy *> attackers;
    int getfloor();
    virtual int getgold();
    virtual void mutatefloor(int flr);
    virtual void mutategold(int gld);
    void attacknotification(enemy *e);
    void removenotification(enemy *e);
    void eraseAllNotifications();
};

#endif /* defined(__ChamberCrawler3000__player__) */
