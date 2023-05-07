#include "util.h"

std::vector<int> cc3k::movement(std::string direction, std::vector<int> curPos)
{
    std::vector<int> newPos;
    if (direction == "no")
    {
        newPos.push_back(curPos.at(0) - 1);
        newPos.push_back(curPos.at(1));
    }
    else if (direction == "so")
    {
        newPos.push_back(curPos.at(0) + 1);
        newPos.push_back(curPos.at(1));
    }
    else if (direction == "ea")
    {
        newPos.push_back(curPos.at(0));
        newPos.push_back(curPos.at(1) + 1);
    }
    else if (direction == "we")
    {
        newPos.push_back(curPos.at(0));
        newPos.push_back(curPos.at(1) - 1);
    }
    else if (direction == "ne")
    {
        newPos.push_back(curPos.at(0) - 1);
        newPos.push_back(curPos.at(1) + 1);
    }
    else if (direction == "se")
    {
        newPos.push_back(curPos.at(0) + 1);
        newPos.push_back(curPos.at(1) + 1);
    }
    else if (direction == "sw")
    {
        newPos.push_back(curPos.at(0) + 1);
        newPos.push_back(curPos.at(1) - 1);
    }
    else if (direction == "nw")
    {
        newPos.push_back(curPos.at(0) - 1);
        newPos.push_back(curPos.at(1) - 1);
    }
    return newPos;
}

std::vector<int> cc3k::movement(int direction, std::vector<int> curPos)
{
    std::vector<int> newPos;
    switch (direction)
    {
    case 0:
        newPos.push_back(curPos.at(0));
        newPos.push_back(curPos.at(1) + 1);
        break;
    case 1:
        newPos.push_back(curPos.at(0) + 1);
        newPos.push_back(curPos.at(1));
        break;
    case 2:
        newPos.push_back(curPos.at(0));
        newPos.push_back(curPos.at(1) - 1);
        break;
    case 3:
        newPos.push_back(curPos.at(0) - 1);
        newPos.push_back(curPos.at(1));
        break;
    case 4:
        newPos.push_back(curPos.at(0) + 1);
        newPos.push_back(curPos.at(1) + 1);
        break;
    case 5:
        newPos.push_back(curPos.at(0) - 1);
        newPos.push_back(curPos.at(1) + 1);
        break;
    case 6:
        newPos.push_back(curPos.at(0) - 1);
        newPos.push_back(curPos.at(1) - 1);
        break;
    case 7:
        newPos.push_back(curPos.at(0) + 1);
        newPos.push_back(curPos.at(1) - 1);
        break;
    default:
        break;
    }
    return newPos;
}

bool cc3k::isCorrectDirection(std::string dir)
{
    return dir == "no" || dir == "we" || dir == "ea" || dir == "so" || dir == "nw" || dir == "ne" || dir == "sw" || dir == "se";
}