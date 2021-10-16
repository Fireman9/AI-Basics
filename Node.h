#ifndef PACMAN_NODE_H
#define PACMAN_NODE_H


#include <QPoint>
#include <vector>
#include <utility>
#include <random>
#include <iostream>

#include "Algorithms.h"
#include "Movement.h"
#include "Timer.h"

using namespace std;

class Node {
public:
    Node(bool root, bool max, int alpha, int beta, int depth,
         QPoint pacmanPos, QPoint blinkyPos, QPoint pinkyPos, QPoint inkyPos, QPoint clydePos,
         int blinkyDir, int pinkyDir, int inkyDir, int clydeDir,
         vector<vector<int>> map);

    double calculateValue();

    bool biscuitLeft();

    int getDist(int fromX, int fromY, int toX, int toY);

    void getAllNewCoordinates(QPoint &ghostPos, vector<QPoint> &pos, int direction, int &newDirection);

    void generateChildren();

    double getValue();

    int calculateBestChild();

    QPoint getPacmanPos() const;

    const vector<Node> &getChildren() const;

    int getBestChildIndex() const;

    int findFirstBiscuitBfs(bool findGhost);

    ~Node();

private:
    bool root;
    bool max;
    int alpha;
    int beta;
    double value;
    int depth;
    int depthLimit;
    int bestChildIndex;

    int blinkyDir;
    int pinkyDir;
    int inkyDir;
    int clydeDir;

    QPoint pacmanPos;
    QPoint blinkyPos;
    QPoint pinkyPos;
    QPoint inkyPos;
    QPoint clydePos;

    vector<vector<int>> map;

    vector<Node> children;
};


#endif //PACMAN_NODE_H
