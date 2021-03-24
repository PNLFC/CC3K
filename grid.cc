//
//  grid.cc
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
#include "grid.h"
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
#include "human.h"
#include "elf.h"
#include "orc.h"
#include "dwarf.h"
#include "player.h"
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

grid::grid(string file) : file(file)
{
    controller = NULL;
    chambers = new chamber *[5];
    potionstore = new potion *[10];
    goldchest = new treasure *[10];
    foes = new enemy *[20];
    dead = false;
    ifstream filestream (file);
    string line;
    while (getline(filestream, line))
    {
        vector <char> row;
        int len = (int)line.length();
        for(int i = 0; i < len; ++i){
            row.push_back(line[i]);
        }
        theDisplay.push_back(row);
    }
    preTile = '.';
}

grid::~grid()
{
    this->cleanboard();
    delete[] chambers;
    delete[] potionstore;
    delete[] goldchest;
    delete[] foes;
    if (controller != NULL)
    {
        delete controller;
    }
}

void grid::cleanboard()
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


void grid::generate_foelist(){
    for (int i = 0; i < 20;i++){
        enemy *e = foes[i];
        foelist.push_back(e);
    }
}

void grid::generate_potionlist(){
    for (int i = 0; i < 10;i++){
        potion *p = potionstore[i];
        potionlist.push_back(p);
    }
}

void grid::generate_treaslist(){
    for (int i = 0; i < 10;i++){
        treasure *t = goldchest[i];
        treaslist.push_back(t);
    }
}

void grid::removefoe(enemy* e){
    for (int i = 0; i < 20;i++){
        vector <int> na = foelist.at(i)->getpoint(); 
        vector <int> ee = e->getpoint();
        if (na.at(0) == ee.at(0) && na.at(1) == ee.at(1)){
            foelist.at(i) = NULL;
            break;
        }
    }    
}

void grid::removepotion(potion* p){
    for (int i = 0; i < 10;i++){
        vector <int> na = potionlist.at(i)->getpoint(); 
        vector <int> pp = p->getpoint();
        if (na.at(0) == pp.at(0) && na.at(1) == pp.at(1)){
            potionlist.at(i) = NULL;
            break;
        }
    }    
}

void grid::removetreas(treasure* t){
    for (int i = 0; i < 10; i++){
        vector <int> na = treaslist.at(i)->getpoint(); 
        vector <int> tt = t->getpoint();
        if (na.at(0) == tt.at(0) && na.at(1) == tt.at(1)){
            treaslist.at(i) = NULL;
            break;
        }
    }    
}



void grid::print()
{
    for (int i = 0; i < 25; i++)
    {
        string line(theDisplay[i].begin(), theDisplay[i].end());
        printf("%s\n", line.c_str());
    }
    cout << "Race: " << controller->getidentity() << " Gold: " << controller->getgold() << endl;
    cout << "HP: " << controller->gethp() << endl;
    cout << "Atk: " << controller->getatk() << endl;
    cout << "Def: " << controller->getdef() << endl;
}

bool grid::won()
{
    if (controller->getfloor() == 5)
    {
        return true;
    }
    return false;
}

char grid::selectplayer()
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

void grid::generateboard(char race, std::string file)
{
    cout << "entered generate board" << endl;
    cout << theDisplay[0][0] << endl;
    this->generatechambers();
    this->createplayer(race);
    this->generatestair();
    this->generatepotions();
    this->generatetreasures();
    this->generateenemies();
    this->generate_foelist();
    this->generate_potionlist();
    this->generate_treaslist();
}

void grid::generatechambers()
{
    for (int i = 0; i < 5; i++)
    {
        cout <<"entered generate chamber loop"<<endl;
        chambers[i] = new chamber(i, theDisplay);
    }
}

