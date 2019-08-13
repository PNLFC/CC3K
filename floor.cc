//
//  floor.cc
//  ChamberCrawler3000
//
//  Created by Charles Nwodo on 2015-04-03.
//  Copyright (c) 2015 Reel. All rights reserved.
//

#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <time.h>
#include "chamber.h"
#include "floor.h"
#include "player.h"
#include "enemy.h"
#include "potion.h"
#include "vampire.h"
#include "werewolf.h"
#include "goblin.h"
#include "troll.h"
#include "phoenix.h"
#include "merchant.h"
#include "dragon.h"
#include "treasure.h"
#include "RH.h"
#include "BA.h"
#include "BD.h"
#include "PH.h"
#include "WA.h"
#include "WD.h"
#include "NH.h"
#include "SH.h"
#include "DH.h"

using namespace std;

floor::floor(string file) : file(file)
{
    controller = NULL;
    chambers = new chamber *[5];
    board = new string[25];
    potionstore = new potion *[10];
    goldchest = new treasure *[10];
    foes = new enemy *[20];
}

floor::~floor()
{
    this->cleanboard();
    delete[] chambers;
    delete[] board;
    delete[] potionstore;
    delete[] goldchest;
    delete[] foes;
    if (controller != NULL)
    {
        delete controller;
    }
}

void floor::cleanboard()
{
    for (int i = 0; i < 5; i++)
    {
        delete chambers[i];
    }
    for (int i = 0; i < 10; i++)
    {
        delete potionstore[i];
    }
    for (int i = 0; i < 20; i++)
    {
        delete foes[i];
    }
    for (int i = 0; i < dragons.size(); i++)
    {
        delete dragons[i];
    }
    while (!dragons.empty())
    {
        dragons.pop_back();
    }
    for (int i = 0; i < 10; i++)
    {
        delete goldchest[i];
    }
}

void floor::print()
{
    for (int i = 0; i < 25; i++)
    {
        printf("%s\n", board[i].c_str());
    }
    cout << "Race: " << controller->getidentity() << " Gold: " << controller->getgold() << endl;
    cout << "HP: " << controller->gethp() << endl;
    cout << "Atk: " << controller->getatk() << endl;
    cout << "Def: " << controller->getdef() << endl;
}

bool floor::won()
{
    if (controller->getfloor() == 5)
    {
        return true;
    }
    return false;
}

void floor::changepointinboard(std::vector<int> p, char c)
{
    int x = p.at(0);
    int y = p.at(1);
    board[y][x] = c;
}

char floor::selectplayer()
{
    char p;
    cout << "Please select a race: " << endl;
    cout << "   human: 'h', orc: 'o', elf: 'e', dwarf " << endl;
    cin >> p;
    while (p != 'h' && p != 'o' && p != 'e' && p != 'd')
    {
        cout << "Bad Selection. Try again" << endl;
        cin >> p;
    }
    return p;
}

void floor::generateboard(char race, std::string file)
{
    ifstream *filestream = new ifstream(file);
    string line;
    int i = 0;
    while (getline(*filestream, line))
    {
        board[i] = line;
        i++;
    }
    cout << "entered generate board" << endl;
    generatechambers();
    this->createplayer(race);
    this->generatestair();
    this->generatepotions();
    this->generatetreasures();
    this->generateenemies();
    delete filestream;
}

void floor::generatechambers()
{
    for (int i = 0; i < 5; i++)
    {
        cout <<"entered generate chamber loop"<<endl;
        chambers[i] = new chamber(i, this);
    }
}

void floor::createplayer(char race)
{
    cout << "create player started" << endl;
    int num = rand() % 5;
    controller = chambers[num]->generateplayer(race);
    changepointinboard(controller->getpoint(), controller->getsymbol());
    std::vector<int> p = controller->getpoint();
    cout << "Player in chamber" << num << "at point" << p.at(0) << p.at(1) << endl;
}

