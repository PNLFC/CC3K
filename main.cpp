//
//  main.cpp
//  ChamberCrawler3000
//
//  Created by Charles Nwodo on 2015-03-29.
//  Copyright (c) 2015 Reel. All rights reserved.
//


#include "floor.h"
#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

void passage() {
    cout << endl <<
    "CHAMBER CRAWLER 3000\n\
    Designed and produced by Charles Nwodo.\n\
    The commands are as follows:\n\
    Movement: (no,so,ea,we,nw,ne,sw,se)\n\
    Attack: a + direction\n\
    Potion: u + direction\n\
    To Attack and collect item you must be within 1 block\n\
    Restart: r, Quit: q" << endl << endl;
}

void win() {
    cout <<
    "CONGRATULATIONS!\n"
    << endl;
}

void quit() {
    cout << endl <<
    "You suck at this game \n\
    Go get better and come back next time." << endl;
}

int main(int argc, char *argv[]) {
    string file;
    if (argc == 2) {
        file = argv[1];
        srand(time(NULL));
    }
    else{
        file = "cc3kfloor.txt";
    }
    srand(static_cast<unsigned int> (time(NULL)));  //  using the time seed from srand
    passage();
    floor *grid = new floor(file);
    char race = grid->selectplayer();
    grid->generateboard(race,file);
    grid->print();
    
    string comm;
    cin >> comm;
    while(!cin.eof()) {
        if (comm == "q") {
            quit();
            break;
        }
        string d = comm;
        if(d[0] == 'a' || d[0] == 'u') {
            d.erase(0, 1);
        }
        while (!(d == "no" || d == "so" || d == "ea" || d == "we"
                 || d == "ne" || d == "se" || d == "nw" || d == "sw" || d == "r")) {
            cin.clear();
            cout << "Enter a valid command: ";
            cin >> comm;
            d = comm;
            if(d[0] == 'a' || d[0] == 'u') {
                d.erase(0, 1);
            }
        }
        grid->moveplayer(d);
        cout << "player moved" << endl;
        grid->moveenemies();
        
        if(grid->won()) {
            win();
            break;
        }
        grid->print();
        cin >> comm;
    }
    
    delete grid;
    return 0;
}