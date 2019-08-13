//
//  item.h
//  ChamberCrawler3000
//
//  Created by Charles Nwodo on 2015-03-30.
//  Copyright (c) 2015 Reel. All rights reserved.
//

#ifndef __ChamberCrawler3000__item__
#define __ChamberCrawler3000__item__

#include <stdio.h>
#include <string>
#include <iostream>
#include "thing.h"
class player;

class item : public thing{
private:
    int mutator;
    bool ispermanent;
public:
    item(std::vector<int> p, char sym,char t, std::string i, int mut, bool pe);
    ~item();
    int getmutator();
    bool permanent();
};

#endif /* defined(__ChamberCrawler3000__item__) */
