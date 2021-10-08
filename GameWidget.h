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
    bool dfs;
    bool bfs;
    bool ucs;
    QPoint randomBiscuitPos;
    QLabel *scoreText;
    QLabel *result;
    QLabel *livesText;
    QTimer gameTimer;

    vector<vector<int>> map;
    vector<pair<int, int>> path;
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

    double setPathesToGhosts(const function<vector<pair<int, int>>(int, int, int, int, vector<vector<int>> &)> &exec,
                             vector<pair<int, int>> &pathToBlinky, vector<pair<int, int>> &pathToPinky,
                             vector<pair<int, int>> &pathToInky, vector<pair<int, int>> &pathToClyde,
                             QPoint &pacmanPos,
                             QPoint &blinkyPos, QPoint &pinkyPos, QPoint &inkyPos, QPoint &clydePos);

    void showPathToGhost(vector<pair<int, int>> &pathToGhost, const QBrush &brush);

    bool checkForScoreChange(QPoint &pacmanPos);

    void moveActorsToStartPos();

    void checkForGameState(QPoint &pacmanPos, QPoint &blinkyPos, QPoint &pinkyPos, QPoint &inkyPos,
                           QPoint &clydePos);
};


#endif //PACMAN_GAMEWIDGET_H
