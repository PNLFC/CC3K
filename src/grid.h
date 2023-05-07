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
class dragon;

using namespace std;

class grid
{
private:
    string file;

public:
    player *controller;
    std::vector<std::vector<char>> theDisplay;
    enemy **foes;
    potion **potionstore;
    treasure **goldchest;

    char preTile; // the tile the Player stood on the last time

    bool dead;

    std::vector<enemy *> foelist;
    std::vector<potion *> potionlist;
    std::vector<treasure *> treaslist;
    std::vector<dragon *> dragons;

    chamber **chambers;

    void removefoe(enemy *e);
    void removepotion(potion *p);
    void removetreas(treasure *t);

    void generate_foelist();
    void generate_potionlist();
    void generate_treaslist();

    grid(string file);
    ~grid();
    bool isValid(std::string direction);
    bool isPlayerDead();
    bool shouldUpdateFloor(std::string direction);
    bool checkPoint(std::string direction, char c);
    void setController(player *p);
    void addControllerToGrid(player *p);
    void print();
    bool won();
    void startagain();
    void changepointinboard(std::vector<int> p, char c);
    void generateboard(); // need to still generate dragons
    void cleanboard();
    void generatedragonposition(std::vector<int> p);
    std::vector<int> createplayerposition();
    void generatechambers();
    void generateenemies();
    void generatepotions();
    void generatetreasures();
    void moveenemy(enemy *e);
    void moveenemies();
    void moveplayer(string a);
    void attackbyplayer();
    void pickPotion(std::vector<int> pos, potion *magic);
    potion *getPotion(std::vector<int> position);
    void turnmerchant();
};

#endif /* defined(__ChamberCrawler3000__floor__) */
