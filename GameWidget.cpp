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
    randomBiscuitPos.setX(-1);
    randomBiscuitPos.setY(-1);

//    this->map = {
//            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
//            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
//            {1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1},
//            {1, 4, 1, 2, 2, 1, 0, 1, 2, 2, 2, 1, 0, 1, 1, 0, 1, 2, 2, 2, 1, 0, 1, 2, 2, 1, 4, 1},
//            {1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1},
//            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
//            {1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1},
//            {1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1},
//            {1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1},
//            {1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1},
//            {2, 2, 2, 2, 2, 1, 0, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 0, 1, 2, 2, 2, 2, 2},
//            {2, 2, 2, 2, 2, 1, 0, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 0, 1, 2, 2, 2, 2, 2},
//            {2, 2, 2, 2, 2, 1, 0, 1, 1, 2, 1, 1, 3, 3, 3, 3, 1, 1, 2, 1, 1, 0, 1, 2, 2, 2, 2, 2},
//            {1, 1, 1, 1, 1, 1, 0, 1, 1, 2, 1, 2, 2, 2, 2, 2, 2, 1, 2, 1, 1, 0, 1, 1, 1, 1, 1, 1},
//            {2, 2, 2, 2, 2, 2, 0, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 0, 2, 2, 2, 2, 2, 2},
//            {1, 1, 1, 1, 1, 1, 0, 1, 1, 2, 1, 2, 2, 2, 2, 2, 2, 1, 2, 1, 1, 0, 1, 1, 1, 1, 1, 1},
//            {2, 2, 2, 2, 2, 1, 0, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 0, 1, 2, 2, 2, 2, 2},
//            {2, 2, 2, 2, 2, 1, 0, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 0, 1, 2, 2, 2, 2, 2},
//            {2, 2, 2, 2, 2, 1, 0, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 0, 1, 2, 2, 2, 2, 2},
//            {1, 1, 1, 1, 1, 1, 0, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 0, 1, 1, 1, 1, 1, 1},
//            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
//            {1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1},
//            {1, 4, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 4, 1},
//            {1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1},
//            {1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1},
//            {1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1},
//            {1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1},
//            {1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
//            {1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
//            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
//            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
//    };
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

    timer.start(50);
    connect(&timer, &QTimer::timeout, this, &GameWidget::clock);
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

