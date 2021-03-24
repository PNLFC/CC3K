//
//  character.cpp
//  ChamberCrawler3000
//
//  Created by Charles Nwodo on 2015-03-29.
//  Copyright (c) 2015 Reel. All rights reserved.
//

#include "character.h"
#include <vector>
#include <string>


character::character(std::vector <int> p, char sym, char t, std::string i, int hp, int atk, int def, int max): thing(p,sym,t,i), hp(hp),atk(atk),def(def),maxhp(max){}
          
character::~character(){
    
}

void character::mutatedef(int d){
    def += d;
    if (def < 0) {
        def = 0;
        return;
    }
}

void character::mutateatk(int a){
    atk += a;
    if(atk < 0){
        atk = 0;
        return;
    }
}

void character::mutatehp(int h){
    hp += h;
    if(hp < 0){
        hp = 0;
        return;
    }
    if (hp > maxhp) {
        hp = maxhp;
        return;
    }
}


int character::getatk(){
    return atk;
}

int character::getdef(){
    return def;
}

int character::gethp(){
    return hp;
}

bool character::slain(){
    return hp == 0;
}

bool character::withinradius(character *p){
    std::vector <int> pcoord = p->getpoint();
    std::vector <int> ecoord = this->getpoint();
    if (abs(pcoord.at(0)-ecoord.at(0)) <= 1  && abs(pcoord.at(1)-ecoord.at(1))<= 1){
        return true;
    }
    else{
        return false;
    }
}    