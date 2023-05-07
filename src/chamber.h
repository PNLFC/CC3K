//
//  chamber.h
//  ChamberCrawler3000
//
//  Created by Charles Nwodo on 2015-04-03.
//  Copyright (c) 2015 Reel. All rights reserved.
//

#ifndef __ChamberCrawler3000__chamber__
#define __ChamberCrawler3000__chamber__
#include <vector>

class chamber
{
    int id;
    int topRow;
    int topCol;
    int rowLen;
    int colLen;
    std::vector<std::vector<char>> &theDisplay;

public:
    chamber(int id, std::vector<std::vector<char>> &theDisplay);
    ~chamber();

    int getid();
    int gettopRow();
    int gettopCol();
    int getrowLen();
    int getcolLen();

    bool isValidTile(const int row, const int col);
    std::vector<int> generatePos();
    std::vector<int> addtochamber(const char symbol);
    bool withinRange(const int row, const int col);
};

#endif
