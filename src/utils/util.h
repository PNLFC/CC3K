#include <vector>
#include <string>

#ifndef __ChamberCrawler3000__cc3k__
#define __ChamberCrawler3000__cc3k__

namespace cc3k
{
    std::vector<int> movement(std::string direction, std::vector<int> curPos);
    std::vector<int> movement(int direction, std::vector<int> curPos);
    bool isCorrectDirection(std::string dir);
}
#endif
