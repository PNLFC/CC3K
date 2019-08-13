//
//  dragon.h
//  ChamberCrawler3000
//
//  Created by Charles Nwodo on 2015-03-29.
//  Copyright (c) 2015 Reel. All rights reserved.
//

#ifndef __ChamberCrawler3000__dragon__
#define __ChamberCrawler3000__dragon__

#include <stdio.h>
#include "enemy.h"

class dragon : public enemy{
public:
    dragon(std::vector<int> p);
};


#endif /* defined(__ChamberCrawler3000__dragon__) */
