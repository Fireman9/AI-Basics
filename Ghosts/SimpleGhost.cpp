#include "SimpleGhost.h"

SimpleGhost::SimpleGhost() {
    ghostTexture.load("../images/Blinky20.png");
    direction = 0;
    prevDirection = 0;
}

QRectF SimpleGhost::boundingRect() const {
    return {0, 0, 20, 20};
}

void SimpleGhost::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->drawImage(0, 0, ghostTexture);
}

QPoint SimpleGhost::move(const vector<vector<int>> map) {
    double x = (pos().x() + 10) / 20;
    double y = (pos().y() + 10) / 20;
    cout << x << " " << y << endl;

    int speed = 5;

    // tunnel
    if ((int) x == -1 and (int) y == 14 and direction == 1) {
        setPos(28 * 20, 14 * 20);
    }
    if ((int) x == 28 and (int) y == 14 and direction == 2) {
        setPos(-1 * 20, 14 * 20);
    }

    Movement::moveItem(this, x, y, direction, map, speed, true);

    x = (pos().x() + 10) / 20;
    y = (pos().y() + 10) / 20;

    if (x - (int) x == 0.5 && y - (int) y == 0.5) {
        if (direction == 0) {
            if (prevDirection != 0) {
                vector<int> dirs = {1, 2, 3, 4};
                if (prevDirection == 1) {
                    dirs.erase(remove(dirs.begin(), dirs.end(), 2), dirs.end());
                    dirs.erase(remove(dirs.begin(), dirs.end(), 1), dirs.end());
                } else if (prevDirection == 2) {
                    dirs.erase(remove(dirs.begin(), dirs.end(), 2), dirs.end());
                    dirs.erase(remove(dirs.begin(), dirs.end(), 1), dirs.end());
                } else if (prevDirection == 3) {
                    dirs.erase(remove(dirs.begin(), dirs.end(), 4), dirs.end());
                    dirs.erase(remove(dirs.begin(), dirs.end(), 3), dirs.end());
                } else if (prevDirection == 4) {
                    dirs.erase(remove(dirs.begin(), dirs.end(), 4), dirs.end());
                    dirs.erase(remove(dirs.begin(), dirs.end(), 3), dirs.end());
                }
                for (int dir: dirs) {
                    if (dir == 1) {
                        if (Movement::checkLeftBlock(x, y, map, 0.6, true)) {
                            dirs.erase(remove(dirs.begin(), dirs.end(), 1), dirs.end());
                        }
                    } else if (dir == 2) {
                        if (Movement::checkRightBlock(x, y, map, 0.6, true)) {
                            dirs.erase(remove(dirs.begin(), dirs.end(), 2), dirs.end());
                        }
                    } else if (dir == 3) {
                        if (Movement::checkTopBlock(x, y, map, 0.6, true)) {
                            dirs.erase(remove(dirs.begin(), dirs.end(), 3), dirs.end());
                        }
                    } else if (dir == 4) {
                        if (Movement::checkBottomBlock(x, y, map, 0.6, true)) {
                            dirs.erase(remove(dirs.begin(), dirs.end(), 4), dirs.end());
                        }
                    }
                }
                auto rd = std::random_device{};
                auto rng = default_random_engine{rd()};
                shuffle(dirs.begin(), dirs.end(), rng);
                direction = dirs[0];
            }
//            else {
//                vector<int> dirs = {1, 2, 3, 4};
//                auto rd = std::random_device{};
//                auto rng = default_random_engine{rd()};
//                shuffle(dirs.begin(), dirs.end(), rng);
//                direction = dirs[0];
//            }
        } else if (direction == 1) {
            vector<int> dirs = {1};
            if (!Movement::checkTopBlock(x, y, map, 0.6, true)) {
                dirs.push_back(3);
            }
            if (!Movement::checkBottomBlock(x, y, map, 0.6, true)) {
                dirs.push_back(4);
            }
            auto rd = std::random_device{};
            auto rng = default_random_engine{rd()};
            shuffle(dirs.begin(), dirs.end(), rng);
            direction = dirs[0];
        } else if (direction == 2) {
            vector<int> dirs = {2};
            if (!Movement::checkTopBlock(x, y, map, 0.6, true)) {
                dirs.push_back(3);
            }
            if (!Movement::checkBottomBlock(x, y, map, 0.6, true)) {
                dirs.push_back(4);
            }
            auto rd = std::random_device{};
            auto rng = default_random_engine{rd()};
            shuffle(dirs.begin(), dirs.end(), rng);
            direction = dirs[0];
        } else if (direction == 3) {
            vector<int> dirs = {3};
            if (!Movement::checkLeftBlock(x, y, map, 0.6, true)) {
                dirs.push_back(1);
            }
            if (!Movement::checkRightBlock(x, y, map, 0.6, true)) {
                dirs.push_back(2);
            }
            auto rd = std::random_device{};
            auto rng = default_random_engine{rd()};
            shuffle(dirs.begin(), dirs.end(), rng);
            direction = dirs[0];
        } else if (direction == 4) {
            vector<int> dirs = {4};
            if (!Movement::checkLeftBlock(x, y, map, 0.6, true)) {
                dirs.push_back(1);
            }
            if (!Movement::checkRightBlock(x, y, map, 0.6, true)) {
                dirs.push_back(2);
            }
            auto rd = std::random_device{};
            auto rng = default_random_engine{rd()};
            shuffle(dirs.begin(), dirs.end(), rng);
            direction = dirs[0];
        }
    }
    if (direction != 0) {
        prevDirection = direction;
    }

    return {(int) x, (int) y};
}

void SimpleGhost::setDirection(int newDirection) {
    direction = newDirection;
}

SimpleGhost::~SimpleGhost() {

}