#include "Algorithms.h"

Algorithms::Algorithms() = default;

vector<pair<int, int>> Algorithms::dfs(int startX, int startY, int destX, int destY, vector<vector<int>> &map) {
    vector<pair<int, int>> path;
    vector<vector<bool>> visited(map.size(), vector<bool>(map[0].size(), false));
    for (int i = 0; i < visited.size(); i++) {
        for (int j = 0; j < visited[i].size(); j++) {
            if (map[i][j] == 1) visited[i][j] = true;
        }
    }
    int x = startX;
    int y = startY;
    visited[y][x] = true;
    path.emplace_back(pair<int, int>(x, y));

    bool allVisited = false;
    bool destFound = false;
    stack<pair<int, int>> stack;
    while (!allVisited && !destFound) {
        if ((y + 1 < map.size() && !visited[y + 1][x]) ||
            (y - 1 > -1 && !visited[y - 1][x]) ||
            (x + 1 < map[y].size() && !visited[y][x + 1]) ||
            (x - 1 > -1 && !visited[y][x - 1])) {
            stack.push(pair<int, int>(x, y));
            if (y + 1 < map.size() && !visited[y + 1][x]) y += 1;
            else if (y - 1 > -1 && !visited[y - 1][x]) y -= 1;
            else if (x + 1 < map[y].size() && !visited[y][x + 1]) x += 1;
            else if (x - 1 > -1 && !visited[y][x - 1]) x -= 1;
            visited[y][x] = true;
            path.emplace_back(pair<int, int>(x, y));
        } else {
            if (!stack.empty()) {
                x = stack.top().first;
                y = stack.top().second;
                stack.pop();
                path.pop_back();
            }
        }
        if (x == destX && y == destY) destFound = true;
        allVisited = true;
        for (auto &i: visited) {
            for (auto &&j: i) {
                if (!j) allVisited = false;
            }
        }
    }
    return path;
}

vector<pair<int, int>> Algorithms::bfs(int startX, int startY, int destX, int destY, vector<vector<int>> &map) {

}

vector<pair<int, int>> Algorithms::ucs(int startX, int startY, int destX, int destY, vector<vector<int>> &map) {

}

Algorithms::~Algorithms() = default;
