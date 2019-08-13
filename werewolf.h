//
//  werewolf.h
//  ChamberCrawler3000
//
//  Created by Charles Nwodo on 2015-03-29.
//  Copyright (c) 2015 Reel. All rights reserved.
//

#ifndef __ChamberCrawler3000__werewolf__
#define __ChamberCrawler3000__werewolf__

#include <stdio.h>
#include "enemy.h"

class werewolf : public enemy{
public:
    werewolf(std::vector<int> p);
};

#endif /* defined(__ChamberCrawler3000__werewolf__) */
