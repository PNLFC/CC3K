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

class grid{
private:
    string file;
    player *controller;
    
    
public:
    std::vector<std::vector<char> > theDisplay;
    enemy **foes;
    potion **potionstore;
    treasure **goldchest;
    std::vector<DH *> dragons;
    char preTile; //the tile the Player stand on last time
    
    bool dead;

    std::vector <enemy*> foelist;
    std::vector <potion*> potionlist;
    std::vector <treasure*> treaslist;

    chamber **chambers;

    void removefoe(enemy* e);
    void removepotion(potion* p);
    void removetreas(treasure* t);

    void generate_foelist();
    void generate_potionlist();
    void generate_treaslist();

    grid(string file);
    ~grid();
    bool isValid(std::string direction);
    bool checkPoint(std::string direction, char c);
    void print();
    bool won();
    char selectplayer();
    void startagain();
    void changepointinboard(std::vector<int> p, char c);
    void generateboard(char race, string file); //need to still generate dragons
    void cleanboard(); //implement moving to the next floor
    void createplayer(char race);
    player *generateplayer(char race, std::vector<int> r);
    void generatechambers();
    void generatestair();
    void generateenemies();
    void generatepotions();
    void generatetreasures();
    void moveenemy(enemy *e);
    void moveenemies();//
    void moveplayer(string a);
    void turnmerchant();
    void attackbyplayer();
    void potionpick(string dir);
    void goldpick(string dir);
    std::vector<int> nextStep(std::string direction);

};

#endif /* defined(__ChamberCrawler3000__floor__) */
