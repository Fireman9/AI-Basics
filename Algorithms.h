#ifndef PACMAN_ALGORITHMS_H
#define PACMAN_ALGORITHMS_H

#include <vector>
#include <stack>
#include <queue>
#include <cstdlib>

using namespace std;

class Algorithms {
public:
    Algorithms();

    vector<pair<int, int>> dfs(int startX, int startY, int destX, int destY, vector<vector<int>> &map);

    vector<pair<int, int>> bfs(int startX, int startY, int destX, int destY, vector<vector<int>> &map);

    vector<pair<int, int>> ucs(int startX, int startY, int destX, int destY, vector<vector<int>> &map);

    vector<pair<int, int>>
    aStar(int startX, int startY, int destX, int destY, vector<vector<int>> &map, bool ghost, bool pathDrawing,
          int direction = 0);



    ~Algorithms();
};


#endif //PACMAN_ALGORITHMS_H
