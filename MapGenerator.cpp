#include "MapGenerator.h"

MapGenerator::MapGenerator() {
    map.resize(31);
    for (auto &i: map) {
        i.resize(28, 1);
    }
    visited.resize(31);
    for (auto &i: visited) {
        i.resize(28, true);
    }

    for (int i = 0; i < map.size(); i++) {
        for (int j = 0; j < map[i].size(); j++) {
            if (i % 2 != 0 && j % 2 != 0) map[i][j] = 0;
        }
    }
    for (int i = 0; i < visited.size(); i++) {
        for (int j = 0; j < visited[i].size(); j++) {
            if (i % 2 != 0 && j % 2 != 0) visited[i][j] = false;
        }
    }

    for (auto &i: map) {
        i[i.size() - 1] = 1;
    }
    for (auto &i: visited) {
        i[i.size() - 1] = true;
    }

    // tunnel
    map[15][0] = 0;
    map[15][map[0].size() - 1] = 0;
    visited[15][visited[0].size() - 1] = false;

    // ghost spawn
    for (int i = 11; i < 18; i++) {
        for (int j = 9; j < 18; j++) {
            map[i][j] = 0;
        }
    }
    for (int i = 12; i < 17; i++) {
        for (int j = 10; j < 17; j++) {
            map[i][j] = 1;
            visited[i][j] = true;
        }
    }
    for (int i = 13; i < 16; i++) {
        for (int j = 11; j < 16; j++) {
            map[i][j] = 2;
        }
    }
    map[12][12] = 3;
    map[12][13] = 3;
    map[12][14] = 3;
}

vector<vector<int>> MapGenerator::generateMapDfs() {
    int curI = 1;
    int curJ = 1;
    visited[curI][curJ] = true;
    bool allVisited = false;
    stack<pair<int, int>> stack;
    while (!allVisited) {
        if ((curI + 2 < map.size() && !visited[curI + 2][curJ]) ||
            (curJ + 2 < map[curI].size() && !visited[curI][curJ + 2]) || (curI - 2 > -1 && !visited[curI - 2][curJ]) ||
            (curJ - 2 > -1 && !visited[curI][curJ - 2])) {
            stack.push(pair<int, int>(curI, curJ));
            vector<pair<int, int>> neighbours;
            // stack.empty debug
            if (curI + 2 < map.size() && !visited[curI + 2][curJ]) neighbours.emplace_back(curJ, curI + 2);
            if (curJ + 2 < map[curI].size() && !visited[curI][curJ + 2]) neighbours.emplace_back(curJ + 2, curI);
            if (curI - 2 > -1 && !visited[curI - 2][curJ]) neighbours.emplace_back(curJ, curI - 2);
            if (curJ - 2 > -1 && !visited[curI][curJ - 2]) neighbours.emplace_back(curJ - 2, curI);
            if (!neighbours.empty()) {
                shuffle(neighbours.begin(), neighbours.end(), std::mt19937(std::random_device()()));
                int xDif = neighbours[0].first - curJ;
                int yDif = neighbours[0].second - curI;
                if (xDif != 0) xDif = xDif / abs(xDif);
                if (yDif != 0) yDif = yDif / abs(yDif);
                map[curI + yDif][curJ + xDif] = 0;
                curJ = neighbours[0].first;
                curI = neighbours[0].second;
                visited[curI][curJ] = true;
                neighbours.clear();
            }
        } else {
            if (!stack.empty()) {
                curJ = stack.top().second;
                curI = stack.top().first;
                stack.pop();
            }
        }
        allVisited = true;
        for (auto &i: visited) {
            for (auto &&j: i) {
                if (!j) {
                    allVisited = false;
                }
            }
        }
    }
    return map;
}

void MapGenerator::printMap(const vector<vector<int>> &m) {
    for (auto &i: m) {
        for (int j: i) {
            if (j == 0) cout << "-" << " ";
            else cout << j << " ";
        }
        cout << endl;
    }
    cout << endl;
}

MapGenerator::~MapGenerator() = default;
