#include "GameWidget.h"

GameWidget::GameWidget(QWidget *parent) :
        QWidget(parent) {
    this->score = 0;
    this->lives = 3;
    dfs = false;
    bfs = false;
    ucs = true;
    scoreText = new QLabel("Score: " + QString::number(score));
    livesText = new QLabel("Lives: " + QString::number(lives));
    result = new QLabel("You lost!");

    MapGenerator generator;
    this->map = generator.generateMapDfs();

    this->scene = new QGraphicsScene();
    this->scene->setSceneRect(0, 0, 560, 620);
    this->view = new QGraphicsView(this->scene);
    this->view->setBackgroundBrush(QBrush(Qt::black));
    this->view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    this->newGameBut = new QPushButton("New Game", this);

    this->drawMap();

    pacmanTexture = new PacmanItem();
    scene->addItem(pacmanTexture);
    pacmanTexture->setPos(13 * 20, 23 * 20);

    blinky = new SimpleGhost();
    scene->addItem(blinky);
    blinky->setPos(13 * 20, 14 * 20);

    pinky = new SimpleGhost();
    scene->addItem(pinky);
    pinky->setPos(14 * 20, 14 * 20);

    inky = new SimpleGhost();
    scene->addItem(inky);
    inky->setPos(13 * 20, 15 * 20);

    clyde = new SimpleGhost();
    scene->addItem(clyde);
    clyde->setPos(14 * 20, 15 * 20);

    mainLayout = new QVBoxLayout();
    mainLayout->addWidget(scoreText);
    mainLayout->addWidget(view);
    mainLayout->addWidget(livesText);
    mainLayout->addWidget(newGameBut);

    this->setLayout(mainLayout);

    gameTimer.start(50);
    connect(&gameTimer, &QTimer::timeout, this, &GameWidget::clock);
    connect(newGameBut, &QPushButton::clicked, this, &GameWidget::startNewGame);
}

void GameWidget::drawMap() {
    for (int i = 0; i < this->map.size(); i++) {
        for (int j = 0; j < this->map[0].size(); j++) {
            if (this->map[i][j] == 1) {
                auto *wallTexture = new QGraphicsRectItem(0, 0, 20, 20);
                wallTexture->setPen(Qt::NoPen);
                wallTexture->setBrush(QBrush(Qt::blue));
                wallTexture->setPos(j * 20, i * 20);
                this->scene->addItem(wallTexture);
            } else if (this->map[i][j] == 3) {
                auto *blockTexture = new QGraphicsRectItem(0, 0, 20, 5);
                blockTexture->setPen(Qt::NoPen);
                blockTexture->setBrush(QBrush(Qt::darkBlue));
                blockTexture->setPos(j * 20, i * 20);
                this->scene->addItem(blockTexture);
            } else if (this->map[i][j] == 0) {
                auto *biscuitTexture = new QGraphicsRectItem(0, 0, 4, 4);
                biscuitTexture->setPen(Qt::NoPen);
                biscuitTexture->setBrush(QBrush(Qt::white));
                biscuitTexture->setPos(j * 20 + 8, i * 20 + 8);
                this->biscuitTextures.push_back(biscuitTexture);
                this->scene->addItem(biscuitTexture);
            }
        }
    }
}

void GameWidget::keyPressEvent(QKeyEvent *event) {
//    if (event->key() == Qt::Key_A) {
//        pacmanTexture->setDirection(1);
//    } else if (event->key() == Qt::Key_D) {
//        pacmanTexture->setDirection(2);
//    } else if (event->key() == Qt::Key_W) {
//        pacmanTexture->setDirection(3);
//    } else if (event->key() == Qt::Key_S) {
//        pacmanTexture->setDirection(4);
//    }
    if (event->key() == Qt::Key_Z) {
        if (dfs) {
            dfs = false;
            bfs = true;
            ucs = false;
        } else if (bfs) {
            dfs = false;
            bfs = false;
            ucs = true;
        } else {
            dfs = true;
            bfs = false;
            ucs = false;
        }
    }
    event->accept();
}

void GameWidget::tunnelCoordinates(QPoint &pos) {
    if (pos.x() == -1) {
        pos.setX(0);
    } else if (pos.x() == 28) {
        pos.setX(27);
    }
}

