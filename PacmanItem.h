#ifndef PACMAN_PACMANITEM_H
#define PACMAN_PACMANITEM_H


#include <QGraphicsItem>
#include <QPainter>
#include <vector>

using namespace std;

class PacmanItem : public QGraphicsItem {

public:
    PacmanItem();

    QPoint move(const vector<vector<int>> &map);

    void setDirection(int newDirection);

    static bool checkLeftBlock(double x, double y, vector<vector<int>> map, double k);

    static bool checkRightBlock(double x, double y, vector<vector<int>> map, double k);

    static bool checkTopBlock(double x, double y, vector<vector<int>> map, double k);

    static bool checkBottomBlock(double x, double y, vector<vector<int>> map, double k);

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
