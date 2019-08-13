//
//  dwarf.cpp
//  ChamberCrawler3000
//
//  Created by Charles Nwodo on 2015-03-29.
//  Copyright (c) 2015 Reel. All rights reserved.
//

#include "dwarf.h"
dwarf::dwarf(std::vector<int> p):player(p,'@','c',"dwarf", 100,20,30,100,0,0){}

void dwarf::mutategold(int gold){
    gold += 2 * gold;
}