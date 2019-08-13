//
//  thing.h
//  ChamberCrawler3000
//
//  Created by Charles Nwodo on 2015-03-30.
//  Copyright (c) 2015 Reel. All rights reserved.
//

#ifndef __ChamberCrawler3000__thing__
#define __ChamberCrawler3000__thing__

#include <stdio.h>
#include <vector>
#include <string>

class thing{
private:
    std::vector<int> point;
    char symbol;
    char type;
    std::string identity;
    
public:
    thing(std::vector <int> p, char sym, char t, std::string i);
    ~thing();
    void setpoint(std::vector <int> p);
    std::vector<int> getpoint();
    char gettype();
    std::string getidentity();
    char getsymbol();
};


#endif /* defined(__ChamberCrawler3000__thing__) */
