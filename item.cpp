//
//  item.cpp
//  ChamberCrawler3000
//
//  Created by Charles Nwodo on 2015-03-30.
//  Copyright (c) 2015 Reel. All rights reserved.
//

#include "item.h"
#include "player.h"

item::item(std::vector<int> p, char sym,char t, std::string i,int mut, bool pe):thing(p,sym,t,i){
    mutator = mut;
    ispermanent = pe;
}

item::~item(){}

int item::getmutator(){
    return mutator;
}

bool item::permanent(){
    return ispermanent;
}