player *grid::generateplayer(char race, std::vector<int> r)
{
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

void grid::createplayer(char race)
{
    cout << "create player started" << endl;
    int num = rand() % 5;
    std::vector<int> cor = chambers[num]->generatePos('@');
    controller = generateplayer(race, cor);
    std::vector<int> p = controller->getpoint();
    cout << "Player in chamber" << num << "at point" << p.at(0) << p.at(1) << endl;
}

void grid::generatestair()
{
    cout << "I started generating stair" << endl;
    int a = rand() % 5;
    std::vector<int> p = controller->getpoint();
    while (chambers[a]->withinRange(p.at(0), p.at(1)))
    {
        a = rand() % 5;
    }
    cout << "found index of chamber where player is not" << endl;
    std::vector<int> w = chambers[a]->generatePos('/');
    cout << "point generated" << endl;
    cout << "stair generated" << w.at(0) << w.at(1) << endl;
}

void grid::generateenemies()
{
    for (int i = 0; i < 20; i++)
    {
        int c = rand() % 5;
        int race = rand() % 18;
        if(race >= 0 && race < 4)
        {
            std::vector<int> random = chambers[c]->generatePos('W');
            foes[i] = new werewolf(random);
        }else if (race >= 4 && race < 7){
            std::vector<int> random = chambers[c]->generatePos('V');
            foes[i] = new vampire(random);
        }else if (race >= 7 && race < 12){
            std::vector<int> random = chambers[c]->generatePos('G');
            foes[i] = new goblin(random);
        }else if (race >= 12 && race < 14){
            std::vector<int> random = chambers[c]->generatePos('T');
            foes[i] = new troll(random);
        }else if (race >= 14 && race < 16){
            std::vector<int> random = chambers[c]->generatePos('P');
            foes[i] = new phoenix(random);
        }else{
            std::vector<int> random = chambers[c]->generatePos('M');
            foes[i] = new merchant(random);
        }
        //print the enemies in their points on the board
    }
    cout << "generated all enemies" <<endl;
}

void grid::generatepotions()
{
    cout << "potions have started generating" << endl;
    for (int i = 0; i < 10; i++)
    {
        cout << i << "potions made" << endl;
        int c = rand() % 5;
        int race = rand() % 6;
        std::vector<int> random = chambers[c]->generatePos('P');
        if (race == 0)
        {
            cout << "RH generated" << endl;
            potionstore[i] = new RH(random);
        }else if (race == 1)
        {
            cout << "BA generated" << endl;
            potionstore[i] = new BA(random);
        }else if (race == 2)
        {
            cout << "BD generated" << endl;
            potionstore[i] = new BD(random);
        }else if (race == 3)
        {
            cout << "PH generated" << endl;
            potionstore[i] = new PH(random);
        }else if(race == 4)
        {
             cout << "WA generated" << endl;
            potionstore[i] = new WA(random);
        }else
        {
            cout << "WD generated" << endl;
            potionstore[i] = new WD(random);
        }
        //print the enemies in their points on the board
    }
}

void grid::generatetreasures()
{
    for (int i = 0; i < 10; i++)
    {
        int c = rand() % 5;
        int race = rand() % 8;
        std::vector<int> random = chambers[c]->generatePos('G');
        if (race >= 0 && race < 5)
        {
            goldchest[i] = new NH(random);
            cout << "Normal Horde generated at" << random.at(0) << random.at(1) << endl;
        }else if (race == 5){
            goldchest[i] = new SH(random);
            cout << "Small Horde generated at" << random.at(0) << random.at(1) << endl;
        }else
        {
            goldchest[i] = new DH(random);
            cout << "Dragon Horde generated at" << random.at(0) << random.at(1) << endl;
        }
        //print the enemies in their points on the board
    }
}

vector<int> grid::nextStep(string direction) { //I AM A HELPER
    std::vector<int> r = controller->getpoint();
    int prow = r.at(0);
    int pcol = r.at(1);
    vector<int> pos;
    if (direction == "no") {
        --prow;
    } else if (direction == "so") {
        ++prow;
    } else if (direction == "ea") {
        ++pcol;
    } else if (direction == "we") {
        --pcol;
    } else if (direction == "ne") {
        --prow;
        ++pcol;
    } else if (direction == "se") {
        ++prow;
        ++pcol;
    } else if (direction == "sw") {
        ++prow;
        --pcol;
    } else{
        --prow;
        --pcol;    
    }
    pos.push_back(prow);
    pos.push_back(pcol);
    return pos;
}

void grid::moveplayer(string a)
{
    std::vector<int> r = controller->getpoint();
    int prow = r.at(0); //current row of player
    int pcol = r.at(1); //current col of player
    vector<int> prePos = nextStep(a);
    char temp = theDisplay[prePos.front()][prePos.back()]; // next char
    if (temp == 'G') {  // next step is Gold
      int ind;
      for (ind = 0; ind < (int)treaslist.size(); ++ind) {
          std::vector<int> point = treaslist[ind]->getpoint();
	      if (point.at(0) == prePos.front() && point.at(1) == prePos.back()){
		      break;
	      }
      }
      if(!treaslist[ind]->permanent()){  // the gold is not dragon hoard or it's a dragon hoard(dragon is dead now)
	      treaslist[ind]->usetreasure(controller);
	      treaslist.erase(treaslist.begin()+ind);
	      temp = '.';
      }
      else{
	      cout<<"The gold is guarded by the Dragon. You can't pick it." << endl; 
      }
    }
    theDisplay[prow][pcol] = preTile;
    controller->movePos(a);
    std::vector <int> newPos = controller->getpoint(); 
    theDisplay[newPos.at(0)][newPos.at(1)] = '@';
    preTile = temp;
    
    int n = controller->get_num_attk();
    for(int i = 0; i < n; i++){
        enemy *enu = controller->attackers[i];
        if (!controller->withinradius(enu)){
            controller->removenotification(enu);
        }
    }
}

void grid::moveenemy(enemy *e)
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
            if (theDisplay[x][y+1] == '.')
            {
                std::vector<int> p;
                p.push_back(x);
                p.push_back(y+1);
                std::vector<int> q = e->getpoint();
                e->setpoint(p);
                theDisplay[x][y+1] = theDisplay[x][y];
                theDisplay[q.at(0)][q.at(1)] =  '.';
                cout << "move " << e->getidentity() << " to the right" << endl;
                if (e->withinradius(controller)){
                    controller->attacknotification(e);
                    cout << "attack notification from " << e->getidentity() << " to kill player" << endl;
                }   
                break;           
            }
             continue;
        }
        if (a == 1)
        {
            if (theDisplay[x+1][y] == '.')
            {
                std::vector<int> p;
                p.push_back(x+1);
                p.push_back(y);
                std::vector<int> q = e->getpoint();
                e->setpoint(p);
                theDisplay[x+1][y] = theDisplay[x][y];
                theDisplay[q.at(0)][q.at(1)] =  '.';
                cout << "move " << e->getidentity() << " down" << endl;
                if (e->withinradius(controller)){
                    controller->attacknotification(e);
                    cout << "attack notification from " << e->getidentity() << "to kill player" << endl;
                }
                break;
            }
            continue;
        }
        if (a == 2)
        {
            if (theDisplay[x][y-1] == '.')
            {
                std::vector<int> p;
                p.push_back(x);
                p.push_back(y-1);
                std::vector<int> q = e->getpoint();
                e->setpoint(p);
                theDisplay[x][y-1] = theDisplay[x][y];
                theDisplay[q.at(0)][q.at(1)] =  '.';
                cout << "move " << e->getidentity() << "to the left" << endl;
                if  (e->withinradius(controller)){
                    controller->attacknotification(e);
                    cout << "attack notification from " << e->getidentity() << "to kill player" << endl;
                }
                break;
            }    
            continue;
        }
        if (a == 3)
        {
            if (theDisplay[x-1][y] == '.')
            {
                std::vector<int> p;
                p.push_back(x-1);
                p.push_back(y);
                std::vector<int> q = e->getpoint();
                e->setpoint(p);
                theDisplay[x-1][y] = theDisplay[x][y];
                theDisplay[q.at(0)][q.at(1)] =  '.';
                cout << "move " << e->getidentity() << "up" << endl;
                if  (e->withinradius(controller)){
                    controller->attacknotification(e);
                    cout << "attack notification from " << e->getidentity() << "to kill player" << endl;
                }
                break;
            }
            continue;
        }
        if (a == 4)
        {
            if (theDisplay[x + 1][y + 1] == '.')
            {
                std::vector<int> p;
                p.push_back(x + 1);
                p.push_back(y + 1);
                std::vector<int> q = e->getpoint();
                e->setpoint(p);
                theDisplay[x+1][y+1] = theDisplay[x][y];
                theDisplay[q.at(0)][q.at(1)] =  '.';
                cout << "move " << e->getidentity() << "downwards right" << endl;
                if  (e->withinradius(controller)){
                    controller->attacknotification(e);
                    cout << "attack notification from " << e->getidentity() << "to kill player" << endl;    
                }
                break;
            } 
            continue;
        }
        if (a == 5)
        {
            if (theDisplay[x - 1][y + 1] == '.')
            {
                std::vector<int> p;
                p.push_back(x - 1);
                p.push_back(y + 1);
                std::vector<int> q = e->getpoint();
                e->setpoint(p);
                theDisplay[x-1][y+1] = theDisplay[x][y];
                theDisplay[q.at(0)][q.at(1)] =  '.';
                cout << "move " << e->getidentity() << "upwards right" << endl;
                if  (e->withinradius(controller)){
                    controller->attacknotification(e);
                    cout << "attack notification from " << e->getidentity() << "to kill player" << endl;
                }
                break;
            }
            continue;
        }
        if (a == 6)
        {
            if (theDisplay[x - 1][y - 1] == '.')
            {
                std::vector<int> p;
                p.push_back(x - 1);
                p.push_back(y - 1);
                std::vector<int> q = e->getpoint();
                e->setpoint(p);
                theDisplay[x-1][y-1] = theDisplay[x][y];
                theDisplay[q.at(0)][q.at(1)] =  '.';
                cout << "move " << e->getidentity() << "upwards left" << endl;
                if  (e->withinradius(controller)){
                    controller->attacknotification(e);
                    cout << "attack notification from " << e->getidentity() << "to kill player" << endl;
                }
                break;
            }
            continue;
        }
        if (a == 7)
        {
            if (theDisplay[x + 1][y - 1] == '.')
            {
                std::vector<int> p;
                p.push_back(x + 1);
                p.push_back(y - 1);
                std::vector<int> q = e->getpoint();
                e->setpoint(p);
                theDisplay[x+1][y-1] = theDisplay[x][y];
                theDisplay[q.at(0)][q.at(1)] =  '.';
                cout << "move " << e->getidentity() << "downwards left" << endl;
                if  (e->withinradius(controller)){
                    controller->attacknotification(e);
                    cout << "attack notification from " << e->getidentity() << "to kill player" << endl;
                }
                break;
            }          
            continue;
        }
    }
}

