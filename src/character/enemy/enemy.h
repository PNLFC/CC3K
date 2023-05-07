//
//  enemy.h
//  ChamberCrawler3000
//
//  Created by Charles Nwodo on 2015-03-29.
//  Copyright (c) 2015 Reel. All rights reserved.
//

#ifndef __ChamberCrawler3000__enemy__
#define __ChamberCrawler3000__enemy__
class treasure;
class player;
#include <stdio.h>
#include "../character.h"

class enemy : public character
{
private:
    bool ishostile;
    treasure *t;

public:
    enemy(std::vector<int> p, char sym, char t, std::string i, int hp, int atk, int def, int max, bool ishostile, treasure *gold);
    virtual ~enemy();
    void turnonhostility();
    treasure *gettreasure();
    void settreasure(treasure *gold);
};

#endif /* defined(__ChamberCrawler3000__enemy__) */
