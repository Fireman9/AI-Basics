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
        bool br = false;
        for (auto &i: visited) {
            if (br) break;
            for (auto &&j: i) {
                if (!j) {
                    allVisited = false;
                    br = true;
                    break;
                }
            }
        }
    }
    return path;
}

vector<pair<int, int>> Algorithms::bfs(int startX, int startY, int destX, int destY, vector<vector<int>> &map) {
    vector<pair<int, int>> path;
    vector<vector<pair<int, int>>> prev(map[0].size());
    for (auto &i: prev) {
        for (int j = 0; j < map.size(); j++) {
            i.emplace_back(-1, -1);
        }
    }

    vector<vector<bool>> visited(map.size(), vector<bool>(map[0].size(), false));
    for (int i = 0; i < visited.size(); i++) {
        for (int j = 0; j < visited[i].size(); j++) {
            if (map[i][j] == 1) visited[i][j] = true;
        }
    }

    int x = startX;
    int y = startY;
    visited[y][x] = true;

    bool allVisited = false;
    bool destFound = false;
    queue<pair<int, int>> queue;
    queue.push(pair<int, int>(x, y));
    while (!allVisited && !destFound) {
        x = queue.front().first;
        y = queue.front().second;
        queue.pop();
        visited[y][x] = true;
        if ((y + 1 < map.size() && !visited[y + 1][x]) ||
            (y - 1 > -1 && !visited[y - 1][x]) ||
            (x + 1 < map[y].size() && !visited[y][x + 1]) ||
            (x - 1 > -1 && !visited[y][x - 1])) {
            if (y + 1 < map.size() && !visited[y + 1][x]) {
                queue.push(pair<int, int>(x, y + 1));
                prev[x][y + 1] = pair<int, int>(x, y);
            }
            if (y - 1 > -1 && !visited[y - 1][x]) {
                queue.push(pair<int, int>(x, y - 1));
                prev[x][y - 1] = pair<int, int>(x, y);
            }
            if (x + 1 < map[y].size() && !visited[y][x + 1]) {
                queue.push(pair<int, int>(x + 1, y));
                prev[x + 1][y] = pair<int, int>(x, y);
            }
            if (x - 1 > -1 && !visited[y][x - 1]) {
                queue.push(pair<int, int>(x - 1, y));
                prev[x - 1][y] = pair<int, int>(x, y);
            }
        }
        if (x == destX && y == destY) destFound = true;
        allVisited = true;
        bool br = false;
        for (auto &i: visited) {
            if (br) break;
            for (auto &&j: i) {
                if (!j) {
                    allVisited = false;
                    br = true;
                    break;
                }
            }
        }
    }
    while (prev[x][y].first != -1 || prev[x][y].second != -1) {
        path.emplace_back(pair<int, int>(x, y));
        pair<int, int> pos = prev[x][y];
        x = pos.first;
        y = pos.second;
    }
    return path;
}

