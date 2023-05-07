//
//  elf.h
//  ChamberCrawler3000
//
//  Created by Charles Nwodo on 2015-03-29.
//  Copyright (c) 2015 Reel. All rights reserved.
//

#ifndef __ChamberCrawler3000__MagicDecorator__
#define __ChamberCrawler3000__MagicDecorator__

#include <cstdlib>
#include <stdio.h>
#include <string>
#include "player.h"
#include "../../item/potion/potion.h"

class MagicDecorator : public player
{
private:
    player *controller;

public:
    MagicDecorator(player *p, potion *magic);
    virtual ~MagicDecorator();
    int getfloor();
    int getgold();
    int gethp();
    void mutatefloor(int flr);
    void mutategold(int gld);
    void mutatehp(int h);
};

#endif /* defined(__ChamberCrawler3000__elf__) */