double
GameWidget::setPathesToGhosts(const function<vector<pair<int, int>>(int, int, int, int, vector<vector<int>> &)> &exec,
                              vector<pair<int, int>> &pathToBlinky, vector<pair<int, int>> &pathToPinky,
                              vector<pair<int, int>> &pathToInky, vector<pair<int, int>> &pathToClyde,
                              QPoint &pacmanPos,
                              QPoint &blinkyPos, QPoint &pinkyPos, QPoint &inkyPos, QPoint &clydePos) {
    Timer t;

    t.startTimer();
    pathToBlinky = exec(pacmanPos.x(), pacmanPos.y(), blinkyPos.x(), blinkyPos.y(), map);
    pathToPinky = exec(pacmanPos.x(), pacmanPos.y(), pinkyPos.x(), pinkyPos.y(), map);
    pathToInky = exec(pacmanPos.x(), pacmanPos.y(), inkyPos.x(), inkyPos.y(), map);
    pathToClyde = exec(pacmanPos.x(), pacmanPos.y(), clydePos.x(), clydePos.y(), map);
    t.stopTimer();

    return t.getElapsedTime();
}

void GameWidget::showPathToGhost(vector<pair<int, int>> &pathToGhost, const QBrush &brush) {
    for (auto &i: pathToGhost) {
        auto *dfsPathTexture = new QGraphicsRectItem(0, 0, 10, 10);
        dfsPathTexture->setPen(Qt::NoPen);
        dfsPathTexture->setBrush(brush);
        dfsPathTexture->setZValue(-1);
        dfsPathTexture->setPos(i.first * 20 + 5, i.second * 20 + 5);
        this->pathTextures.push_back(dfsPathTexture);
        this->scene->addItem(dfsPathTexture);
    }
}

bool GameWidget::checkForScoreChange(QPoint &pacmanPos) {
    if (-1 < pacmanPos.x() && pacmanPos.x() < 28 && map[pacmanPos.y()][pacmanPos.x()] == 0) {
        pacmanTexture->setEating(true);
        map[pacmanPos.y()][pacmanPos.x()] = 2;
        score++;
        scoreText->setText("Score: " + QString::number(score));
        for (int i = 0; i < biscuitTextures.size(); i++) {
            if ((int) (biscuitTextures[i]->pos().x() / 20) == pacmanPos.x() &&
                (int) (biscuitTextures[i]->pos().y() / 20) == pacmanPos.y()) {
                scene->removeItem(biscuitTextures[i]);
                biscuitTextures.erase(biscuitTextures.begin() + i);
                break;
            }
        }
        return true;
    } else {
        pacmanTexture->setEating(false);
        return false;
    }
}

void GameWidget::moveActorsToStartPos() {
    pacmanTexture->setPos(13 * 20, 23 * 20);
    pacmanTexture->setDirection(0);

    blinky->setPos(13 * 20, 14 * 20);
    blinky->setDirection(0);

    pinky->setPos(14 * 20, 14 * 20);
    pinky->setDirection(0);

    inky->setPos(13 * 20, 15 * 20);
    inky->setDirection(0);

    clyde->setPos(14 * 20, 15 * 20);
    clyde->setDirection(0);
}

