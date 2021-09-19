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

    for (int i = 1; i < map[0].size() - 2; i++) {
        map[1][i] = 0;
        map[map.size() - 2][i] = 0;
    }

    map[23][13] = 0;
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
            pair<int, int> neighbour = connectToRandomNeighbour(curI, curJ);
            curJ = neighbour.first;
            curI = neighbour.second;
            visited[curI][curJ] = true;
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

    for (auto &i: visited) {
        for (auto &&j: i) {
            j = false;
        }
    }
    checkForDeadEnds();

    return map;
}

pair<int, int> MapGenerator::connectToRandomNeighbour(int i, int j, bool deadEnd) {
    vector<pair<int, int>> neighbours;
    if (deadEnd) {
        if (i + 2 < map.size() && map[i + 1][j] != 0 && map[i + 2][j] == 0) neighbours.emplace_back(j, i + 2);
        if (j + 2 < map[i].size() && map[i][j + 1] != 0 && map[i][j + 2] == 0) neighbours.emplace_back(j + 2, i);
        if (i - 2 > -1 && map[i - 1][j] != 0 && map[i - 2][j] == 0) neighbours.emplace_back(j, i - 2);
        if (j - 2 > -1 && map[i][j - 1] != 0 && map[i][j - 2] == 0) neighbours.emplace_back(j - 2, i);
    } else {
        if (i + 2 < map.size() && !visited[i + 2][j]) neighbours.emplace_back(j, i + 2);
        if (j + 2 < map[i].size() && !visited[i][j + 2]) neighbours.emplace_back(j + 2, i);
        if (i - 2 > -1 && !visited[i - 2][j]) neighbours.emplace_back(j, i - 2);
        if (j - 2 > -1 && !visited[i][j - 2]) neighbours.emplace_back(j - 2, i);
    }
    if (!neighbours.empty()) {
        shuffle(neighbours.begin(), neighbours.end(), std::mt19937(std::random_device()()));
        int xDif = neighbours[0].first - j;
        int yDif = neighbours[0].second - i;
        if (xDif != 0) xDif = xDif / abs(xDif);
        if (yDif != 0) yDif = yDif / abs(yDif);
        map[i + yDif][j + xDif] = 0;
        return neighbours[0];
    } else return {-1, -1};
}

void MapGenerator::checkForDeadEnds() {
    for (int i = 0; i < map.size(); i++) {
        for (int j = 0; j < map[i].size(); j++) {
            if (map[i][j] == 0 && getNeighbours(i, j) < 2) {
                connectToRandomNeighbour(i, j, true);
            }
        }
    }
}

int MapGenerator::getNeighbours(int i, int j) {
    vector<pair<int, int>> neighbours;
    if (i + 1 < map.size() && map[i + 1][j] == 0) neighbours.emplace_back(j, i + 1);
    if (j + 1 < map[i].size() && map[i][j + 1] == 0) neighbours.emplace_back(j + 1, i);
    if (i - 1 > -1 && map[i - 1][j] == 0) neighbours.emplace_back(j, i - 1);
    if (j - 1 > -1 && map[i][j - 1] == 0) neighbours.emplace_back(j - 1, i);
    return neighbours.size();
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
