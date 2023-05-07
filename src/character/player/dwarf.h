//
//  dwarf.h
//  ChamberCrawler3000
//
//  Created by Charles Nwodo on 2015-03-29.
//  Copyright (c) 2015 Reel. All rights reserved.
//

#ifndef __ChamberCrawler3000__dwarf__
#define __ChamberCrawler3000__dwarf__

#include <stdio.h>
#include "player.h"

class dwarf : public player{
public:
    dwarf(std::vector<int> p);
    void mutategold(int gold);
};


#endif /* defined(__ChamberCrawler3000__dwarf__) */