vector<pair<int, int>> Algorithms::ucs(int startX, int startY, int destX, int destY, vector<vector<int>> &map) {
    vector<pair<int, int>> path;
    vector<vector<pair<int, int>>> prev(map[0].size());
    for (auto &i: prev) {
        for (int j = 0; j < map.size(); j++) {
            i.emplace_back(-1, -1);
        }
    }

    vector<vector<bool>> visited(map.size(), vector<bool>(map[0].size(), false));
    for (int i = 0; i < visited.size(); i++) {
        for (int j = 0; j < visited[i].size(); j++) {
            if (map[i][j] == 1) visited[i][j] = true;
        }
    }

    int x = startX;
    int y = startY;
    visited[y][x] = true;

    bool allVisited = false;
    bool destFound = false;
    priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<>> queue;
    queue.push(make_pair(1, make_pair(x, y)));
    while (!allVisited && !destFound) {
        x = queue.top().second.first;
        y = queue.top().second.second;
        int length = queue.top().first;
        queue.pop();
        visited[y][x] = true;
        if ((y + 1 < map.size() && !visited[y + 1][x]) ||
            (y - 1 > -1 && !visited[y - 1][x]) ||
            (x + 1 < map[y].size() && !visited[y][x + 1]) ||
            (x - 1 > -1 && !visited[y][x - 1])) {
            if (y + 1 < map.size() && !visited[y + 1][x]) {
                queue.push(make_pair(1 + length, make_pair(x, y + 1)));
                prev[x][y + 1] = pair<int, int>(x, y);
            }
            if (y - 1 > -1 && !visited[y - 1][x]) {
                queue.push(make_pair(1 + length, make_pair(x, y - 1)));
                prev[x][y - 1] = pair<int, int>(x, y);
            }
            if (x + 1 < map[y].size() && !visited[y][x + 1]) {
                queue.push(make_pair(1 + length, make_pair(x + 1, y)));
                prev[x + 1][y] = pair<int, int>(x, y);
            }
            if (x - 1 > -1 && !visited[y][x - 1]) {
                queue.push(make_pair(1 + length, make_pair(x - 1, y)));
                prev[x - 1][y] = pair<int, int>(x, y);
            }
        }
        if (x == destX && y == destY) destFound = true;
        allVisited = true;
        bool br = false;
        for (auto &i: visited) {
            if (br) break;
            for (auto &&j: i) {
                if (!j) {
                    allVisited = false;
                    br = true;
                    break;
                }
            }
        }
    }
    while (prev[x][y].first != -1 || prev[x][y].second != -1) {
        path.emplace_back(pair<int, int>(x, y));
        pair<int, int> pos = prev[x][y];
        x = pos.first;
        y = pos.second;
    }
    return path;
}

vector<pair<int, int>>
Algorithms::aStar(int startX, int startY, int destX, int destY, vector<vector<int>> &map, bool ghost, bool pathDrawing,
                  int direction) {
    vector<pair<int, int>> path;
    vector<vector<pair<int, int>>> prev(map[0].size());
    for (auto &i: prev) {
        for (int j = 0; j < map.size(); j++) {
            i.emplace_back(-1, -1);
        }
    }

    vector<vector<bool>> visited(map.size(), vector<bool>(map[0].size(), false));
    for (int i = 0; i < visited.size(); i++) {
        for (int j = 0; j < visited[i].size(); j++) {
            if (pathDrawing) {
                if (map[i][j] == 1) visited[i][j] = true;
            } else {
                if (map[i][j] == 1 || map[i][j] == 3) visited[i][j] = true;
            }
        }
    }

    int x = startX;
    int y = startY;
    visited[y][x] = true;

    bool allVisited = false;
    bool destFound = false;
    struct Order {
        bool operator()(pair<int, pair<int, int>> const &a, pair<int, pair<int, int>> const &b) const {
            return a.first > b.first;
        }
    };
    priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, Order> queue;
    queue.push(make_pair(1, make_pair(x, y)));

    bool firstTime = ghost;

    while (!allVisited && !destFound) {
        x = queue.top().second.first;
        y = queue.top().second.second;
        queue.pop();
        visited[y][x] = true;
        if ((y + 1 < map.size() && !visited[y + 1][x]) ||
            (y - 1 > -1 && !visited[y - 1][x]) ||
            (x + 1 < map[y].size() && !visited[y][x + 1]) ||
            (x - 1 > -1 && !visited[y][x - 1])) {
            if (y + 1 < map.size() && !visited[y + 1][x]) {
                if (firstTime && direction == 3) {
                    firstTime = false;
                } else {
                    queue.push(make_pair(1 + (abs(destX - x) + abs(destY - (y + 1))), make_pair(x, y + 1)));
                    prev[x][y + 1] = pair<int, int>(x, y);
                }
            }
            if (y - 1 > -1 && !visited[y - 1][x]) {
                if (firstTime && direction == 4) {
                    firstTime = false;
                } else {
                    queue.push(make_pair(1 + (abs(destX - x) + abs(destY - (y - 1))), make_pair(x, y - 1)));
                    prev[x][y - 1] = pair<int, int>(x, y);
                }
            }
            if (x + 1 < map[y].size() && !visited[y][x + 1]) {
                if (firstTime && direction == 1) {
                    firstTime = false;
                } else {
                    queue.push(make_pair(1 + (abs(destX - (x + 1)) + abs(destY - y)), make_pair(x + 1, y)));
                    prev[x + 1][y] = pair<int, int>(x, y);
                }
            }
            if (x - 1 > -1 && !visited[y][x - 1]) {
                if (firstTime && direction == 2) {
                    firstTime = false;
                } else {
                    queue.push(make_pair(1 + (abs(destX - (x - 1)) + abs(destY - y)), make_pair(x - 1, y)));
                    prev[x - 1][y] = pair<int, int>(x, y);
                }
            }
        }
        if (x == destX && y == destY) destFound = true;
        allVisited = true;
        bool br = false;
        for (auto &i: visited) {
            if (br) break;
            for (auto &&j: i) {
                if (!j) {
                    allVisited = false;
                    br = true;
                    break;
                }
            }
        }
    }
    while (prev[x][y].first != -1 || prev[x][y].second != -1) {
        path.emplace_back(pair<int, int>(x, y));
        pair<int, int> pos = prev[x][y];
        x = pos.first;
        y = pos.second;
    }
    return path;
}

