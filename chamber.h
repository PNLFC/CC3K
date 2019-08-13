//
//  chamber.h
//  ChamberCrawler3000
//
//  Created by Charles Nwodo on 2015-04-03.
//  Copyright (c) 2015 Reel. All rights reserved.
//

#ifndef __ChamberCrawler3000__chamber__
#define __ChamberCrawler3000__chamber__

#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>

class floor;
class player;

class chamber {
    int i;
    std::vector <int> firstpoint;
    int width, height;
    bool **tile;
    floor *f;
    
    void assignValids();
public:
    chamber(int i, floor *flood);
    ~chamber();
    bool validtile(int x, int y);
    bool iswithinchamber(std::vector <int> p);
    void setvalid(int x, int y, bool valid);
    int getfirstx();
    int getfirsty();
    std::vector <int> getfirstpoint();
    int getwidth();
    int getheight();
    std::vector <int> generatepoint();
    player *generateplayer(char race);
   
};

#endif /* defined(__ChamberCrawler3000__chamber__) */