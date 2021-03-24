//
//  potion.h
//  ChamberCrawler3000
//
//  Created by Charles Nwodo on 2015-03-30.
//  Copyright (c) 2015 Reel. All rights reserved.
//

#ifndef __ChamberCrawler3000__potion__
#define __ChamberCrawler3000__potion__

#include <stdio.h>
#include "item.h"
#include "enemy.h"
#include "player.h"

class potion : public item {
public:
    potion(std::vector<int> p, char sym, int mut, char t, std::string i, bool pe);
    ~potion();
    void usepotion(player *p);
    bool potionlocation(std::vector<int> loc);
};


#endif /* defined(__ChamberCrawler3000__potion__) */