void GameWidget::clock() {
    QPoint pacmanPos = pacmanTexture->move(map, biscuitTextures);
    QPoint blinkyPos = blinky->move(map, pacmanPos);
    QPoint pinkyPos = pinky->move(map, pacmanPos);
    QPoint inkyPos = inky->move(map, pacmanPos);
    QPoint clydePos = clyde->move(map, pacmanPos);

    tunnelCoordinates(pacmanPos);
    tunnelCoordinates(blinkyPos);
    tunnelCoordinates(pinkyPos);
    tunnelCoordinates(inkyPos);
    tunnelCoordinates(clydePos);

    for (auto &i: pathTextures) {
        scene->removeItem(i);
    }
    pathTextures.clear();

    Algorithms alg;

    vector<pair<int, int>> pathToBlinky, pathToPinky, pathToInky, pathToClyde;

    if (dfs) {
        auto execFunctP = bind(&Algorithms::bfs, alg, _1, _2, _3, _4, _5);
        double elapsedTime = setPathesToGhosts(execFunctP,
                                               pathToBlinky, pathToPinky, pathToInky, pathToClyde,
                                               pacmanPos, blinkyPos, pinkyPos, inkyPos, clydePos) * 1000;
        cout << "Dfs: " << elapsedTime << "ms" << endl;
    } else if (bfs) {
        auto execFunctP = bind(&Algorithms::bfs, alg, _1, _2, _3, _4, _5);
        double elapsedTime = setPathesToGhosts(execFunctP,
                                               pathToBlinky, pathToPinky, pathToInky, pathToClyde,
                                               pacmanPos, blinkyPos, pinkyPos, inkyPos, clydePos) * 1000;
        cout << "Bfs: " << elapsedTime << "ms" << endl;
    } else {
        auto execFunctP = bind(&Algorithms::ucs, alg, _1, _2, _3, _4, _5);
        double elapsedTime = setPathesToGhosts(execFunctP,
                                               pathToBlinky, pathToPinky, pathToInky, pathToClyde,
                                               pacmanPos, blinkyPos, pinkyPos, inkyPos, clydePos) * 1000;
        cout << "Ucs: " << elapsedTime << "ms" << endl;
    }

    showPathToGhost(pathToBlinky, QBrush(Qt::red));
    showPathToGhost(pathToPinky, QBrush(Qt::gray));
    showPathToGhost(pathToInky, QBrush(Qt::yellow));
    showPathToGhost(pathToClyde, QBrush(Qt::green));

    bool scoreChanged = checkForScoreChange(pacmanPos);

    if (score == 1 && scoreChanged) {
        blinky->setDirection(3);
    }
    if (score == 10 && scoreChanged) {
        pinky->setDirection(3);
    }
    if (score == 20 && scoreChanged) {
        inky->setDirection(3);
    }
    if (score == 30 && scoreChanged) {
        clyde->setDirection(3);
    }

    checkForGameState(pacmanPos, blinkyPos, pinkyPos, inkyPos, clydePos);
}

void GameWidget::checkForGameState(QPoint &pacmanPos, QPoint &blinkyPos, QPoint &pinkyPos, QPoint &inkyPos,
                                   QPoint &clydePos) {
    if (biscuitTextures.empty()) {
        cout << "Win" << endl;
        gameTimer.stop();
        result = new QLabel("You won!");
        result->setGeometry(230, 210, 400, 200);
        result->setStyleSheet(
                "QLabel { color : white; width: 400px; height: 200px; background-color: transparent; border: 0; font-size: 28px; }");
        scene->addWidget(result);
    }

    if (pacmanPos == blinkyPos or pacmanPos == pinkyPos or pacmanPos == inkyPos or pacmanPos == clydePos) {
        lives--;
        livesText->setText("Lives: " + QString::number(lives));
        if (lives != 0) {
            moveActorsToStartPos();
        } else {
            cout << "Lose" << endl;
            result = new QLabel("You lost!");
            result->setGeometry(230, 210, 400, 200);
            result->setStyleSheet(
                    "QLabel { color : white; width: 400px; height: 200px; background-color: transparent; border: 0; font-size: 28px; }");
            scene->addWidget(result);

            gameTimer.stop();
        }
    }
}

void GameWidget::startNewGame() {
    scene->clear();
    score = 0;
    lives = 3;
    scoreText->setText("Score: " + QString::number(score));
    livesText->setText("Lives: " + QString::number(lives));
    biscuitTextures.clear();
    pathTextures.clear();

    MapGenerator generator;
    this->map = generator.generateMapDfs();

    this->drawMap();

    pacmanTexture = new PacmanItem();
    scene->addItem(pacmanTexture);

    blinky = new SimpleGhost();
    scene->addItem(blinky);

    pinky = new SimpleGhost();
    scene->addItem(pinky);

    inky = new SimpleGhost();
    scene->addItem(inky);

    clyde = new SimpleGhost();
    scene->addItem(clyde);

    moveActorsToStartPos();

    gameTimer.start(50);
}

GameWidget::~GameWidget() = default;
