//
//  character.h
//  ChamberCrawler3000
//
//  Created by Charles Nwodo on 2015-03-29.
//  Copyright (c) 2015 Reel. All rights reserved.
//

#ifndef __ChamberCrawler3000__character__
#define __ChamberCrawler3000__character__

#include <stdio.h>
#include "../thing.h"

class character : public thing
{
private:
    int hp;
    int atk;
    int def;
    int maxhp;

public:
    character(std::vector<int> p, char sym, char t, std::string i, int hp, int atk, int def, int maxhp);
    ~character();
    int getatk();
    int getdef();
    virtual int gethp();
    int getMaxHp();
    void mutateatk(int a);
    void mutatedef(int d);
    virtual void mutatehp(int h);
    bool slain();
    bool withinradius(std::vector<int> p);
    virtual int attack(character *c);
};
#endif /* defined(__ChamberCrawler3000__character__) */