vector<pair<int, int>>
Algorithms::bfsForGhosts(int startX, int startY, int destX, int destY, vector<vector<int>> &map, int direction) {
    vector<pair<int, int>> path;
    vector<vector<pair<int, int>>> prev(map[0].size());
    for (auto &i: prev) {
        for (int j = 0; j < map.size(); j++) {
            i.emplace_back(-1, -1);
        }
    }

    vector<vector<bool>> visited(map.size(), vector<bool>(map[0].size(), false));
    for (int i = 0; i < visited.size(); i++) {
        for (int j = 0; j < visited[i].size(); j++) {
            if (map[i][j] == 1) visited[i][j] = true;
        }
    }

    int x = startX;
    int y = startY;
    visited[y][x] = true;

    bool allVisited = false;
    bool destFound = false;
    queue<pair<int, int>> queue;
    queue.push(pair<int, int>(x, y));

    bool firstTime = true;
    while (!allVisited && !destFound) {
        x = queue.front().first;
        y = queue.front().second;
        queue.pop();
        visited[y][x] = true;
        if ((y + 1 < map.size() && !visited[y + 1][x]) ||
            (y - 1 > -1 && !visited[y - 1][x]) ||
            (x + 1 < map[y].size() && !visited[y][x + 1]) ||
            (x - 1 > -1 && !visited[y][x - 1])) {
            if (y + 1 < map.size() && !visited[y + 1][x]) {
                if (firstTime && direction == 3) {
                    firstTime = false;
                } else {
                    queue.push(pair<int, int>(x, y + 1));
                    prev[x][y + 1] = pair<int, int>(x, y);
                }
            }
            if (y - 1 > -1 && !visited[y - 1][x]) {
                if (firstTime && direction == 4) {
                    firstTime = false;
                } else {
                    queue.push(pair<int, int>(x, y - 1));
                    prev[x][y - 1] = pair<int, int>(x, y);
                }
            }
            if (x + 1 < map[y].size() && !visited[y][x + 1]) {
                if (firstTime && direction == 1) {
                    firstTime = false;
                } else {
                    queue.push(pair<int, int>(x + 1, y));
                    prev[x + 1][y] = pair<int, int>(x, y);
                }
            }
            if (x - 1 > -1 && !visited[y][x - 1]) {
                if (firstTime && direction == 2) {
                    firstTime = false;
                } else {
                    queue.push(pair<int, int>(x - 1, y));
                    prev[x - 1][y] = pair<int, int>(x, y);
                }
            }
        }
        if (x == destX && y == destY) destFound = true;
        allVisited = true;
        bool br = false;
        for (auto &i: visited) {
            if (br) break;
            for (auto &&j: i) {
                if (!j) {
                    allVisited = false;
                    br = true;
                    break;
                }
            }
        }
    }
    while (prev[x][y].first != -1 || prev[x][y].second != -1) {
        path.emplace_back(pair<int, int>(x, y));
        pair<int, int> pos = prev[x][y];
        x = pos.first;
        y = pos.second;
    }
    return path;
}

Algorithms::~Algorithms() = default;
