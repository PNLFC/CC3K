//
//  orc.cpp
//  ChamberCrawler3000
//
//  Created by Charles Nwodo on 2015-03-29.
//  Copyright (c) 2015 Reel. All rights reserved.
//

#include "orc.h"

orc::orc(std::vector<int> p):player(p,'@','c', "orc",180,30,25,180,0,0){}

void orc::mutategold(int gld){
    gold += gld / 2;
}