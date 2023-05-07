//
//  treasure.cpp
//  ChamberCrawler3000
//
//  Created by Charles Nwodo on 2015-03-30.
//  Copyright (c) 2015 Reel. All rights reserved.
//

#include "treasure.h"


treasure::treasure(std::vector<int> p, char sym,int mut,char t, std::string i, bool pe):item(p,sym, t, i,mut, pe){}

treasure::~treasure(){}

void treasure::usetreasure(player *p){
    int a = this->getmutator();
    p->mutategold(a);
}