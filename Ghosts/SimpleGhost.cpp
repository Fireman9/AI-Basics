#include "SimpleGhost.h"

#include <random>

SimpleGhost::SimpleGhost() {
    ghostTextureLeft.load("../images/blinkyLeft.png");
    ghostTextureRight.load("../images/blinkyRight.png");
    ghostTextureTop.load("../images/blinkyTop.png");
    ghostTextureBottom.load("../images/blinkyBottom.png");
    direction = 0;
}

QRectF SimpleGhost::boundingRect() const {
    return {0, 0, 20, 20};
}

void SimpleGhost::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    if (direction == 1) {
        painter->drawImage(0, 0, ghostTextureLeft);
    } else if (direction == 2) {
        painter->drawImage(0, 0, ghostTextureRight);
    } else if (direction == 3) {
        painter->drawImage(0, 0, ghostTextureTop);
    } else {
        painter->drawImage(0, 0, ghostTextureBottom);
    }
}

QPoint SimpleGhost::move(vector<vector<int>> &map, QPoint pacmanPos, bool canMove, bool random) {
    double x = (pos().x() + 10) / 20;
    double y = (pos().y() + 10) / 20;

    int speed = 5;

    // tunnel
    if ((int) x == -1 and (int) y == 15 and direction == 1) {
        setPos(28 * 20, 15 * 20);
    }
    if ((int) x == 28 and (int) y == 15 and direction == 2) {
        setPos(-1 * 20, 15 * 20);
    }

    if (canMove) {
        Movement::moveItem(this, x, y, direction, map, speed, true);
    }

    x = (pos().x() + 10) / 20;
    y = (pos().y() + 10) / 20;

    vector<int> randomDirs;

    if (x - (int) x == 0.5 && y - (int) y == 0.5 && canMove) {
        if (!((int) x >= 12 && (int) x <= 16 && (int) y >= 12 && (int) y <= 16)) {
            if (random) {
                if (direction != 1) {
                    if (!Movement::checkRightBlock(x, y, map, 0.6, false)) randomDirs.push_back(2);
                }
                if (direction != 2) {
                    if (!Movement::checkLeftBlock(x, y, map, 0.6, false)) randomDirs.push_back(1);
                }
                if (direction != 3) {
                    if (!Movement::checkBottomBlock(x, y, map, 0.6, false)) randomDirs.push_back(4);
                }
                if (direction != 4) {
                    if (!Movement::checkTopBlock(x, y, map, 0.6, false)) randomDirs.push_back(3);
                }
                shuffle(randomDirs.begin(), randomDirs.end(), std::mt19937(std::random_device()()));
                if (!randomDirs.empty()) direction = randomDirs[0];
            } else {
                Algorithms alg;
                vector<pair<int, int>> path;
                path = alg.aStar((int) x, (int) y, pacmanPos.x(), pacmanPos.y(), map, true, false, direction);
                if (!path.empty()) {
                    if ((int) x - path[path.size() - 1].first == -1) {
                        direction = 2;
                    } else if ((int) x - path[path.size() - 1].first == 1) {
                        direction = 1;
                    } else if ((int) y - path[path.size() - 1].second == -1) {
                        direction = 4;
                    } else if ((int) y - path[path.size() - 1].second == 1) {
                        direction = 3;
                    }
                }
            }
        }
    }
    return {(int) x, (int) y};
}

void SimpleGhost::setDirection(int newDirection) {
    direction = newDirection;
}

int SimpleGhost::getDirection() {
    return direction;
}

QPoint SimpleGhost::getPos() {
    return {(int) (pos().x() + 10) / 20, (int) (pos().y() + 10) / 20};
}

SimpleGhost::~SimpleGhost() = default;
