/* 
  chamber.cpp
  ChamberCrawler3000

  Created by Charles Nwodo on 2015-04-03.
  Copyright (c) 2015 Reel. All rights reserved.
*/

#include <cstdlib>
#include <time.h>
#include <cstdio>
#include "chamber.h"
#include <iostream>
#include <memory>
#include <utility>

using namespace std;

chamber::chamber(int id, std::vector<std::vector<char> >& theDisplay): id(id), theDisplay(theDisplay) 
{
    //std::move is used for unique_ptr Floor here
    if (id == 0) { //top left
         topRow = 3;
         topCol = 3;
         rowLen = 4;
         colLen = 26;
    }
    if (id == 1) { //top right(special case)
        topRow = 3;
        topCol = 39;
        rowLen = 10;
        colLen = 37;
    }
    if (id == 2) { //middle
        topRow = 10;
        topCol = 38;
        rowLen = 3;
        colLen = 12;
    }
    if (id == 3) { //bottom left
        topRow = 15;
        topCol = 4;
        rowLen = 7;
        colLen = 21;
    }
    if (id == 4) { //bottom right(special case)
        topRow = 16;
        topCol = 37;
        rowLen = 6;
        colLen = 39;
    }
}

chamber::~chamber() {}

int chamber::getid() {
    return id;
}

int chamber::gettopRow() {
    return topRow;
}

int chamber::gettopCol(){
    return topCol;
}

int chamber::getrowLen() {
    return rowLen;
}

int chamber::getcolLen(){
    return colLen;
}

bool chamber::isValidTile(int row,int col) {
    if (theDisplay[row][col] == '.' ) return true;
    else return false;    
}

vector<int> chamber::generatePos() {
    vector<int> cor;
    int currRow, currCol;
    while (true) {
      currRow = rand() % rowLen;
      currCol = rand() % colLen;
        if (isValidTile(topRow+currRow, topCol+currCol)) break;
    }
    cor.push_back(topRow+currRow);
    cor.push_back(topCol+currCol);
    return cor;
}

vector<int> chamber::addtochamber(const char symbol) {
    vector<int> cor;
    int currRow, currCol;
    while (true) {
      currRow = rand() % rowLen;
      currCol = rand() % colLen;
      if (isValidTile(topRow+currRow, topCol+currCol)) break;
    }
    theDisplay[topRow+currRow][topCol+currCol] = symbol;
    cor.push_back(topRow+currRow);
    cor.push_back(topCol+currCol);
    return cor;
}

bool chamber::withinRange(const int row, const int col) {
    if (id != 1 && id != 4) {
        if ((row >= topRow && row <= topRow+rowLen) && (col >= topCol && row <= topCol+colLen)) return true;
        else return false;
    } else if (id == 1) {
        if (col <= topCol+1) {
            if (row < topRow+23) return true;
            else return false;
        } else if (col == topCol+2) {
            if (row < topRow+30) return true;
            else return false;
        } else if (col == topCol+3) {
            if (row < topRow+34) return true;
            else return false;
        }else{
            if (col <= topCol+10 && (row > topRow+23 && row < 37)) return true;
            else return false;
        }
    } else {
        if (col <= topCol+2) {
            if (row > topRow+28 && row < topRow+40) return true;
            else return false;
        } else  {
            if (col <= topCol+5 &&(row >= topRow && row < topRow+40)) return true;
            else return false;
        }
    }
}

