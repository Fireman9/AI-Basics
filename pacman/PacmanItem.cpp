#include "PacmanItem.h"

PacmanItem::PacmanItem() {
    pacmanLeft.load("../images/pacmanLeft.png");
    pacmanLeftEating.load("../images/pacmanLeftEating.png");

    pacmanRight.load("../images/pacmanRight.png");
    pacmanRightEating.load("../images/pacmanRightEating.png");

    pacmanTop.load("../images/pacmanTop.png");
    pacmanTopEating.load("../images/pacmanTopEating.png");

    pacmanBottom.load("../images/pacmanBottom.png");
    pacmanBottomEating.load("../images/pacmanBottomEating.png");

    direction = 0;
    prevDirection = 1;
    eating = false;
}

QRectF PacmanItem::boundingRect() const {
    return {0, 0, 20, 20};
}

void PacmanItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    if (direction == 1) {
        if (eating) {
            painter->drawImage(0, 0, pacmanLeftEating);
        } else {
            painter->drawImage(0, 0, pacmanLeft);
        }
    } else if (direction == 2) {
        if (eating) {
            painter->drawImage(0, 0, pacmanRightEating);
        } else {
            painter->drawImage(0, 0, pacmanRight);
        }
    } else if (direction == 3) {
        if (eating) {
            painter->drawImage(0, 0, pacmanTopEating);
        } else {
            painter->drawImage(0, 0, pacmanTop);
        }
    } else {
        if (eating) {
            painter->drawImage(0, 0, pacmanBottomEating);
        } else {
            painter->drawImage(0, 0, pacmanBottom);
        }
    }
}

QPoint PacmanItem::move(const vector<vector<int>> &map, vector<QGraphicsItem *> &biscuitTextures,
                        QPoint blinkyPos, QPoint pinkyPos, QPoint inkyPos, QPoint clydePos,
                        int blinkyDir, int pinkyDir, int inkyDir, int clydeDir) {
    double x = (pos().x() + 10) / 20;
    double y = (pos().y() + 10) / 20;

    int speed = 6;

    // tunnel for main map
//    if ((int) x == -1 and (int) y == 14 and direction == 1) {
//        setPos(28 * 20, 14 * 20);
//    }
//    if ((int) x == 28 and (int) y == 14 and direction == 2) {
//        setPos(-1 * 20, 14 * 20);
//    }

    // tunnel
    if ((int) x == -1 and (int) y == 15 and direction == 1) {
        setPos(28 * 20, 15 * 20);
    }
    if ((int) x == 28 and (int) y == 15 and direction == 2) {
        setPos(-1 * 20, 15 * 20);
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

    Timer t;
    t.startTimer();

    Node minimaxTree(true, true, 0, 0, 0, QPoint((int) x, (int) y),
                     blinkyPos, pinkyPos, inkyPos, clydePos,
                     blinkyDir, pinkyDir, inkyDir, clydeDir,
                     map);
    const vector<Node> &nextMoveNode = minimaxTree.getChildren();
    QPoint nextMove = nextMoveNode[minimaxTree.getBestChildIndex()].getPacmanPos();
    if (!nextMoveNode.empty()) {
        if ((int) x - nextMove.x() == -1) {
            direction = 2;
        } else if ((int) x - nextMove.x() == 1) {
            direction = 1;
        } else if ((int) y - nextMove.y() == -1) {
            direction = 4;
        } else if ((int) y - nextMove.y() == 1) {
            direction = 3;
        }
    }

    t.stopTimer();
    cout << "Node: " << t.getElapsedTime() * 1000 << endl << endl;

    return {(int) x, (int) y};
}

int PacmanItem::getDirection() {
    return direction;
}

void PacmanItem::setDirection(int newDirection) {
    direction = newDirection;
}

void PacmanItem::setEating(bool newEating) {
    eating = newEating;
}

PacmanItem::~PacmanItem() = default;
