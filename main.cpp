//
//  main.cpp
//  ChamberCrawler3000
//
//  Created by Charles Nwodo on 2015-03-29.
//  Copyright (c) 2015 Reel. All rights reserved.
//


#include "grid.h"
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
        file = "map.txt";
    }
    srand(static_cast<unsigned int> (time(NULL)));  //  using the time seed from srand
    passage();
    grid *floor = new grid(file);
    char race = floor->selectplayer();
    floor->generateboard(race,file);
    floor->print();
    
    string d;
    cin >> d;
    while(!cin.eof()) {
        if (d == "q") {
            quit();
            break;
        }
        if(d[0] == 'a' ){
            d.erase(0, 1);
            floor->attackbyplayer();
        }
        if(d[0] == 'u'){
            d.erase(0, 1);
            cout << "Enter direction" << endl;
            cin >> d;
            floor->potionpick(d);
        }
        //player moving through floor    
        while (!(d == "no" || d == "so" || d == "ea" || d == "we"
                 || d == "ne" || d == "se" || d == "nw" || d == "sw" || d == "r")) {
            cin.clear();
            cout << "Enter a valid command: ";
            cin >> d;
            if(d[0] == 'a' ) {
                d.erase(0, 1);
                cout << "Enter direction" << endl;
                floor->attackbyplayer();
                d.erase(0,2);
            }
            else if (d[0] == 'u'){
                d.erase(0, 1);
                cout << "Enter direction" << endl;
                cin >> d;
                floor->potionpick(d);
                d.erase(0,2);
            }
        }
        if (floor->isValid(d)){
            floor->moveplayer(d);
            cout << "player moved" << endl;
            floor->moveenemies();
        }
        
        if(floor->won()) {
            win();
            break;
        }
        floor->print();
        cin >> d;
    }
    
    delete floor;
    return 0;
}