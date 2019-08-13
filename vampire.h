//
//  vampire.h
//  ChamberCrawler3000
//
//  Created by Charles Nwodo on 2015-03-29.
//  Copyright (c) 2015 Reel. All rights reserved.
//

#ifndef __ChamberCrawler3000__vampire__
#define __ChamberCrawler3000__vampire__

#include <stdio.h>
#include "enemy.h"

class vampire : public enemy{
public:
    vampire(std::vector<int> p);
};


#endif /* defined(__ChamberCrawler3000__vampire__) */
