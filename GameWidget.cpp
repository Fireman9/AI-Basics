#include "GameWidget.h"

GameWidget::GameWidget(QWidget *parent) :
        QWidget(parent) {
    this->score = 0;
    this->lives = 3;
    canMoveBlinky = false;
    canMovePinky = false;
    canMoveInky = false;
    canMoveClyde = false;
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

    gameTimer.start(70);
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
    event->accept();
}

void GameWidget::tunnelCoordinates(QPoint &pos) {
    if (pos.x() == -1) {
        pos.setX(0);
    } else if (pos.x() == 28) {
        pos.setX(27);
    }
}

void
GameWidget::setPathesToGhosts(
        const function<vector<pair<int, int>>(int, int, int, int, vector<vector<int>> &, bool, bool, int)> &exec,
        vector<pair<int, int>> &pathToBlinky, vector<pair<int, int>> &pathToPinky,
        vector<pair<int, int>> &pathToInky, vector<pair<int, int>> &pathToClyde,
        QPoint &pacmanPos,
        QPoint &blinkyPos, QPoint &pinkyPos, QPoint &inkyPos, QPoint &clydePos) {
    pathToBlinky = exec(blinkyPos.x(), blinkyPos.y(), pacmanPos.x(), pacmanPos.y(), map, true, true,
                        blinky->getDirection());
    pathToPinky = exec(pinkyPos.x(), pinkyPos.y(), pacmanPos.x(), pacmanPos.y(), map, true, true,
                       pinky->getDirection());
    pathToInky = exec(inkyPos.x(), inkyPos.y(), pacmanPos.x(), pacmanPos.y(), map, true, true, inky->getDirection());
    pathToClyde = exec(clydePos.x(), clydePos.y(), pacmanPos.x(), pacmanPos.y(), map, true, true,
                       clyde->getDirection());
}

void GameWidget::showPathToGhost(vector<pair<int, int>> &pathToGhost, const QBrush &brush) {
    for (int i = 0; i < pathToGhost.size(); i++) {
        if (i == 0 || i == pathToGhost.size() - 1) continue;
        auto *pathTexture = new QGraphicsRectItem(0, 0, 10, 10);
        pathTexture->setPen(Qt::NoPen);
        pathTexture->setBrush(brush);
        pathTexture->setZValue(-1);
        pathTexture->setPos(pathToGhost[i].first * 20 + 5, pathToGhost[i].second * 20 + 5);
        this->pathTextures.push_back(pathTexture);
        this->scene->addItem(pathTexture);
    }
}

void GameWidget::checkForScoreChange(QPoint &pacmanPos) {
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
    } else {
        pacmanTexture->setEating(false);
    }
}

void GameWidget::moveActorsToStartPos() {
    pacmanTexture->setPos(13 * 20, 23 * 20);
    pacmanTexture->setDirection(0);

    blinky->setPos(13 * 20, 14 * 20);
    blinky->setDirection(0);
    canMoveBlinky = false;

    pinky->setPos(14 * 20, 14 * 20);
    pinky->setDirection(0);
    canMovePinky = false;

    inky->setPos(13 * 20, 15 * 20);
    inky->setDirection(0);
    canMoveInky = false;

    clyde->setPos(14 * 20, 15 * 20);
    clyde->setDirection(0);
    canMoveClyde = false;
}

void GameWidget::clock() {
    if (score >= 1 && !canMoveBlinky) {
        blinky->setDirection(3);
        canMoveBlinky = true;
    }
    if (score >= 10 && !canMovePinky) {
        pinky->setDirection(3);
        canMovePinky = true;
    }
    if (score >= 20 && !canMoveInky) {
        inky->setDirection(3);
        canMoveInky = true;
    }
    if (score >= 30 && !canMoveClyde) {
        clyde->setDirection(3);
        canMoveClyde = true;
    }

    QPoint pacmanPos = pacmanTexture->move(map, biscuitTextures,
                                           blinky->getPos(), pinky->getPos(),
                                           inky->getPos(), clyde->getPos(),
                                           blinky->getDirection(), pinky->getDirection(),
                                           inky->getDirection(), clyde->getDirection());
    QPoint blinkyPos = blinky->move(map, pacmanPos, canMoveBlinky, true);
    QPoint pinkyPos = pinky->move(map, pacmanPos, canMovePinky, false);
    QPoint inkyPos = inky->move(map, pacmanPos, canMoveInky, true);
    QPoint clydePos = clyde->move(map, pacmanPos, canMoveClyde, false);

    checkForScoreChange(pacmanPos);

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

    auto execFunctP = bind(&Algorithms::aStar, alg, _1, _2, _3, _4, _5, _6, _7, _8);
    setPathesToGhosts(execFunctP,
                      pathToBlinky, pathToPinky, pathToInky, pathToClyde,
                      pacmanPos, blinkyPos, pinkyPos, inkyPos, clydePos);

    showPathToGhost(pathToBlinky, QBrush(Qt::red));
    showPathToGhost(pathToPinky, QBrush(Qt::gray));
    showPathToGhost(pathToInky, QBrush(Qt::yellow));
    showPathToGhost(pathToClyde, QBrush(Qt::green));

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

    gameTimer.start(70);
}

GameWidget::~GameWidget() = default;
