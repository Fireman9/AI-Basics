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
#include <QPushButton>

#include "pacman/PacmanItem.h"
#include "Ghosts/SimpleGhost.h"
#include "MapGenerator.h"
#include "Timer.h"
#include "Algorithms.h"

using namespace std;
using namespace std::placeholders;

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

    void startNewGame();

private:
    int score;
    int lives;
    bool canMoveBlinky;
    bool canMovePinky;
    bool canMoveInky;
    bool canMoveClyde;

    QLabel *scoreText;
    QLabel *result;
    QLabel *livesText;
    QTimer gameTimer;

    vector<vector<int>> map;
    vector<QGraphicsItem *> biscuitTextures;

    vector<QGraphicsItem *> pathTextures;

    QGraphicsScene *scene;
    QGraphicsView *view;
    QVBoxLayout *mainLayout;
    QPushButton *newGameBut;

    PacmanItem *pacmanTexture;
    SimpleGhost *blinky;
    SimpleGhost *pinky;
    SimpleGhost *inky;
    SimpleGhost *clyde;

    void tunnelCoordinates(QPoint &pos);

    void checkForScoreChange(QPoint &pacmanPos);

    void moveActorsToStartPos();

    void checkForGameState(QPoint &pacmanPos, QPoint &blinkyPos, QPoint &pinkyPos, QPoint &inkyPos,
                           QPoint &clydePos);
};


#endif //PACMAN_GAMEWIDGET_H
