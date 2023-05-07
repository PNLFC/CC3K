//
//  treasure.h
//  ChamberCrawler3000
//
//  Created by Charles Nwodo on 2015-03-30.
//  Copyright (c) 2015 Reel. All rights reserved.
//

#ifndef __ChamberCrawler3000__treasure__
#define __ChamberCrawler3000__treasure__

#include <stdio.h>
#include "../item.h"
#include "../../character/player/player.h"

class treasure : public item
{
public:
    treasure(std::vector<int> p, char sym, int mut, char t, std::string i, bool pe);
    virtual ~treasure();
    void usetreasure(player *p);
};

#endif /* defined(__ChamberCrawler3000__treasure__) */
