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
    this->depthLimit = 3;

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
    if (this->map[this->pacmanPos.y()][this->pacmanPos.x()] == 0)
        this->map[this->pacmanPos.y()][this->pacmanPos.x()] = 2;

    this->value = calculateValue();

    generateChildren();
    this->bestChildIndex = getBestChild();
}

double Node::calculateValue() {
    vector<QPoint> points;
    int minDist = getPoints(points);
    int pathToBlinky = getDist(pacmanPos.x(), pacmanPos.y(), blinkyPos.x(), blinkyPos.y());
    int pathToPinky = getDist(pacmanPos.x(), pacmanPos.y(), pinkyPos.x(), pinkyPos.y());
    int pathToInky = getDist(pacmanPos.x(), pacmanPos.y(), inkyPos.x(), inkyPos.y());
    int pathToClyde = getDist(pacmanPos.x(), pacmanPos.y(), clydePos.x(), clydePos.y());
    double avgGhostDist = (double) (pathToBlinky + pathToPinky + pathToInky + pathToClyde) / 4;
    return avgGhostDist - minDist;
}

int Node::getPoints(vector<QPoint> &points) {
    int minDist = 9999;
    for (int i = 0; i < map.size(); ++i) {
        for (int j = 0; j < map[i].size(); ++j) {
            if (map[i][j] == 0) {
                int dist = getDist(pacmanPos.x(), pacmanPos.y(), j, i);
                if (dist == minDist) {
                    points.emplace_back(j, i);
                } else if (dist < minDist) {
                    points.clear();
                    points.emplace_back(j, i);
                    minDist = dist;
                }
            }
        }
    }
    return minDist;
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
    vector<QPoint> biscuitPoints;
    getPoints(biscuitPoints);
    if (biscuitPoints.empty()) return;
    shuffle(biscuitPoints.begin(), biscuitPoints.end(), std::mt19937(std::random_device()()));

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

int Node::getBestChild() {
    if (children.empty()) return -1;
    bestChildIndex = 0;
    double bestValue = -9999;
    for (int i = 0; i < children.size(); ++i) {
        if (children[i].bestChildIndex != -1) children[i].value += children[i].children[bestChildIndex].value;
        if (children[i].value > bestValue) {
            bestValue = children[i].value;
            bestChildIndex = i;
        }
    }
    return bestChildIndex;
}

Node::~Node() = default;
