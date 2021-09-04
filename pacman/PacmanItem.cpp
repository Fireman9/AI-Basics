#include "PacmanItem.h"

PacmanItem::PacmanItem() {
    pacmanTexture.load("../images/pacmanMain20.png");
    direction = 1;
    prevDirection = 1;
}

QRectF PacmanItem::boundingRect() const {
    return {0, 0, 20, 20};
}

void PacmanItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->drawImage(0, 0, pacmanTexture);
}

QPoint PacmanItem::move(const vector<vector<int>> &map) {
    double x = (pos().x() + 10) / 20;
    double y = (pos().y() + 10) / 20;

    int speed = 6;

    // tunnel
    if ((int) x == -1 and (int) y == 14 and direction == 1) {
        setPos(28 * 20, 14 * 20);
    }
    if ((int) x == 28 and (int) y == 14 and direction == 2) {
        setPos(-1 * 20, 14 * 20);
    }

    if (prevDirection != direction) {
        if (direction == 1) {
            if (Movement::checkLeftBlock(x, y, map, 0.6, false)) {
                direction = prevDirection;
            } else {
                this->setPos(this->pos().x(), (int) y * 20);
            }
        } else if (direction == 2) {
            if (Movement::checkRightBlock(x, y, map, 0.6, false)) {
                direction = prevDirection;
            } else {
                this->setPos(this->pos().x(), (int) y * 20);
            }
        } else if (direction == 3) {
            if (Movement::checkTopBlock(x, y, map, 0.6, false)) {
                direction = prevDirection;
            } else {
                this->setPos((int) x * 20, this->pos().y());
            }
        } else if (direction == 4) {
            if (Movement::checkBottomBlock(x, y, map, 0.6, false)) {
                direction = prevDirection;
            } else {
                this->setPos((int) x * 20, this->pos().y());
            }
        }
        prevDirection = direction;
    }

    Movement::moveItem(this, x, y, direction, map, speed, false);

    x = (pos().x() + 10) / 20;
    y = (pos().y() + 10) / 20;

    return {(int) x, (int) y};
}

void PacmanItem::setDirection(int newDirection) {
    direction = newDirection;
}

PacmanItem::~PacmanItem() = default;
