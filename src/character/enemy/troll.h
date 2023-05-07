//
//  troll.h
//  ChamberCrawler3000
//
//  Created by Charles Nwodo on 2015-03-29.
//  Copyright (c) 2015 Reel. All rights reserved.
//

#ifndef __ChamberCrawler3000__troll__
#define __ChamberCrawler3000__troll__

#include <stdio.h>
#include "enemy.h"

class troll : public enemy{
public:
    troll(std::vector<int> p);
};


#endif /* defined(__ChamberCrawler3000__troll__) */
