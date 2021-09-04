#ifndef PACMAN_GAMEWIDGET_H
#define PACMAN_GAMEWIDGET_H


#include <QWidget>
#include <QtGui>
#include <QLabel>
#include <QHBoxLayout>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QVBoxLayout>
#include <QGraphicsRectItem>
#include <vector>

#include "pacman/PacmanItem.h"
#include "Ghosts/SimpleGhost.h"

using namespace std;

class GameWidget : public QWidget {
Q_OBJECT

public:
    explicit GameWidget(QWidget *parent = nullptr);

    void drawMap();

    ~GameWidget();

protected:

    void keyPressEvent(QKeyEvent *event) override;

private slots:

    void clock();

private:
    int biscuit;
    int wall;
    int empty;
    int block;
    int pill;
    int score;
    QLabel *scoreText;
    QTimer timer;

    vector<vector<int>> map;
    vector<QGraphicsItem *> biscuitTextures;

    QGraphicsScene *scene;
    QGraphicsView *view;
    QVBoxLayout *mainLayout;

    PacmanItem *pacmanTexture;
    SimpleGhost *blinky;
    SimpleGhost *pinky;
    SimpleGhost *inky;
    SimpleGhost *clyde;

};


#endif //PACMAN_GAMEWIDGET_H
