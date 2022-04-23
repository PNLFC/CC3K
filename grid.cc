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
#include <stdlib.h>
#include <time.h>
#include "chamber.h"
#include "grid.h"
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
        row.reserve(len);
        for(int i = 0; i < len; ++i){
            row.emplace_back(line[i]);
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
    for (int i = 0; i < 20; i++){
        enemy *e = foes[i];
        foelist.push_back(e);
    }
}

void grid::generate_potionlist(){
    for (int i = 0; i < 10; i++){
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
    std::vector<enemy*>::iterator it;
    for (it = foelist.begin(); it != foelist.end();){
        vector <int> na = (*it)->getpoint(); 
        vector <int> ee = e->getpoint();
        if (na.at(0) == ee.at(0) && na.at(1) == ee.at(1)){
            it = foelist.erase(it);
            break;
        }else{
            ++it;
        }
    }    
}

void grid::removepotion(potion* p){
    std::vector<potion*>::iterator it;
    for (it = potionlist.begin(); it != potionlist.end();){
        vector <int> na = (*it)->getpoint(); 
        vector <int> pp = p->getpoint();
        if (na.at(0) == pp.at(0) && na.at(1) == pp.at(1)){
            it = potionlist.erase(it);
            break;
        }else{
            ++it;
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


void grid::generateboard()
{
    this->generatechambers();
    this->generatepotions();
    this->generatetreasures();
    this->generateenemies();
    this->generate_foelist();
    this->generate_potionlist();
    this->generate_treaslist();
    //attack notifications from nearby enemies
}

void grid::nextboard()
{
    cout << "generate next board" << endl;
    this->cleanboard();
    cout << "cleaned board" << endl;
    this->generatechambers();
    cout << "generate chambers complete" << endl;
    this->generatepotions();
    cout << "generate potions complete" << endl;
    this->generatetreasures();
    cout << "generate treasure complete" << endl;
    this->generateenemies();
    cout << "generate enemies complete" << endl;
    this->generate_foelist();
    cout << "generate foelist complete" << endl;
    this->generate_potionlist();
    cout << "generate potionlist complete" << endl;
    this->generate_treaslist();
    cout << "generate treasurelist complete" << endl;
    // attack notifications from nearby enemies
    for (int y = 0; y < 20; y++)
    {
        enemy *foe = foelist.at(y);
        cout << foe->getidentity() << "identity";
        if (foe != NULL && controller->withinradius(foe)){
            controller->attacknotification(foe);
            cout << "attack notification from " << foe->getidentity() << " to kill player" << endl;
        }
    }
}

void grid::generatechambers()
{
    for (int i = 0; i < 5; i++)
    {
        chambers[i] = new chamber(i, theDisplay);
    }
}


std::vector<int> grid::createplayerposition()
{
    int num = rand() % 5;
    std::vector<int> cor = chambers[num]->addtochamber('@');
    return cor;
}

void grid::setController(player *p)
{
    controller = p;
    int a = rand() % 5;
    std::vector<int> point = controller->getpoint();
    while (chambers[a]->withinRange(point.at(0), point.at(1)))
    {
        a = rand() % 5;
    }
    chambers[a]->addtochamber('/');
    for (int y = 0; y < 20; y++)
    {
        enemy *foe = foelist.at(y);
        if (foe != NULL && controller->withinradius(foe)){
            controller->attacknotification(foe);
            cout << "attack notification from " << foe->getidentity() << " to kill player" << endl;
        }
    }
}


void grid::generateenemies()
{
    for (int i = 0; i < 20; i++)
    {
        int c = rand() % 5;
        int race = rand() % 18;
        if(race >= 0 && race < 4)
        {
            std::vector<int> random = chambers[c]->addtochamber('W');
            foes[i] = new werewolf(random);
        }else if (race >= 4 && race < 7){
            std::vector<int> random = chambers[c]->addtochamber('V');
            foes[i] = new vampire(random);
        }else if (race >= 7 && race < 12){
            std::vector<int> random = chambers[c]->addtochamber('N');
            foes[i] = new goblin(random);
        }else if (race >= 12 && race < 14){
            std::vector<int> random = chambers[c]->addtochamber('T');
            foes[i] = new troll(random);
        }else if (race >= 14 && race < 16){
            std::vector<int> random = chambers[c]->addtochamber('X');
            foes[i] = new phoenix(random);
        }else{
            std::vector<int> random = chambers[c]->addtochamber('M');
            foes[i] = new merchant(random);
        }
        //print the enemies in their points on the board
    }
}

void grid::generatepotions()
{
    for (int i = 0; i < 10; i++)
    {
        int c = rand() % 5;
        int race = rand() % 6;
        std::vector<int> random = chambers[c]->addtochamber('P');
        if (race == 0)
        {
            potionstore[i] = new RH(random);
        }else if (race == 1)
        {
            potionstore[i] = new BA(random);
        }else if (race == 2)
        {
            potionstore[i] = new BD(random);
        }else if (race == 3)
        {
            potionstore[i] = new PH(random);
        }else if(race == 4)
        {
            potionstore[i] = new WA(random);
        }else
        {
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
        if (race >= 0 && race < 5)
        {
            std::vector<int> random = chambers[c]->addtochamber('G');
            goldchest[i] = new NH(random);
        }else if (race == 5){
            std::vector<int> random = chambers[c]->addtochamber('G');
            goldchest[i] = new SH(random);
        }else
        {
            std::vector<int> dragonLocation;
            std::vector<int> random;
            dragonLocation.reserve(2);
            while(dragonLocation.empty()){
                random = chambers[c]->generatePos();
                for (int i = 0; i < 9; ++i){
                    if (i == 4) continue;
                    div_t divresult = div (i,3); 
                    int x = divresult.quot - 1 + random.at(0);
                    int y = divresult.rem - 1 + random.at(1);
                    if (theDisplay[x][y] == '.'){
                        dragonLocation.emplace_back(x);
                        dragonLocation.emplace_back(y);
                        break;
                    }
                }
            }
            theDisplay[random.at(0)][random.at(1)] = 'G';
            cout << random.at(0) << random.at(1) << " dragon horde" << endl;
            theDisplay[dragonLocation.at(0)][dragonLocation.at(1)] = 'D';
            cout << dragonLocation.at(0) << dragonLocation.at(1) << " dragon" << endl;
            goldchest[i] = new DH(random);
            dragon* d = new dragon(dragonLocation);
            dragons.push_back(d);
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
    
    std::vector<enemy*>::iterator it1;
    for(it1 = foelist.begin(); it1 != foelist.end();){
        if (!controller->withinradius(*it1)){
            controller->removenotification(*it1);
        }
        ++it1;
    }
}

void grid::moveenemy(enemy *e)
{
    int a;
    std::vector<int> r = e->getpoint();
    int x = r.at(0);
    int y = r.at(1);
    for(int i = 0; i < 5; ++i)
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
                if  (e->withinradius(controller)){
                    controller->attacknotification(e);
                    cout << "attack notification from " << e->getidentity() << "to kill player" << endl;
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
                if  (e->withinradius(controller)){
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
    std::vector<enemy*>::iterator it;
    std::vector<dragon*>::iterator dt;
    for (it = foelist.begin(); it != foelist.end();)
    {
        this->moveenemy(*it);
        ++it;
    }
    for(dt = dragons.begin(); dt != dragons.end();){
        if  ((*dt)->withinradius(controller)){
            controller->attacknotification(*dt);
            cout << "attack notification from " << (*dt)->getidentity() << "to kill player" << endl;
        }
        ++dt;
    }
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
    while (!controller->attackers.empty()){
        cout << "Enter direction" <<endl;
        cin >> dir;
        vector <int> pos = controller->getpoint();
        if (dir == "no"){
             pos[0] -= 1;     
        } 
        else if (dir == "we"){
             pos[1] -= 1;     
        } 
        else if (dir == "ea"){
            pos[1] += 1;  
        } 
        else if (dir == "so"){
            pos[0] += 1;    
        } 
        else if (dir == "nw"){
            pos[0] -= 1;
            pos[1] -= 1;     
        } 
        else if (dir == "ne"){
            pos[0] -= 1;
            pos[1] += 1;     
        } 
        else if (dir == "sw"){
            pos[0] += 1;
            pos[1] -= 1;     
        } 
        else if (dir == "se"){
            pos[0] += 1;
            pos[1] += 1;     
        }
        else{
            continue;
        } 
        enemy *en = NULL;
        std::vector<enemy*>::iterator it;
        for (it = controller->attackers.begin(); it != controller->attackers.end();){
            vector <int> apos = (*it)->getpoint();
            if (apos.at(0) == pos.at(0) && apos.at(1) == pos.at(1)){
                en = *it;
                break;
            }else{
                ++it;
            }
        }
        if (en != NULL){
            controller->attack(en);
            en->attack(controller);
            int enemyhp = en->gethp();
            int controllerhp = controller->gethp();
            if(controllerhp == 0){
                dead = true;
                break;    
            }   
            if(enemyhp == 0){
                vector <int> enemypos = en->getpoint();
                vector <int> pos = controller->getpoint();
                theDisplay[pos.at(0)][pos.at(1)] = preTile;
                controller->setpoint(enemypos);
                theDisplay[enemypos.at(0)][enemypos.at(1)] = '@';
                controller->removenotification(en);
                this->removefoe(en);
                break;
            }
        }
    }
    return;
}

void grid::potionpick(string dir){
    vector<int> cpoint = controller->getpoint();
    vector<int> point = cpoint;
    std::vector<potion*>::iterator it;
    if (dir == "no"){
        cpoint[0] -= 1;
    }
    else if (dir == "we"){
        cpoint[1] -= 1;
    } 
    else if (dir == "ea"){
        cpoint[1] += 1; 
    } 
    else if (dir == "so"){
        cpoint[0] += 1;    
    } 
    else if (dir == "nw"){
        cpoint[0] -= 1;
        cpoint[1] -= 1;
    } 
    else if (dir == "ne"){
        cpoint[0] -= 1;
        cpoint[1] += 1;
    } 
    else if (dir == "sw"){
        cpoint[0] += 1;
        cpoint[1] -= 1;
    } 
    else if (dir == "se"){
        cpoint[0] += 1;
        cpoint[1] += 1;
    }
    else{
        cout << "Enter correct direction" <<endl;
    }
    for (it = potionlist.begin(); it != potionlist.end();){
        bool t = (*it)->potionlocation(cpoint);
        if (t) {
            theDisplay[cpoint.at(0)][cpoint.at(1)] = '@';
            controller->setpoint(cpoint);
            theDisplay[point.at(0)][point.at(1)] =  preTile;
            this->removepotion(*it);
            cout << "potion picked" <<endl;
            break;
        } else{
            ++it;
        }
    }
}

bool grid::isValid(string direction){
    return(checkPoint(direction,'.')||checkPoint(direction, '+')
           ||checkPoint(direction, '#')||checkPoint(direction, 'G'));
    // only include pickable gold
}

bool grid::isNextFloor(std::string direction){
    bool isNextTile = checkPoint(direction,'/');
    if (isNextTile){
        int floorNum = controller->getfloor();
        controller->mutatefloor(floorNum+1);
    }
    return isNextTile;
}

bool grid::checkPoint(string direction, char c) {
    vector<int> pos = nextStep(direction);
  if (c == theDisplay[pos.front()][pos.back()]) return true;
  return false;
}

void grid::goldpick(string dir){

}