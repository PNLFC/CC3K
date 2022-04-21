//
//  thing.cpp
//  ChamberCrawler3000
//
//  Created by Charles Nwodo on 2015-03-30.
//  Copyright (c) 2015 Reel. All rights reserved.
//

#include "thing.h"


thing::thing(std::vector<int> p, char sym, char t, std::string i){
    point = p;
    symbol = sym;
    type = t;
    identity = i;
}

thing::~thing(){}

void thing::setpoint(std::vector <int> p){
    point = p;
}

std::vector<int> thing::getpoint(){
    return point;
}

char thing::getsymbol(){
    return symbol;
}

char thing::gettype(){
    return type;
}

std::string thing::getidentity(){
    return identity;
}
