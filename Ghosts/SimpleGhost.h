#ifndef PACMAN_SIMPLEGHOST_H
#define PACMAN_SIMPLEGHOST_H


#include <QGraphicsItem>
#include <QPainter>
#include <vector>
#include <algorithm>
#include <random>
#include <iostream>

#include "../Movement.h"

using namespace std;

class SimpleGhost : public QGraphicsItem {

public:
    SimpleGhost();

    QPoint move(const vector<vector<int>> map);

    void setDirection(int newDirection);

    ~SimpleGhost();

protected:
    QRectF boundingRect() const override;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    int direction;
    int prevDirection;

    QImage ghostTextureLeft;
    QImage ghostTextureRight;
    QImage ghostTextureTop;
    QImage ghostTextureBottom;
};


#endif //PACMAN_SIMPLEGHOST_H
