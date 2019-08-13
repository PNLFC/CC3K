/* 
  chamber.cpp
  ChamberCrawler3000

  Created by Charles Nwodo on 2015-04-03.
  Copyright (c) 2015 Reel. All rights reserved.
*/

#include <cstdlib>
#include <time.h>
#include <cstdio>
#include <vector>
#include "chamber.h"
#include "floor.h"
#include "human.h"
#include "elf.h"
#include "orc.h"
#include "dwarf.h"
#include "player.h"

chamber::chamber(int i, floor *flood) : i(i), f(flood)
{
    std::vector<int> temp;
    switch (i)
    { //i used to construct different sets of chambers in the floor
    case 0:
        temp.push_back(4);
        temp.push_back(3);
        firstpoint = temp;
        width = 26;
        height = 4;
        break;
    case 1:
        temp.push_back(4);
        temp.push_back(15);
        firstpoint = temp;
        width = 21;
        height = 7;
        break;
    case 2:
        temp.push_back(38);
        temp.push_back(10);
        firstpoint = temp;
        width = 12;
        height = 3;
        break;
    case 3:
        temp.push_back(39);
        temp.push_back(3);
        firstpoint = temp;
        width = 37;
        height = 10;
        break;
    case 4:
        temp.push_back(38);
        temp.push_back(16);
        firstpoint = temp;
        width = 39;
        height = 6;
        break;
    }
    tile = new bool *[height];
    for (int x = 0; x < height; x++)
    {
        tile[x] = new bool[width];
    }

    //make the whole 2d array values be true
    for (int x = 0; x < height; x++)
    {
        for (int y = 0; y < width; y++)
        {
            tile[x][y] = true;
        }
    }

    //reshapen the 2d array so that it takes the shapes of the
    //actual chambers through indicating false values for all non chamber tiles
    //involved
    switch (i)
    {
    case 3:
        for (int y = 22; y < width; y++)
        {
            tile[0][y] = false;
        }

        for (int y = 22; y < width; y++)
        {
            tile[1][y] = false;
        }
        for (int y = 30; y < width; y++)
        {
            tile[2][y] = false;
        }
        for (int y = 33; y < width; y++)
        {
            tile[3][y] = false;
        }
        for (int x = 4; x < 10; x++)
        {
            for (int y = 0; y < 22; y++)
            {
                tile[x][y] = false;
            }
        }
        break;
    case 4:
        for (int x = 0; x < 3; x++)
        {
            for (int y = 0; y < 28; y++)
            {
                tile[x][y] = false;
            }
        }
        break;
    }
}

chamber::~chamber()
{
    for (int i = 0; i < height; i++)
    {
        delete[] tile[i];
    }
    delete[] tile;
}

int chamber::getfirstx()
{
    return firstpoint.at(0);
}

int chamber::getfirsty()
{
    return firstpoint.at(1);
}

std::vector<int> chamber::getfirstpoint()
{
    return firstpoint;
}

int chamber::getwidth()
{
    return width;
}

int chamber::getheight()
{
    return height;
}

bool chamber::validtile(int x, int y)
{
    int x1 = this->getfirstx();
    int y1 = this->getfirsty();
    if (x < x1 || x > x1 + width - 1 || y < y1 || y > y1 + height - 1)
    {
        return false;
    }
    cout << tile[y - y1][x - x1] << endl;
    return tile[y - y1][x - x1];
}

void chamber::setvalid(int x, int y, bool valid)
{
    tile[y][x] = valid;
}

std::vector<int> chamber::generatepoint()
{
    cout << "generation point function entered" << endl;
    int y = rand() % height;
    int x = rand() % width;
    while (this->validtile(x + this->getfirstx(), y + this->getfirsty()) == false)
    {
        y = rand() % height;
        x = rand() % width;
    }
    std::vector<int> newpoint;
    newpoint.push_back(x + this->getfirstx());
    newpoint.push_back(y + this->getfirsty());
    cout << "point generated at" << newpoint.at(0) << newpoint.at(1) << endl;
    setvalid(x, y, false);
    return newpoint;
}

player *chamber::generateplayer(char race)
{
    std::vector<int> r = this->generatepoint();
    switch (race)
    {
    case 'h':
        return new human(r);
    case 'e':
        return new elf(r);
    case 'o':
        return new orc(r);
    case 'd':
        return new dwarf(r);
    default:
        cerr << "Wrong input";
        return NULL;
    }
}

bool chamber::iswithinchamber(std::vector<int> p)
{
    int x = p.at(0);
    int y = p.at(1);
    int x1 = this->getfirstx();
    int y1 = this->getfirsty();
    if (x < x1 || x > x1 + width - 1 || y < y1 || y > y1 + height - 1)
    {
        return false;
    }
    return true;
}

/* int main(int argc, char *argv[])
{
    string file = "cc3kfloor.txt";
    srand(static_cast<unsigned int>(time(NULL)));
    floor *grid = new floor(file);
    string i = argv[0];
    for (int i = 0; i < 5; i++)
    {
        grid->chambers[i] = new chamber(i, grid);
        int height = grid->chambers[i]->getheight();
        int width = grid->chambers[i]->getwidth();
        for (int h = 0; h < height; h++)
        {
            for (int w = 0; w < width; w++)
            {
                if (grid->chambers[i]->validtile(w,h) == true)
                {
                    printf("1");
                }
                else
                {
                    printf("0");
                }
            }
            printf("/n");
        }
    }    
    return 0;
}
*/
