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
#include <list>


player::player(std::vector<int> p, char sym, char t, std::string i,int hp, int atk, int def,int max,int goldn,int floor):character(p,sym,t,i,hp,atk,def,max),gold(goldn),floor(floor){
    std::vector<enemy*> attackers;
}

player::~player(){

}

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
    float m = ceilf((100/(float)(100 + e->getdef())) * num);
    int decrease = static_cast<int>(m);
    std::cout << "Enemy HP decreased by " << decrease << std::endl;
    e->mutatehp(-decrease);
}

void player::attacknotification(enemy *e){
    attackers.push_back(e);
}

void player::removenotification(enemy *e){
    std::vector<enemy*>::iterator it;
    for (it = attackers.begin(); it != attackers.end(); ){
        std::vector <int> na = (*it)->getpoint(); 
        std::vector <int> ee = e->getpoint();
        if (na.at(0) == ee.at(0) && na.at(1) == ee.at(1)){
            it = attackers.erase(it);
        }
        else{
            ++it;
        }
    }    
}

void player::movePos(std::string direction){
    std::vector <int> curPos = this->getpoint();
    std::vector <int> newPos;
     if(direction == "no"){
        newPos.push_back(curPos.at(0) - 1);
        newPos.push_back(curPos.at(1));
        this->setpoint(newPos);
    }
    else if(direction == "so"){
        newPos.push_back(curPos.at(0) + 1);
        newPos.push_back(curPos.at(1));
        this->setpoint(newPos);
    }
    else if(direction == "ea"){
        newPos.push_back(curPos.at(0));
        newPos.push_back(curPos.at(1) + 1);
        this->setpoint(newPos);
    }
    else if(direction == "we"){
        newPos.push_back(curPos.at(0));
        newPos.push_back(curPos.at(1) - 1);
        this->setpoint(newPos);
    }
    else if(direction == "ne"){
        newPos.push_back(curPos.at(0) - 1);
        newPos.push_back(curPos.at(1) + 1);
        this->setpoint(newPos);
    }
    else if(direction == "se"){
        newPos.push_back(curPos.at(0) + 1);
        newPos.push_back(curPos.at(1) + 1);
        this->setpoint(newPos);
    }
    else if(direction == "sw"){
        newPos.push_back(curPos.at(0) + 1);
        newPos.push_back(curPos.at(1) - 1);
        this->setpoint(newPos);
    }
    else if(direction == "nw"){
        newPos.push_back(curPos.at(0) - 1);
        newPos.push_back(curPos.at(1) - 1);
        this->setpoint(newPos);   
    }
}


