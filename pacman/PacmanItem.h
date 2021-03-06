#ifndef PACMAN_PACMANITEM_H
#define PACMAN_PACMANITEM_H


#include <QGraphicsItem>
#include <QPainter>
#include <vector>
#include <random>
#include <iostream>

#include "../Movement.h"
#include "../Algorithms.h"
#include "../Node.h"
#include "../Timer.h"

using namespace std;

class PacmanItem : public QGraphicsItem {

public:
    PacmanItem();

    QPoint move(const vector<vector<int>> &map, vector<QGraphicsItem *> &biscuitTextures,
                QPoint blinkyPos, QPoint pinkyPos, QPoint inkyPos, QPoint clydePos,
                int blinkyDir, int pinkyDir, int inkyDir, int clydeDir);

    int getDirection();

    void setDirection(int newDirection);

    void setEating(bool newEating);

    ~PacmanItem();

protected:
    QRectF boundingRect() const override;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    int direction;
    int prevDirection;
    bool eating;

    QImage pacmanLeft;
    QImage pacmanRight;
    QImage pacmanTop;
    QImage pacmanBottom;
    QImage pacmanLeftEating;
    QImage pacmanRightEating;
    QImage pacmanTopEating;
    QImage pacmanBottomEating;
};


#endif //PACMAN_PACMANITEM_H
