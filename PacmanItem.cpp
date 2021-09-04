#include "PacmanItem.h"

PacmanItem::PacmanItem() {
    pacmanTexture.load("images/pacmanMain20.png");
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

    int speed = 5;

    // tunnel
    if ((int) x == -1 and (int) y == 14 and direction == 1) {
        setPos(28 * 20, 14 * 20);
    }
    if ((int) x == 28 and (int) y == 14 and direction == 2) {
        setPos(-1 * 20, 14 * 20);
    }

    if (prevDirection != direction) {
        if (direction == 1) {
            if (checkLeftBlock(x, y, map, 0.6)) {
                direction = prevDirection;
            } else {
                this->setPos(this->pos().x(), (int) y * 20);
            }
        } else if (direction == 2) {
            if (checkRightBlock(x, y, map, 0.6)) {
                direction = prevDirection;
            } else {
                this->setPos(this->pos().x(), (int) y * 20);
            }
        } else if (direction == 3) {
            if (checkTopBlock(x, y, map, 0.6)) {
                direction = prevDirection;
            } else {
                this->setPos((int) x * 20, this->pos().y());
            }
        } else if (direction == 4) {
            if (checkBottomBlock(x, y, map, 0.6)) {
                direction = prevDirection;
            } else {
                this->setPos((int) x * 20, this->pos().y());
            }
        }
        prevDirection = direction;
    }

    if (direction == 1) {
        if (!checkLeftBlock(x, y, map, 0.6)) {
            this->setPos(this->mapToParent(-speed, 0));
        } else {
            this->setPos((int) x * 20, (int) y * 20);
            direction = 0;
        }
    } else if (direction == 2) {
        if (!checkRightBlock(x, y, map, 0.6)) {
            this->setPos(this->mapToParent(speed, 0));
        } else {
            this->setPos((int) x * 20, (int) y * 20);
            direction = 0;
        }
    } else if (direction == 3) {
        if (!checkTopBlock(x, y, map, 0.6)) {
            this->setPos(this->mapToParent(0, -speed));
        } else {
            this->setPos((int) x * 20, (int) y * 20);
            direction = 0;
        }
    } else if (direction == 4) {
        if (!checkBottomBlock(x, y, map, 0.6)) {
            this->setPos(this->mapToParent(0, speed));
        } else {
            this->setPos((int) x * 20, (int) y * 20);
            direction = 0;
        }
    }
    return {(int) x, (int) y};
}

void PacmanItem::setDirection(int newDirection) {
    direction = newDirection;
}

bool PacmanItem::checkLeftBlock(double x, double y, vector<vector<int>> map, double k) {
    if ((int) (x - k) < 0) {
        return false;
    } else if (map[(int) y][(int) (x - k)] != 1 and map[(int) y][(int) (x - k)] != 3) {
        return false;
    } else {
        return true;
    }
}

bool PacmanItem::checkRightBlock(double x, double y, vector<vector<int>> map, double k) {
    if ((int) (x + k) < 0) {
        return false;
    } else if (map[(int) y][(int) (x + k)] != 1 and map[(int) y][(int) (x + k)] != 3) {
        return false;
    } else {
        return true;
    }
}

bool PacmanItem::checkTopBlock(double x, double y, vector<vector<int>> map, double k) {
    if (map[(int) (y - k)][(int) x] != 1 and map[(int) (y - k)][(int) x] != 3) {
        return false;
    } else {
        return true;
    }
}

bool PacmanItem::checkBottomBlock(double x, double y, vector<vector<int>> map, double k) {
    if (map[(int) (y + k)][(int) x] != 1 and map[(int) (y + k)][(int) x] != 3) {
        return false;
    } else {
        return true;
    }
}

PacmanItem::~PacmanItem() = default;
