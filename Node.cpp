#include "Node.h"

Node::Node(bool root, bool max, int alpha, int beta, int depth,
           QPoint pacmanPos, QPoint blinkyPos, QPoint pinkyPos, QPoint inkyPos, QPoint clydePos,
           int blinkyDir, int pinkyDir, int inkyDir, int clydeDir,
           vector<vector<int>> map) {
    this->root = root;
    this->max = max;
    this->alpha = alpha;
    this->beta = beta;
    this->depth = depth;
    this->depthLimit = 4;

    this->blinkyDir = blinkyDir;
    this->pinkyDir = pinkyDir;
    this->inkyDir = inkyDir;
    this->clydeDir = clydeDir;

    this->pacmanPos = pacmanPos;
    this->blinkyPos = blinkyPos;
    this->pinkyPos = pinkyPos;
    this->inkyPos = inkyPos;
    this->clydePos = clydePos;

    this->map = move(map);
    this->value = calculateValue();
    if (this->map[this->pacmanPos.y()][this->pacmanPos.x()] == 0) {
        this->map[this->pacmanPos.y()][this->pacmanPos.x()] = 2;
    }

    generateChildren();
    this->bestChildIndex = calculateBestChild();
}

double Node::calculateValue() {
    double score;
    if (!max) {
        int minDist = findFirstBiscuitBfs(false);
        score = -minDist * 3;
        if (minDist == 0) {
            score += 100;
        }
    } else {
        int minPath = findFirstBiscuitBfs(true);
        score = minPath;
        if (minPath == 0) {
            score -= 9999;
        } else if (minPath == 1) {
            score -= 500;
        } else if (minPath == 2) {
            score -= 200;
        }
    }
    return score;
}

