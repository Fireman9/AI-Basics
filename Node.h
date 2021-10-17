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
    Node(bool root, bool max, double alpha, double beta, int depth, double value,
         QPoint pacmanPos, QPoint blinkyPos, QPoint pinkyPos, QPoint inkyPos, QPoint clydePos,
         int blinkyDir, int pinkyDir, int inkyDir, int clydeDir,
         vector<vector<int>> map, bool expectimax);

    double calculateValue();

    bool biscuitLeft();

    int getDist(int fromX, int fromY, int toX, int toY);

    void getAllNewCoordinates(QPoint &ghostPos, vector<QPoint> &pos, int direction, int &newDirection);

    void generateChildren();

    void generateChildrenExpectimax();

    double getValue() const;

    QPoint getPacmanPos() const;

    const vector<Node> &getChildren() const;

    int findFirstBiscuitBfs(bool findGhost);

    ~Node();

private:
    bool root;
    bool max;
    double alpha;
    double beta;
    double finalValue;
    double tempValue;
    double parentValue;
    int depth;
    int depthLimit;

    bool expectimax;

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
