#include "Movement.h"

bool Movement::checkLeftBlock(double x, double y, vector<vector<int>> map, double k, bool ghost) {
    if ((int) (x - k) < 0) {
        return false;
    } else if (map[(int) y][(int) (x - k)] != 1 && ghost) {
        return false;
    } else if (map[(int) y][(int) (x - k)] != 1 && map[(int) y][(int) (x - k)] != 3) {
        return false;
    } else {
        return true;
    }
}

bool Movement::checkRightBlock(double x, double y, vector<vector<int>> map, double k, bool ghost) {
    if ((int) (x + k) > map[0].size()) {
        return false;
    } else if (map[(int) y][(int) (x + k)] != 1 && ghost) {
        return false;
    } else if (map[(int) y][(int) (x + k)] != 1 and map[(int) y][(int) (x + k)] != 3) {
        return false;
    } else {
        return true;
    }
}

bool Movement::checkTopBlock(double x, double y, vector<vector<int>> map, double k, bool ghost) {
    if (map[(int) (y - k)][(int) x] != 1 && ghost) {
        return false;
    } else if (map[(int) (y - k)][(int) x] != 1 and map[(int) (y - k)][(int) x] != 3) {
        return false;
    } else {
        return true;
    }
}

bool Movement::checkBottomBlock(double x, double y, vector<vector<int>> map, double k, bool ghost) {
    if (map[(int) (y + k)][(int) x] != 1 && ghost) {
        return false;
    } else if (map[(int) (y + k)][(int) x] != 1 and map[(int) (y + k)][(int) x] != 3) {
        return false;
    } else {
        return true;
    }
}

void Movement::moveItem(QGraphicsItem *item, double x, double y, int &direction, vector<vector<int>> map, int speed,
                        bool ghost) {
    if (direction == 1) {
        if (!Movement::checkLeftBlock(x, y, map, 0.6, ghost)) {
            item->setPos(item->mapToParent(-speed, 0));
        } else {
            item->setPos((int) x * 20, (int) y * 20);
            direction = 0;
        }
    } else if (direction == 2) {
        if (!Movement::checkRightBlock(x, y, map, 0.6, ghost)) {
            item->setPos(item->mapToParent(speed, 0));
        } else {
            item->setPos((int) x * 20, (int) y * 20);
            direction = 0;
        }
    } else if (direction == 3) {
        if (!Movement::checkTopBlock(x, y, map, 0.6, ghost)) {
            item->setPos(item->mapToParent(0, -speed));
        } else {
            item->setPos((int) x * 20, (int) y * 20);
            direction = 0;
        }
    } else if (direction == 4) {
        if (!Movement::checkBottomBlock(x, y, map, 0.6, ghost)) {
            item->setPos(item->mapToParent(0, speed));
        } else {
            item->setPos((int) x * 20, (int) y * 20);
            direction = 0;
        }
    }
}

Movement::Movement() = default;

Movement::~Movement() = default;