int Node::findFirstBiscuitBfs(bool findGhost) {
    if (blinkyPos.x() == -1 and blinkyPos.y() == 15) {
        blinkyPos.setX(0);
    }
    if (blinkyPos.x() == 28 and blinkyPos.y() == 15) {
        blinkyPos.setX(27);
    }
    int prevMapPosBlinky = map[blinkyPos.y()][blinkyPos.x()];
    int prevMapPosPinky = map[pinkyPos.y()][pinkyPos.x()];
    int prevMapPosInky = map[inkyPos.y()][inkyPos.x()];
    int prevMapPosClyde = map[clydePos.y()][clydePos.x()];
    if (!findGhost) {
        map[blinkyPos.y()][blinkyPos.x()] = 1;
        map[pinkyPos.y()][pinkyPos.x()] = 1;
        map[inkyPos.y()][inkyPos.x()] = 1;
        map[clydePos.y()][clydePos.x()] = 1;
    } else {
        map[blinkyPos.y()][blinkyPos.x()] = 7;
        map[pinkyPos.y()][pinkyPos.x()] = 7;
        map[inkyPos.y()][inkyPos.x()] = 7;
        map[clydePos.y()][clydePos.x()] = 7;
    }

    vector<QPoint> path;
    vector<vector<QPoint>> prev(map[0].size());
    for (auto &i: prev) {
        for (int j = 0; j < map.size(); j++) {
            i.emplace_back(-1, -1);
        }
    }

    vector<vector<bool>> visited(map.size(), vector<bool>(map[0].size(), false));
    for (int i = 0; i < visited.size(); i++) {
        for (int j = 0; j < visited[i].size(); j++) {
            if (findGhost) {
                if (map[i][j] == 1) visited[i][j] = true;
            } else {
                if (map[i][j] == 1 || map[i][j] == 3) visited[i][j] = true;
            }
        }
    }

    int x, y;
    bool allVisited = false;
    bool destFound = false;
    queue<QPoint> queue;
    queue.push(QPoint(pacmanPos.x(), pacmanPos.y()));
    while (!allVisited && !destFound) {
        if (queue.empty()) {
            allVisited = true;
            break;
        }
        x = queue.front().x();
        y = queue.front().y();
        queue.pop();
        visited[y][x] = true;
        if (y + 1 < map.size() && !visited[y + 1][x]) {
            queue.push(QPoint(x, y + 1));
            prev[x][y + 1] = QPoint(x, y);
        }
        if (y - 1 > -1 && !visited[y - 1][x]) {
            queue.push(QPoint(x, y - 1));
            prev[x][y - 1] = QPoint(x, y);
        }
        if (x + 1 < map[y].size() && !visited[y][x + 1]) {
            queue.push(QPoint(x + 1, y));
            prev[x + 1][y] = QPoint(x, y);
        }
        if (x - 1 > -1 && !visited[y][x - 1]) {
            queue.push(QPoint(x - 1, y));
            prev[x - 1][y] = QPoint(x, y);
        }

        if (!findGhost) {
            if (map[y][x] == 0)
                destFound = true;
            else {
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
        } else {
            if (map[y][x] == 7)
                destFound = true;
            else {
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
        }

    }
    if (!allVisited && destFound) {
        while (prev[x][y].x() != -1 || prev[x][y].y() != -1) {
            path.emplace_back(QPoint(x, y));
            QPoint pos = prev[x][y];
            x = pos.x();
            y = pos.y();
        }
    }

    map[blinkyPos.y()][blinkyPos.x()] = prevMapPosBlinky;
    map[pinkyPos.y()][pinkyPos.x()] = prevMapPosPinky;
    map[inkyPos.y()][inkyPos.x()] = prevMapPosInky;
    map[clydePos.y()][clydePos.x()] = prevMapPosClyde;

    if (allVisited && path.empty()) {
        return 9999;
    }
    return (int) path.size();
}

bool Node::biscuitLeft() {
    for (auto &i: map) {
        for (int j: i) {
            if (j == 0) return true;
        }
    }
    return false;
}

int Node::getDist(int fromX, int fromY, int toX, int toY) {
    return abs(fromX - toX) + abs(fromY - toY);
}

void Node::getAllNewCoordinates(QPoint &ghostPos, vector<QPoint> &pos, int direction, int &newDirection) {
    if (ghostPos.x() >= 12 && ghostPos.x() <= 16 && ghostPos.y() >= 12 && ghostPos.y() <= 16) {
        pos.emplace_back(ghostPos.x(), ghostPos.y());
        newDirection = 0;
        return;
    }
    if (direction != 1) {
        if (!Movement::checkRightBlock(ghostPos.x(), ghostPos.y(), map, 0.6, true)) {
            pos.emplace_back(ghostPos.x() + 1, ghostPos.y());
            newDirection = 2;
        }
    }
    if (direction != 2) {
        if (!Movement::checkLeftBlock(ghostPos.x(), ghostPos.y(), map, 0.6, true)) {
            pos.emplace_back(ghostPos.x() - 1, ghostPos.y());
            newDirection = 1;
        }
    }
    if (direction != 3) {
        if (!Movement::checkBottomBlock(ghostPos.x(), ghostPos.y(), map, 0.6, true)) {
            pos.emplace_back(ghostPos.x(), ghostPos.y() + 1);
            newDirection = 4;
        }
    }
    if (direction != 4) {
        if (!Movement::checkTopBlock(ghostPos.x(), ghostPos.y(), map, 0.6, true)) {
            pos.emplace_back(ghostPos.x(), ghostPos.y() - 1);
            newDirection = 3;
        }
    }
}

void Node::generateChildren() {
    if (depth == depthLimit) return;
    if (!biscuitLeft()) return;

    vector<QPoint> newPacmanPos;
    vector<QPoint> newBlinkyPos;
    vector<QPoint> newPinkyPos;
    vector<QPoint> newInkyPos;
    vector<QPoint> newClydePos;
    int newBlinkyDir;
    int newPinkyDir;
    int newInkyDir;
    int newClydeDir;
    vector<vector<int>> newMap = map;

    if (max) {
        if (!Movement::checkRightBlock(pacmanPos.x(), pacmanPos.y(), map, 1, false)) {
            newPacmanPos.emplace_back(pacmanPos.x() + 1, pacmanPos.y());
        }
        if (!Movement::checkLeftBlock(pacmanPos.x(), pacmanPos.y(), map, 1, false)) {
            newPacmanPos.emplace_back(pacmanPos.x() - 1, pacmanPos.y());
        }
        if (!Movement::checkBottomBlock(pacmanPos.x(), pacmanPos.y(), map, 1, false)) {
            newPacmanPos.emplace_back(pacmanPos.x(), pacmanPos.y() + 1);
        }
        if (!Movement::checkTopBlock(pacmanPos.x(), pacmanPos.y(), map, 1, false)) {
            newPacmanPos.emplace_back(pacmanPos.x(), pacmanPos.y() - 1);
        }
        for (auto &pacman: newPacmanPos) {
            children.emplace_back(
                    Node(false, false, 0, 0, depth + 1, pacman,
                         blinkyPos, pinkyPos, inkyPos, clydePos,
                         blinkyDir, pinkyDir, inkyDir, clydeDir,
                         newMap)
            );
        }
    } else {
        getAllNewCoordinates(blinkyPos, newBlinkyPos, blinkyDir, newBlinkyDir);
        getAllNewCoordinates(pinkyPos, newPinkyPos, pinkyDir, newPinkyDir);
        getAllNewCoordinates(inkyPos, newInkyPos, inkyDir, newInkyDir);
        getAllNewCoordinates(clydePos, newClydePos, clydeDir, newClydeDir);

        for (auto &blinky: newBlinkyPos) {
            for (auto &pinky: newPinkyPos) {
                for (auto &inky: newInkyPos) {
                    for (auto &clyde: newClydePos) {
                        children.emplace_back(
                                Node(false, true, 0, 0, depth + 1, pacmanPos,
                                     blinky, pinky, inky, clyde,
                                     newBlinkyDir, newPinkyDir, newInkyDir, newClydeDir,
                                     newMap)
                        );
                    }
                }
            }
        }
    }
}

double Node::getValue() {
    return this->value;
}

int Node::calculateBestChild() {
    if (children.empty()) return -1;
    if (max) {
        bestChildIndex = 0;
        double bestValue = -9999;
        for (int i = 0; i < children.size(); ++i) {
            if (children[i].bestChildIndex != -1)
                children[i].value += children[i].children[children[i].bestChildIndex].value;
            if (children[i].value > bestValue) {
                bestValue = children[i].value;
                bestChildIndex = i;
            }
        }
        return bestChildIndex;
    } else {
        bestChildIndex = 0;
        double bestValue = 9999;
        for (int i = 0; i < children.size(); ++i) {
            if (children[i].bestChildIndex != -1)
                children[i].value += children[i].children[children[i].bestChildIndex].value;
            if (children[i].value < bestValue) {
                bestValue = children[i].value;
                bestChildIndex = i;
            }
        }
        return bestChildIndex;
    }

}

QPoint Node::getPacmanPos() const {
    return pacmanPos;
}

const vector<Node> &Node::getChildren() const {
    return children;
}

int Node::getBestChildIndex() const {
    return bestChildIndex;
}

Node::~Node() = default;
