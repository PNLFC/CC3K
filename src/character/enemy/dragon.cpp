//
//  dragon.cpp
//  ChamberCrawler3000
//
//  Created by Charles Nwodo on 2015-03-29.
//  Copyright (c) 2015 Reel. All rights reserved.
//

#include "dragon.h"
dragon::dragon(std::vector<int> p) : enemy(p, 'D', 'e', "dragon", 150, 20, 20, 150, false, NULL) {}

dragon::~dragon() {}