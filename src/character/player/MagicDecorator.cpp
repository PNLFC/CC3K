//
//  MagicDecorator.cpp
//  ChamberCrawler3000
//
//  Created by Charles Nwodo on 2015-03-29.
//  Copyright (c) 2015 Reel. All rights reserved.
//

#include "MagicDecorator.h"
#include "player.h"
#include "../../item/potion/potion.h"

MagicDecorator::MagicDecorator(player *p, potion *magic)
    : player(p->getpoint(), p->getsymbol(),
             p->gettype(),
             p->getidentity(),
             p->gethp(),
             p->getatk(),
             p->getdef(),
             p->getMaxHp(),
             p->getgold(),
             p->getfloor())
{
    std::string id = magic->getidentity();
    if (id == "BA" || id == "WA")
    {
        this->mutateatk(magic->getmutator());
    }
    else if (id == "BD" || id == "WD")
    {
        this->mutatedef(magic->getmutator());
    }
    for (int i = 0; i < p->attackers.size(); i++)
    {
        this->attacknotification(p->attackers[i]);
    }
    MagicDecorator *decorator = dynamic_cast<MagicDecorator *>(p);
    if (!!decorator)
    {
        controller = decorator->controller;
        delete decorator;
    }
    else
    {
        controller = p;
    }
}

MagicDecorator::~MagicDecorator() {}

void MagicDecorator::mutategold(int gld)
{
    controller->mutategold(gld);
    std::cout << controller->getgold() << std::endl;
}

void MagicDecorator::mutatefloor(int flr)
{
    controller->mutatefloor(flr);
}

void MagicDecorator::mutatehp(int h)
{
    controller->mutatehp(h);
}

int MagicDecorator::getfloor()
{
    return controller->getfloor();
}

int MagicDecorator::getgold()
{
    return controller->getgold();
}

int MagicDecorator::gethp()
{
    return controller->gethp();
}