void floor::generatestair()
{
    cout << "I started generating stair" << endl;
    int a = rand() % 5;
    std::vector<int> p = controller->getpoint();
    while (chambers[a]->iswithinchamber(p))
    {
        a = rand() % 5;
    }
    cout << "found index of chamber where player is not" << endl;
    std::vector<int> w = chambers[a]->generatepoint();
    cout << "point generated" << endl;
    chambers[a]->setvalid(w.at(0) - chambers[a]->getfirstx(), w.at(1) - chambers[a]->getfirsty(), false);
    this->changepointinboard(w, '/');
    cout << "stair generated" << endl;
}

void floor::generateenemies()
{
    for (int i = 0; i < 20; i++)
    {
        int c = rand() % 5;
        int race = rand() % 18;
        std::vector<int> random = chambers[c]->generatepoint();
        switch (race)
        {
        case 0:
        case 1:
        case 2:
        case 3:
            foes[i] = new werewolf(random);
            break;
        case 4:
        case 5:
        case 6:
            foes[i] = new vampire(random);
            break;
        case 7:
        case 8:
        case 9:
        case 10:
        case 11:
            foes[i] = new goblin(random);
            break;
        case 12:
        case 13:
            foes[i] = new troll(random);
            break;
        case 14:
        case 15:
            foes[i] = new phoenix(random);
            break;
        case 16:
        case 17:
            foes[i] = new merchant(random);
            break;
        }
        //print the enemies in their points on the board
        chambers[c]->setvalid(random.at(0) - chambers[c]->getfirstx(), random.at(1) - chambers[c]->getfirsty(), false);
        changepointinboard(random, foes[i]->getsymbol());
    }
}

void floor::generatepotions()
{
    cout << "potions have started generating" << endl;
    for (int i = 0; i < 10; i++)
    {
        cout << i << "potions made" << endl;
        int c = rand() % 5;
        int race = rand() % 6;
        std::vector<int> random = chambers[c]->generatepoint();
        switch (race)
        {
        case 0:
            cout << "RH generated" << endl;
            potionstore[i] = new RH(random);
            break;
        case 1:
            cout << "BA generated" << endl;
            potionstore[i] = new BA(random);
            break;
        case 2:
            cout << "BD generated" << endl;
            potionstore[i] = new BD(random);
            break;
        case 3:
            cout << "PH generated" << endl;
            potionstore[i] = new PH(random);
            break;
        case 4:
            cout << "WA generated" << endl;
            potionstore[i] = new WA(random);
            break;
        case 5:
            cout << "WD generated" << endl;
            potionstore[i] = new WD(random);
            break;
        }
        //print the enemies in their points on the board
        changepointinboard(random, potionstore[i]->getsymbol());
    }
}

void floor::generatetreasures()
{
    for (int i = 0; i < 10; i++)
    {
        int c = rand() % 5;
        int race = rand() % 8;
        std::vector<int> random = chambers[c]->generatepoint();
        switch (race)
        {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
            goldchest[i] = new NH(random);
            cout << "Normal Horde generated at" << random.at(0) << random.at(1) << endl;
            break;
        case 5:
            goldchest[i] = new SH(random);
            cout << "Small Horde generated at" << random.at(0) << random.at(1) << endl;
            break;
        case 6:
        case 7:
            goldchest[i] = new DH(random);
            cout << "Dragon Horde generated at" << random.at(0) << random.at(1) << endl;
            break;
        }
        //print the enemies in their points on the board
        changepointinboard(random, goldchest[i]->getsymbol());
    }
}

//void floor::updatefloor(string a){
//    moveplayer(a);
//    moveenemies();
//}