void GameWidget::clock() {
    QPoint pacmanPos = pacmanTexture->move(map);
    QPoint blinkyPos = blinky->move(map);
    QPoint pinkyPos = pinky->move(map);
    QPoint inkyPos = inky->move(map);
    QPoint clydePos = clyde->move(map);

    if (pacmanPos.x() == -1) {
        pacmanPos.setX(0);
    } else if (pacmanPos.x() == 28) {
        pacmanPos.setX(27);
    }
    if (blinkyPos.x() == -1) {
        blinkyPos.setX(0);
    } else if (blinkyPos.x() == 28) {
        blinkyPos.setX(27);
    }
    if (pinkyPos.x() == -1) {
        pinkyPos.setX(0);
    } else if (pinkyPos.x() == 28) {
        pinkyPos.setX(27);
    }
    if (inkyPos.x() == -1) {
        inkyPos.setX(0);
    } else if (inkyPos.x() == 28) {
        inkyPos.setX(27);
    }
    if (clydePos.x() == -1) {
        clydePos.setX(0);
    } else if (clydePos.x() == 28) {
        clydePos.setX(27);
    }

    for (auto &i: pathTextures) {
        scene->removeItem(i);
    }
    pathTextures.clear();

    Timer t;
    Algorithms alg;

    vector<pair<int, int>> pathToBlinky;
    vector<pair<int, int>> pathToPinky;
    vector<pair<int, int>> pathToInky;
    vector<pair<int, int>> pathToClyde;

    if (dfs) {
        t.startTimer();
        pathToBlinky = alg.dfs(pacmanPos.x(), pacmanPos.y(), blinkyPos.x(), blinkyPos.y(), map);
        pathToPinky = alg.dfs(pacmanPos.x(), pacmanPos.y(), pinkyPos.x(), pinkyPos.y(), map);
        pathToInky = alg.dfs(pacmanPos.x(), pacmanPos.y(), inkyPos.x(), inkyPos.y(), map);
        pathToClyde = alg.dfs(pacmanPos.x(), pacmanPos.y(), clydePos.x(), clydePos.y(), map);
        t.stopTimer();
        cout << "Dfs: " << t.getElapsedTime() * 1000 << "ms" << endl;
    } else if (bfs) {
        t.startTimer();
        pathToBlinky = alg.bfs(pacmanPos.x(), pacmanPos.y(), blinkyPos.x(), blinkyPos.y(), map);
        pathToPinky = alg.bfs(pacmanPos.x(), pacmanPos.y(), pinkyPos.x(), pinkyPos.y(), map);
        pathToInky = alg.bfs(pacmanPos.x(), pacmanPos.y(), inkyPos.x(), inkyPos.y(), map);
        pathToClyde = alg.bfs(pacmanPos.x(), pacmanPos.y(), clydePos.x(), clydePos.y(), map);
        t.stopTimer();
        cout << "Bfs: " << t.getElapsedTime() * 1000 << "ms" << endl;
    } else {
        t.startTimer();
        pathToBlinky = alg.ucs(pacmanPos.x(), pacmanPos.y(), blinkyPos.x(), blinkyPos.y(), map);
        pathToPinky = alg.ucs(pacmanPos.x(), pacmanPos.y(), pinkyPos.x(), pinkyPos.y(), map);
        pathToInky = alg.ucs(pacmanPos.x(), pacmanPos.y(), inkyPos.x(), inkyPos.y(), map);
        pathToClyde = alg.ucs(pacmanPos.x(), pacmanPos.y(), clydePos.x(), clydePos.y(), map);
        t.stopTimer();
        cout << "Ucs: " << t.getElapsedTime() * 1000 << "ms" << endl;
    }

    for (auto &i: pathToBlinky) {
        auto *dfsPathTexture = new QGraphicsRectItem(0, 0, 10, 10);
        dfsPathTexture->setPen(Qt::NoPen);
        dfsPathTexture->setBrush(QBrush(Qt::red));
        dfsPathTexture->setZValue(-1);
        dfsPathTexture->setPos(i.first * 20 + 5, i.second * 20 + 5);
        this->pathTextures.push_back(dfsPathTexture);
        this->scene->addItem(dfsPathTexture);
    }

    for (auto &i: pathToPinky) {
        auto *dfsPathTexture = new QGraphicsRectItem(0, 0, 10, 10);
        dfsPathTexture->setPen(Qt::NoPen);
        dfsPathTexture->setBrush(QBrush(Qt::gray));
        dfsPathTexture->setZValue(-1);
        dfsPathTexture->setPos(i.first * 20 + 5, i.second * 20 + 5);
        this->pathTextures.push_back(dfsPathTexture);
        this->scene->addItem(dfsPathTexture);
    }

    for (auto &i: pathToInky) {
        auto *dfsPathTexture = new QGraphicsRectItem(0, 0, 10, 10);
        dfsPathTexture->setPen(Qt::NoPen);
        dfsPathTexture->setBrush(QBrush(Qt::yellow));
        dfsPathTexture->setZValue(-1);
        dfsPathTexture->setPos(i.first * 20 + 5, i.second * 20 + 5);
        this->pathTextures.push_back(dfsPathTexture);
        this->scene->addItem(dfsPathTexture);
    }

    for (auto &i: pathToClyde) {
        auto *dfsPathTexture = new QGraphicsRectItem(0, 0, 10, 10);
        dfsPathTexture->setPen(Qt::NoPen);
        dfsPathTexture->setBrush(QBrush(Qt::green));
        dfsPathTexture->setZValue(-1);
        dfsPathTexture->setPos(i.first * 20 + 5, i.second * 20 + 5);
        this->pathTextures.push_back(dfsPathTexture);
        this->scene->addItem(dfsPathTexture);
    }

    bool scoreChanged = false;

    if (-1 < pacmanPos.x() && pacmanPos.x() < 28 && map[pacmanPos.y()][pacmanPos.x()] == 0) {
        pacmanTexture->setEating(true);
        map[pacmanPos.y()][pacmanPos.x()] = 2;
        score++;
        scoreChanged = true;
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

    cout << "Pacman" << pacmanPos.x() << " " << pacmanPos.y() << endl;
    if (!path.empty())
        cout << "Next point" << path[path.size() - 1].first << " " << path[path.size() - 1].second << endl;

    if ((randomBiscuitPos.x() == -1 && randomBiscuitPos.y() == -1) ||
        map[randomBiscuitPos.y()][randomBiscuitPos.x()] == 2) {
        path.clear();
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> distr(0, biscuitTextures.size() - 1);
        int randomPos = distr(gen);
        randomBiscuitPos.setX(int((biscuitTextures[randomPos]->x() - 8) / 20));
        randomBiscuitPos.setY(int((biscuitTextures[randomPos]->y() - 8) / 20));
        path = alg.aStar(pacmanPos.x(), pacmanPos.y(), randomBiscuitPos.x(), randomBiscuitPos.y(), map);
        if (!path.empty()) {
            if (pacmanPos.x() - path[path.size() - 1].first == -1) {
                pacmanTexture->setDirection(2);
            } else if (pacmanPos.x() - path[path.size() - 1].first == 1) {
                pacmanTexture->setDirection(1);
            } else if (pacmanPos.y() - path[path.size() - 1].second == -1) {
                pacmanTexture->setDirection(4);
            } else if (pacmanPos.y() - path[path.size() - 1].second == 1) {
                pacmanTexture->setDirection(3);
            }
        }
    } else {
        if (pacmanPos.x() == path[path.size() - 1].first && pacmanPos.y() == path[path.size() - 1].second)
            path.pop_back();
        if (!path.empty()) {
            if (pacmanPos.x() - path[path.size() - 1].first == -1) {
                if (pacmanTexture->getDirection() != 2) pacmanTexture->setDirection(2);
            } else if (pacmanPos.x() - path[path.size() - 1].first == 1) {
                if (pacmanTexture->getDirection() != 1) pacmanTexture->setDirection(1);
            } else if (pacmanPos.y() - path[path.size() - 1].second == -1) {
                if (pacmanTexture->getDirection() != 4) pacmanTexture->setDirection(4);
            } else if (pacmanPos.y() - path[path.size() - 1].second == 1) {
                if (pacmanTexture->getDirection() != 3) pacmanTexture->setDirection(3);
            }
        }
    }


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

    if (biscuitTextures.empty()) {
        cout << "Win" << endl;
        timer.stop();
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
            randomBiscuitPos.setX(-1);
            randomBiscuitPos.setY(-1);
            pacmanTexture->setPos(13 * 20, 23 * 20);
            pacmanTexture->setDirection(0);

            blinky->setPos(13 * 20, 14 * 20);
            blinky->setDirection(3);

            pinky->setPos(14 * 20, 14 * 20);
            pinky->setDirection(3);

            inky->setPos(13 * 20, 15 * 20);
            inky->setDirection(3);

            clyde->setPos(14 * 20, 15 * 20);
            clyde->setDirection(3);

        } else {
            cout << "Lose" << endl;
            result = new QLabel("You lost!");
            result->setGeometry(230, 210, 400, 200);
            result->setStyleSheet(
                    "QLabel { color : white; width: 400px; height: 200px; background-color: transparent; border: 0; font-size: 28px; }");
            scene->addWidget(result);

            timer.stop();
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
    randomBiscuitPos.setX(-1);
    randomBiscuitPos.setY(-1);
//    this->map = {
//            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
//            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
//            {1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1},
//            {1, 4, 1, 2, 2, 1, 0, 1, 2, 2, 2, 1, 0, 1, 1, 0, 1, 2, 2, 2, 1, 0, 1, 2, 2, 1, 4, 1},
//            {1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1},
//            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
//            {1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1},
//            {1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1},
//            {1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1},
//            {1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1},
//            {2, 2, 2, 2, 2, 1, 0, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 0, 1, 2, 2, 2, 2, 2},
//            {2, 2, 2, 2, 2, 1, 0, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 0, 1, 2, 2, 2, 2, 2},
//            {2, 2, 2, 2, 2, 1, 0, 1, 1, 2, 1, 1, 3, 3, 3, 3, 1, 1, 2, 1, 1, 0, 1, 2, 2, 2, 2, 2},
//            {1, 1, 1, 1, 1, 1, 0, 1, 1, 2, 1, 2, 2, 2, 2, 2, 2, 1, 2, 1, 1, 0, 1, 1, 1, 1, 1, 1},
//            {2, 2, 2, 2, 2, 2, 0, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 0, 2, 2, 2, 2, 2, 2},
//            {1, 1, 1, 1, 1, 1, 0, 1, 1, 2, 1, 2, 2, 2, 2, 2, 2, 1, 2, 1, 1, 0, 1, 1, 1, 1, 1, 1},
//            {2, 2, 2, 2, 2, 1, 0, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 0, 1, 2, 2, 2, 2, 2},
//            {2, 2, 2, 2, 2, 1, 0, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 0, 1, 2, 2, 2, 2, 2},
//            {2, 2, 2, 2, 2, 1, 0, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 0, 1, 2, 2, 2, 2, 2},
//            {1, 1, 1, 1, 1, 1, 0, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 0, 1, 1, 1, 1, 1, 1},
//            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
//            {1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1},
//            {1, 4, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 4, 1},
//            {1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1},
//            {1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1},
//            {1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1},
//            {1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1},
//            {1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
//            {1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
//            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
//            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
//    };
    MapGenerator generator;
    this->map = generator.generateMapDfs();

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

    timer.start(50);
}

GameWidget::~GameWidget() = default;