void grid::moveenemies()
{
    cout << "move enemies entered" << endl;
    for (int y = 0; y < 20; y++)
    {
        if (foelist.at(y) != NULL){
            this->moveenemy(foelist.at(y));
        }
    }
    cout << "all enemies moved" << endl;
}

void grid::turnmerchant()
{
    for (int i = 0; i < 20; i++)
    {
        if (foes[i]->getidentity() == "merchant")
        {
            foes[i]->turnonhostility();
        }
    }
}

void quitfloor() {
    cout << endl <<
    "You suck at this game \n\
    Go get better and come back next time." << endl;
}

void grid::attackbyplayer(){
    string dir;
    int numattk = controller->get_num_attk();
    while (numattk > 0){
        cout << "Enter direction" <<endl;
        cin >> dir;
        vector <int> pos = controller->getpoint();
        if (dir == "no"){
             pos.at(1) -= 1;     
        } 
        else if (dir == "we"){
             pos.at(0) -= 1;     
        } 
        else if (dir == "ea"){
            pos.at(0) += 1;     
        } 
        else if (dir == "so"){
            pos.at(1) += 1;    
        } 
        else if (dir == "nw"){
            pos.at(0) -= 1;
            pos.at(1) -= 1;     
        } 
        else if (dir == "ne"){
            pos.at(0) += 1;
            pos.at(1) -= 1;     
        } 
        else if (dir == "sw"){
            pos.at(0) -= 1;
            pos.at(1) += 1;     
        } 
        else if (dir == "se"){
            pos.at(0) += 1;
            pos.at(1) += 1;     
        }
        else{
            continue;
        } 

        for (int i = 0; i < controller->num_attackers; i++){
            enemy *en = controller->attackers[i];
            vector <int> apos = en->getpoint();
            if (apos.at(0) == pos.at(0) && apos.at(1) == pos.at(1)){
                controller->attack(en);
                en->attack(controller);
                int enemyhp = en->gethp();
                int controllerhp = controller->gethp();
                if(controllerhp == 0){
                    numattk = 0;
                    dead = true;
                    break;    
                }   
                if(enemyhp == 0){
                     theDisplay[apos.at(0)][apos.at(1)] = '.';
                    controller->num_attk_minus();
                    this->removefoe(en);
                    numattk = controller->get_num_attk();
                    break;
                }
            }
        }
            
    }
    return;
}