void floor::moveplayer(string a)
{
    std::vector<int> r = controller->getpoint();
    int x = r.at(0);
    int y = r.at(1);
    if (a == "ea")
    {
        std::vector<int> p;
        if (board[y][x + 1] == '.' || board[y][x + 1] == '+' || board[y][x + 1] == '#')
        {
            if(board[y][x+1] == '#'){
                changepointinboard(r,'#');
            }
            if ((board[y][x+1] == '#' && board[y][x-1] == '.')||(board[y][x-1] == '#' && board[y][x+1] == '.')){
                changepointinboard(r,'+');
            }
            else{
                changepointinboard(r, '.');
            }
            p.push_back(x+1);
            p.push_back(y);
            controller->setpoint(p);
            cout << "ea Player is at" << p.at(0) << " " << p.at(1) << endl;
            changepointinboard(p,'@');
        }
        else
        {
            cout << "ran into a wall or an enemy" << endl;
        }
        return;
    }
    if (a == "so")
    {
        std::vector<int> p;
        if (board[y + 1][x] == '.' || board[y + 1][x] == '+' || board[y + 1][x] == '#')
        {
            if(board[y+1][x] == '#'){
                changepointinboard(r,'#');
            }
            if((board[y+1][x] == '#' && board[y-1][x] == '.')||(board[y-1][x] == '#' && board[y+1][x] == '.')){
                changepointinboard(r,'+');
            }
            else{
                std::vector<int> q = r;
                changepointinboard(q, '.');
            }
            p.push_back(x);
            p.push_back(y+1);
            controller->setpoint(p);
            changepointinboard(p, '@');
            cout << "so Player is at" << p.at(0) << " " << p.at(1) << endl;
        }
        else
        {
            cout << "ran into a wall or an enemy" << endl;
        }
        return;
    }
    if (a == "we")
    {
        std::vector<int> p;
        if (board[y][x - 1] == '.' || board[y][x - 1] == '+' || board[y][x - 1] == '#')
        {
            if(board[y][x-1] == '#'){
                changepointinboard(r,'#');
            }
            if((board[y][x-1] == '#' && board[y][x+1] == '.')||(board[y][x+1] == '#' && board[y][x-1] == '.')){
                changepointinboard(r,'+');
            }
            else{
                std::vector<int> q = r;
                changepointinboard(q, '.');
            }
            p.push_back(x-1);
            p.push_back(y);
            controller->setpoint(p);
            changepointinboard(p, '@');
            cout << "move player left" << endl;
        }
        else
        {
            cout << "ran into a wall or an enemy" << endl;
        }
        cout << "Player is at" << p.at(0) << " " << p.at(1) << endl;
        return;
    }
    if (a == "no")
    {
        std::vector<int> p;
        if (board[y - 1][x] == '.' || board[y - 1][x] == '+' || board[y - 1][x] == '#')
        {
            if(board[y-1][x] == '#'){
                changepointinboard(r,'#');
            }
            if((board[y+1][x] == '#' && board[y-1][x] == '.')||(board[y-1][x] == '#' && board[y+1][x] == '.')){
                changepointinboard(r,'+');
            }
            else{
                std::vector<int> q = r;
                changepointinboard(q, '.');
            }
            p.push_back(x);
            p.push_back(y-1);
            controller->setpoint(p);
            changepointinboard(p, '@');
            cout << "move player up" << endl;
        }
        else
        {
            cout << "ran into a wall or an enemy" << endl;
        }
        cout << "Player is at" << p.at(0) << " " << p.at(1) << endl;
        return;
    }
    if (a == "se")
    {
        std::vector<int> p;
        if ((board[y + 1][x + 1] == '.' || board[y + 1][x + 1] == '+' || board[y + 1][x + 1] == '#'))
        {
            p.push_back(x + 1);
            p.push_back(y + 1);
            std::vector<int> q = r;
            controller->setpoint(p);
            changepointinboard(p, board[y][x]);
            changepointinboard(q, '.');
            cout << "move player downward right" << endl;
        }
        else
        {
            cout << "ran into a wall or an enemy" << endl;
        }
        return;
    }
    if (a == "ne")
    {
        std::vector<int> p;
        if (board[y - 1][x + 1] == '.' || board[y - 1][x + 1] == '+' || board[y - 1][x + 1] == '#')
        {
            p.push_back(x + 1);
            p.push_back(y - 1);
            std::vector<int> q = r;
            controller->setpoint(p);
            changepointinboard(p, board[y][x]);
            changepointinboard(q, '.');
            cout << "move player upward right" << endl;
        }
        else
        {
            cout << "ran into a wall or an enemy" << endl;
        }
        return;
    }
    if (a == "nw")
    {
        std::vector<int> p;
        if (board[y - 1][x - 1] == '.' || board[y - 1][x - 1] == '+' || board[y - 1][x - 1] == '#')
        {
            p.push_back(x - 1);
            p.push_back(y - 1);
            std::vector<int> q = r;
            controller->setpoint(p);
            changepointinboard(p, board[y][x]);
            changepointinboard(q, '.');
            cout << "move player upward left" << endl;
        }
        else
        {
            cout << "ran into a wall or an enemy" << endl;
        }
        return;
    }
    if (a == "sw")
    {
        std::vector<int> p;
        if (board[y + 1][x - 1] == '.' || board[y + 1][x - 1] == '+' || board[y + 1][x - 1] == '#')
        {
            p.push_back(x - 1);
            p.push_back(y + 1);
            std::vector<int> q = r;
            controller->setpoint(p);
            changepointinboard(p, board[y][x]);
            changepointinboard(q, '.');
            cout << "move player downward left" << endl;
        }
        else
        {
            cout << "ran into a wall or an enemy" << endl;
        }
        return;
    }
}

