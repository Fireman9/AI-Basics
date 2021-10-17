#ifndef PACMAN_SIMPLEGHOST_H
#define PACMAN_SIMPLEGHOST_H


#include <QGraphicsItem>
#include <QPainter>
#include <vector>
#include <algorithm>
#include <random>
#include <iostream>

#include "../Movement.h"
#include "../Algorithms.h"

using namespace std;

class SimpleGhost : public QGraphicsItem {

public:
    SimpleGhost();

    QPoint move(vector<vector<int>>& map, QPoint pacmanPos, bool canMove, bool random);

    void setDirection(int newDirection);

    int getDirection();

    QPoint getPos();

    ~SimpleGhost();

protected:
    QRectF boundingRect() const override;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    int direction;

    QImage ghostTextureLeft;
    QImage ghostTextureRight;
    QImage ghostTextureTop;
    QImage ghostTextureBottom;
};


#endif //PACMAN_SIMPLEGHOST_H