void grid::potionpick(string dir){
    vector<int> cpoint = controller->getpoint();
    vector<int> point = cpoint;
    for (int i = 0; i<10; i++){
        if (dir == "no"){
            cpoint.at(1) -= 1;
            bool t = potionstore[i]->potionlocation(cpoint);
            if (t){
                theDisplay[cpoint.at(0)][cpoint.at(1)] = '@';
                controller->setpoint(cpoint);
                theDisplay[point.at(0)][point.at(1)] =  '.';
                this->removepotion(potionstore[i]);
                break;
            }
        }
        else if (dir == "we"){
            cpoint.at(0) -= 1;   
            bool t = potionstore[i]->potionlocation(cpoint);
            if (t){
                theDisplay[cpoint.at(0)][cpoint.at(1)] = '@';
                controller->setpoint(cpoint);
                theDisplay[point.at(0)][point.at(1)] =  '.';
                this->removepotion(potionstore[i]);
                break;
            }  
        } 
        else if (dir == "ea"){
            cpoint.at(0) += 1;  
            bool t = potionstore[i]->potionlocation(cpoint);
            if (t){
                theDisplay[cpoint.at(0)][cpoint.at(1)] = '@';
                controller->setpoint(cpoint);
                theDisplay[point.at(0)][point.at(1)] =  '.';
                this->removepotion(potionstore[i]);
                break;
            }   
        } 
        else if (dir == "so"){
            cpoint.at(1) += 1;    
            bool t = potionstore[i]->potionlocation(cpoint);
            if (t){
                theDisplay[cpoint.at(0)][cpoint.at(1)] = '@';
                controller->setpoint(cpoint);
                theDisplay[point.at(0)][point.at(1)] =  '.';
                this->removepotion(potionstore[i]);
                break;
            }
        } 
        else if (dir == "nw"){
            cpoint.at(0) -= 1;
            cpoint.at(1) -= 1;
            bool t = potionstore[i]->potionlocation(cpoint);
            if (t){
                theDisplay[cpoint.at(0)][cpoint.at(1)] = '@';
                controller->setpoint(cpoint);
                theDisplay[point.at(0)][point.at(1)] =  '.';
                this->removepotion(potionstore[i]);
                break;
            }
        } 
        else if (dir == "ne"){
            cpoint.at(0) += 1;
            cpoint.at(1) -= 1;
            bool t = potionstore[i]->potionlocation(cpoint);
            if (t){
                theDisplay[cpoint.at(0)][cpoint.at(1)] = '@';
                controller->setpoint(cpoint);
                theDisplay[point.at(0)][point.at(1)] =  '.';
                this->removepotion(potionstore[i]);
                break;
            }
        } 
        else if (dir == "sw"){
            cpoint.at(0) -= 1;
            cpoint.at(1) += 1;
            bool t = potionstore[i]->potionlocation(cpoint);
            if (t){
                theDisplay[cpoint.at(0)][cpoint.at(1)] = '@';
                controller->setpoint(cpoint);
                theDisplay[point.at(0)][point.at(1)] =  '.';
                this->removepotion(potionstore[i]);
                break;
            }
        } 
        else if (dir == "se"){
            cpoint.at(0) += 1;
            cpoint.at(1) += 1;
            bool t = potionstore[i]->potionlocation(cpoint);
            if (t){
                theDisplay[cpoint.at(0)][cpoint.at(1)] = '@';
                controller->setpoint(cpoint);
                theDisplay[point.at(0)][point.at(1)] =  '.';
                this->removepotion(potionstore[i]);
                break;
            }
        }
        else{
            cout << "Enter correct direction" <<endl;
            break;
        }
    }
    cout << "potion picked" <<endl;
}

bool grid::isValid(string direction){
    return(checkPoint(direction,'.')||checkPoint(direction, '+')
           ||checkPoint(direction, '#')); // only include pickable gold
}

bool grid::checkPoint(string direction, char c) {
    vector<int> pos = nextStep(direction);
  if (c == theDisplay[pos.front()][pos.back()]) return true;
  return false;
}



void grid::goldpick(string dir){

}