void floor::moveenemy(enemy *e)
{
    cout <<"move enemy entered" <<endl;
    int a;
    std::vector<int> r = e->getpoint();
    int x = r.at(0);
    int y = r.at(1);
    while (true)
    {
        a = rand() % 8;
        if (a == 0)
        {
            if (board[y + 1][x] == '.')
            {
                std::vector<int> p;
                p.push_back(x);
                p.push_back(y+1);
                std::vector<int> q = e->getpoint();
                e->setpoint(p);
                changepointinboard(p, board[y][x]);
                changepointinboard(q, '.');
                cout << "move " << e->getidentity() << " to the right" << endl;
                break;
            }
            else if (board[y + 1][x] == '@')
            {
                int random = rand() % 2;
                if (random == 1)
                {
                    e->attack(controller);
                    cout << "move " << e->getidentity() << " to kill player" << endl;
                    break;
                }
                break;
            }
            continue;
        }
        if (a == 1)
        {
            if (board[y][x + 1] == '.')
            {
                std::vector<int> p;
                p.push_back(x+1);
                p.push_back(y);
                std::vector<int> q = e->getpoint();
                e->setpoint(p);
                changepointinboard(p, board[y][x]);
                changepointinboard(q, '.');
                cout << "move " << e->getidentity() << "down" << endl;
                break;
            }
            else if (board[y][x + 1] == '@')
            {
                int random = rand() % 2;
                if (random == 1)
                {
                    e->attack(controller);
                    cout << "move " << e->getidentity() << "to kill player" << endl;
                    break;
                }
            }
            continue;
        }
        if (a == 2)
        {
            if (board[y - 1][x] == '.')
            {
                std::vector<int> p;
                p.push_back(x);
                p.push_back(y-1);
                std::vector<int> q = e->getpoint();
                e->setpoint(p);
                changepointinboard(p, board[y][x]);
                changepointinboard(q, '.');
                cout << "move " << e->getidentity() << "to the left" << endl;
                break;
            }
            else if (board[y - 1][x] == '@')
            {
                int random = rand() % 2;
                if (random == 1)
                {
                    e->attack(controller);
                    cout << "move " << e->getidentity() << "to kill player" << endl;
                    break;
                }
                break;
            }
            continue;
        }
        if (a == 3)
        {
            if (board[y][x - 1] == '.')
            {
                std::vector<int> p;
                p.push_back(x-1);
                p.push_back(y);
                std::vector<int> q = e->getpoint();
                e->setpoint(p);
                changepointinboard(p, board[y][x]);
                changepointinboard(q, '.');
                cout << "move " << e->getidentity() << "up" << endl;
                break;
            }
            else if (board[y][x - 1] == '@')
            {
                int random = rand() % 2;
                if (random == 1)
                {
                    e->attack(controller);
                    cout << "move " << e->getidentity() << "to kill player" << endl;
                    break;
                }
                break;
            }
            continue;
        }
        if (a == 4)
        {
            if (board[y + 1][x + 1] == '.')
            {
                std::vector<int> p;
                p.push_back(x + 1);
                p.push_back(y + 1);
                std::vector<int> q = e->getpoint();
                e->setpoint(p);
                changepointinboard(p, board[y][x]);
                changepointinboard(q, '.');
                cout << "move " << e->getidentity() << "downwards right" << endl;
                break;
            }
            else if (board[y + 1][x + 1] == '@')
            {
                int random = rand() % 2;
                if (random == 1)
                {
                    e->attack(controller);
                    cout << "move " << e->getidentity() << "to kill player" << endl;
                    break;
                }
            }
            continue;
        }
        if (a == 5)
        {
            if (board[y + 1][x - 1] == '.')
            {
                std::vector<int> p;
                p.push_back(x - 1);
                p.push_back(y + 1);
                std::vector<int> q = e->getpoint();
                e->setpoint(p);
                changepointinboard(p, board[y][x]);
                changepointinboard(q, '.');
                cout << "move " << e->getidentity() << "upwards right" << endl;
                break;
            }
            else if (board[y + 1][x - 1] == '@')
            {
                int random = rand() % 2;
                if (random == 1)
                {
                    e->attack(controller);
                    cout << "move " << e->getidentity() << "to kill player" << endl;
                    break;
                }
            }
            continue;
        }
        if (a == 6)
        {
            if (board[y - 1][x - 1] == '.')
            {
                std::vector<int> p;
                p.push_back(x - 1);
                p.push_back(y - 1);
                std::vector<int> q = e->getpoint();
                e->setpoint(p);
                changepointinboard(p, board[y][x]);
                changepointinboard(q, '.');
                cout << "move " << e->getidentity() << "upwards left" << endl;
                break;
            }
            else if (board[y - 1][x - 1] == '@')
            {
                int random = rand() % 2;
                if (random == 1)
                {
                    e->attack(controller);
                    cout << "move " << e->getidentity() << "to kill player" << endl;
                    break;
                }
                break;
            }
            continue;
        }
        if (a == 7)
        {
            if (board[y - 1][x + 1] == '.')
            {
                std::vector<int> p;
                p.push_back(x + 1);
                p.push_back(y - 1);
                std::vector<int> q = e->getpoint();
                e->setpoint(p);
                changepointinboard(p, board[y][x]);
                changepointinboard(q, '.');
                cout << "move " << e->getidentity() << "downwards left" << endl;
                break;
            }
            else if (board[y - 1][x + 1] == '@')
            {
                int random = rand() % 2;
                if (random == 1)
                {
                    e->attack(controller);
                    cout << "move " << e->getidentity() << "to kill player" << endl;
                    break;
                }
                break;
            }
            continue;
        }
    }
}

void floor::moveenemies()
{
    cout << "move enemies entered" << endl;
    for (int y = 0; y < 20; y++)
    {
        this->moveenemy(foes[y]);
    }
    cout << "all enemies moved" << endl;
}

void floor::turnmerchant()
{
    for (int i = 0; i < 20; i++)
    {
        if (foes[i]->getidentity() == "merchant")
        {
            foes[i]->turnonhostility();
        }
    }
}
