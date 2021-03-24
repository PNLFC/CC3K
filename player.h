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
#include<string>
#include "character.h"
class enemy;
class treasure;
class potion;

class player: public character{
private:
    int mutdef;
    int mutatk;
    int muthp;
    int maxhp;


    
protected:
    int gold;
    int floor;
    
        
public:
    player(std::vector<int> p, char sym, char t, std::string i,int hp, int atk, int def,int max,int goldn,int floor);
    ~player();
    int getfloor();
    std::vector<enemy*> attackers;
    int num_attackers;
    int get_num_attk();
    void num_attk_minus();
    void mutatefloor(int flor);
    int getgold();
    void mutategold(int gld);
    void mutatemutdef(int def);
    void mutatemutatk(int atk);
    void mutatemuthp(int hp);
    void attack(enemy *e);
    void attacknotification(enemy *e);
    void removenotification(enemy *e);
    void movePos(std::string direction);
    };


#endif /* defined(__ChamberCrawler3000__player__) */
