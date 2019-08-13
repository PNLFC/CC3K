//
//  orc.h
//  ChamberCrawler3000
//
//  Created by Charles Nwodo on 2015-03-29.
//  Copyright (c) 2015 Reel. All rights reserved.
//

#ifndef __ChamberCrawler3000__orc__
#define __ChamberCrawler3000__orc__

#include <stdio.h>
#include "player.h"

class orc : public player{
public:
    orc(std::vector<int> p);
    void mutategold(int gld);
};


#endif /* defined(__ChamberCrawler3000__orc__) */
