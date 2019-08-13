//
//  floor.h
//  ChamberCrawler3000
//
//  Created by Charles Nwodo on 2015-03-31.
//  Copyright (c) 2015 Reel. All rights reserved.
//

#ifndef __ChamberCrawler3000__floor__
#define __ChamberCrawler3000__floor__

#include <stdio.h>
#include <string>
#include <vector>
class character;
class player;
class enemy;
class treasure;
class potion;
class chamber;
class DH;

using namespace std;

class floor{
private:
    string file;
    string *board;
    player *controller;
    
    enemy **foes;
    potion **potionstore;
    treasure **goldchest;
    std::vector<DH *> dragons;
    
public:
    chamber **chambers;
    floor(string file);
    ~floor();
    void print();
    bool won();
    char selectplayer();
    void startagain();
    void changepointinboard(std::vector<int> p, char c);
    void generateboard(char race, string file); //need to still generate dragons
    void cleanboard(); //implement moving to the next floor
    void createplayer(char race);
    void generatechambers();
    void generatestair();
    void generateenemies();
    void generatepotions();
    void generatetreasures();
    void moveenemy(enemy *e);
    void moveenemies();//
    void moveplayer(string a);
    void turnmerchant();
};

#endif /* defined(__ChamberCrawler3000__floor__) */
