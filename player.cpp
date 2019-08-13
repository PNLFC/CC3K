//
//  player.cpp
//  ChamberCrawler3000
//
//  Created by Charles Nwodo on 2015-03-29.
//  Copyright (c) 2015 Reel. All rights reserved.
//


#include "player.h"
#include "treasure.h"
#include "potion.h"
#include "enemy.h"
#include <cmath>

player::player(std::vector<int> p, char sym, char t, std::string i,int hp, int atk, int def,int max,int goldn,int floor):character(p,sym,t,i,hp,atk,def,max),gold(goldn),floor(floor){}

player::~player(){}


int player::getfloor(){
    return floor;
}

void player::mutatefloor(int flor){
    floor = flor;
}

void player::mutategold(int gld){
    gold += gld;
}

int player::getgold(){
    return gold;
}

void player::mutatemutdef(int def){
    mutdef += def;
    if (mutdef < 0) {
        mutdef = 0;
        return;
    }
    }

void player::mutatemutatk(int atk){
    mutatk += atk;
    if(mutatk < 0){
    mutatk = 0;
        return;
    }
}

void player::mutatemuthp(int hp){
    muthp += hp;
    if(muthp < 0){
        muthp = 0;
        return;
    }
    if (muthp > maxhp) {
        muthp = maxhp;
        return;
    }
}

void player::attack(enemy *e){
    float num = this->getatk();
    int m = ceilf(100/(100 + e->getdef()) * num);
    e->mutatehp(-m);
}
