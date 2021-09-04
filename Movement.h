#ifndef PACMAN_MOVEMENT_H
#define PACMAN_MOVEMENT_H

#include <vector>
#include <QGraphicsItem>

using namespace std;

class Movement {
public:
    Movement();

    static bool checkLeftBlock(double x, double y, vector<vector<int>> map, double k, bool ghost);

    static bool checkRightBlock(double x, double y, vector<vector<int>> map, double k, bool ghost);

    static bool checkTopBlock(double x, double y, vector<vector<int>> map, double k, bool ghost);

    static bool checkBottomBlock(double x, double y, vector<vector<int>> map, double k, bool ghost);

    static void moveItem(QGraphicsItem *item, double x, double y, int &direction, vector<vector<int>> map,
                         int speed, bool ghost);

    ~Movement();
};


#endif //PACMAN_MOVEMENT_H
