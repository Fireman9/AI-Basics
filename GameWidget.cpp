#include "GameWidget.h"

GameWidget::GameWidget(QWidget *parent) :
        QWidget(parent) {
    this->biscuit = 0;
    this->wall = 1;
    this->empty = 2;
    this->block = 3;
    this->pill = 4;
    this->score = 0;
    this->lives = 3;
    scoreText = new QLabel("Score: " + QString::number(score));
    livesText = new QLabel("Lives: " + QString::number(lives));
    result = new QLabel("You lost!");

    this->map = {
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1},
            {1, 4, 1, 2, 2, 1, 0, 1, 2, 2, 2, 1, 0, 1, 1, 0, 1, 2, 2, 2, 1, 0, 1, 2, 2, 1, 4, 1},
            {1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1},
            {1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1},
            {1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1},
            {2, 2, 2, 2, 2, 1, 0, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 0, 1, 2, 2, 2, 2, 2},
            {2, 2, 2, 2, 2, 1, 0, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 0, 1, 2, 2, 2, 2, 2},
            {2, 2, 2, 2, 2, 1, 0, 1, 1, 2, 1, 1, 3, 3, 3, 3, 1, 1, 2, 1, 1, 0, 1, 2, 2, 2, 2, 2},
            {1, 1, 1, 1, 1, 1, 0, 1, 1, 2, 1, 2, 2, 2, 2, 2, 2, 1, 2, 1, 1, 0, 1, 1, 1, 1, 1, 1},
            {2, 2, 2, 2, 2, 2, 0, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 0, 2, 2, 2, 2, 2, 2},
            {1, 1, 1, 1, 1, 1, 0, 1, 1, 2, 1, 2, 2, 2, 2, 2, 2, 1, 2, 1, 1, 0, 1, 1, 1, 1, 1, 1},
            {2, 2, 2, 2, 2, 1, 0, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 0, 1, 2, 2, 2, 2, 2},
            {2, 2, 2, 2, 2, 1, 0, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 0, 1, 2, 2, 2, 2, 2},
            {2, 2, 2, 2, 2, 1, 0, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 0, 1, 2, 2, 2, 2, 2},
            {1, 1, 1, 1, 1, 1, 0, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 0, 1, 1, 1, 1, 1, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1},
            {1, 4, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 4, 1},
            {1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1},
            {1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1},
            {1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1},
            {1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
            {1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
    };
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
    pacmanTexture->setPos(13 * 20 + 10, 23 * 20);

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
    if (event->key() == Qt::Key_A) {
        pacmanTexture->setDirection(1);
    } else if (event->key() == Qt::Key_D) {
        pacmanTexture->setDirection(2);
    } else if (event->key() == Qt::Key_W) {
        pacmanTexture->setDirection(3);
    } else if (event->key() == Qt::Key_S) {
        pacmanTexture->setDirection(4);
    }
    event->accept();
}

void GameWidget::clock() {
    QPoint pacmanPos = pacmanTexture->move(map);
    QPoint blinkyPos = blinky->move(map);
    QPoint pinkyPos = pinky->move(map);
    QPoint inkyPos = inky->move(map);
    QPoint clydePos = clyde->move(map);

    bool scoreChanged = false;

    if (-1 < pacmanPos.x() && pacmanPos.x() < 28 && map[pacmanPos.y()][pacmanPos.x()] == 0) {
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
            pacmanTexture->setPos(13 * 20 + 10, 23 * 20);
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
    this->map = {
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1},
            {1, 4, 1, 2, 2, 1, 0, 1, 2, 2, 2, 1, 0, 1, 1, 0, 1, 2, 2, 2, 1, 0, 1, 2, 2, 1, 4, 1},
            {1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1},
            {1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1},
            {1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1},
            {2, 2, 2, 2, 2, 1, 0, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 0, 1, 2, 2, 2, 2, 2},
            {2, 2, 2, 2, 2, 1, 0, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 0, 1, 2, 2, 2, 2, 2},
            {2, 2, 2, 2, 2, 1, 0, 1, 1, 2, 1, 1, 3, 3, 3, 3, 1, 1, 2, 1, 1, 0, 1, 2, 2, 2, 2, 2},
            {1, 1, 1, 1, 1, 1, 0, 1, 1, 2, 1, 2, 2, 2, 2, 2, 2, 1, 2, 1, 1, 0, 1, 1, 1, 1, 1, 1},
            {2, 2, 2, 2, 2, 2, 0, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 0, 2, 2, 2, 2, 2, 2},
            {1, 1, 1, 1, 1, 1, 0, 1, 1, 2, 1, 2, 2, 2, 2, 2, 2, 1, 2, 1, 1, 0, 1, 1, 1, 1, 1, 1},
            {2, 2, 2, 2, 2, 1, 0, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 0, 1, 2, 2, 2, 2, 2},
            {2, 2, 2, 2, 2, 1, 0, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 0, 1, 2, 2, 2, 2, 2},
            {2, 2, 2, 2, 2, 1, 0, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 0, 1, 2, 2, 2, 2, 2},
            {1, 1, 1, 1, 1, 1, 0, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 0, 1, 1, 1, 1, 1, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1},
            {1, 4, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 4, 1},
            {1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1},
            {1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1},
            {1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1},
            {1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
            {1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
    };

    this->drawMap();

    pacmanTexture = new PacmanItem();
    scene->addItem(pacmanTexture);
    pacmanTexture->setPos(13 * 20 + 10, 23 * 20);

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

GameWidget::~GameWidget() {
    for (auto &it: this->biscuitTextures)
        delete it;
    delete scene;
    delete view;
    delete newGameBut;
    delete pacmanTexture;
    delete blinky;
    delete pinky;
    delete inky;
    delete clyde;
    delete scoreText;
    delete livesText;
    delete result;
    delete mainLayout;
}
