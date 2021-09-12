#ifndef PACMAN_MAPGENERATOR_H
#define PACMAN_MAPGENERATOR_H

#include <vector>
#include <stack>
#include <iostream>
#include <random>
#include <algorithm>

using namespace std;

class MapGenerator {
public:
    MapGenerator();

    vector<vector<int>> generateMapDfs();

    ~MapGenerator();

private:
    vector<vector<int>> map;
    vector<vector<bool>> visited;

    static void printMap(const vector<vector<int>> &m);

    pair<int, int> connectToRandomNeighbour(int i, int j, bool deadEnd = false);

    void checkForDeadEnds();

    int getNeighbours(int i, int j);
};


#endif //PACMAN_MAPGENERATOR_H
