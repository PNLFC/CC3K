//
//  potion.cpp
//  ChamberCrawler3000
//
//  Created by Charles Nwodo on 2015-03-30.
//  Copyright (c) 2015 Reel. All rights reserved.
//

#include "potion.h"

potion::potion(std::vector<int> p, char sym, int mut, char t, std::string i, bool pe): item(p, sym, t, i,mut, pe){}

potion::~potion(){
    
}

int abs(int a){
    if (a < 0) {
        return -a;
    }
    return a;
}

void potion::usepotion(player *p){
    int a = this->getmutator();
    if (p->getidentity() == "elf"){
        a = abs(a);
    }
    if (this->gettype() == 'h'){
        if (this->permanent() == false){
            p->mutatemuthp(-a);
            return;
        }
        p->mutatehp(a);
    }
    if (this->gettype() == 'a'){
        if ((p->getidentity() == "elf") && a < 0){
            p->mutateatk(-a);
            return;
        }
        p->mutatehp(a);
    }
    if (this->gettype() == 'd'){
        if ((p->getidentity() == "elf") && a < 0){
            p->mutatedef(-a);
            return;
        }
        p->mutatehp(a);
    }
}
