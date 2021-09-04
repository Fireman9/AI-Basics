#ifndef PACMAN_PACMANITEM_H
#define PACMAN_PACMANITEM_H


#include <QGraphicsItem>
#include <QPainter>
#include <vector>

#include "../Movement.h"

using namespace std;

class PacmanItem : public QGraphicsItem {

public:
    PacmanItem();

    QPoint move(const vector<vector<int>> &map);

    void setDirection(int newDirection);

    ~PacmanItem();

protected:
    QRectF boundingRect() const override;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    int direction;
    int prevDirection;

    QImage pacmanTexture;
};


#endif //PACMAN_PACMANITEM_H
