//
//  merchant.h
//  ChamberCrawler3000
//
//  Created by Charles Nwodo on 2015-03-29.
//  Copyright (c) 2015 Reel. All rights reserved.
//

#ifndef __ChamberCrawler3000__merchant__
#define __ChamberCrawler3000__merchant__

#include <stdio.h>
#include "enemy.h"

class merchant : public enemy{
public:
    merchant(std::vector<int> p);
};


#endif /* defined(__ChamberCrawler3000__merchant__) */
