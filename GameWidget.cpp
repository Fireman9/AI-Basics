#include "GameWidget.h"

GameWidget::GameWidget(QWidget *parent) :
        QWidget(parent) {
    this->biscuit = 0;
    this->wall = 1;
    this->empty = 2;
    this->block = 3;
    this->pill = 4;
    this->score = 0;
    scoreText = new QLabel("Score: " + QString::number(score));

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

    this->drawMap();

    pacmanTexture = new PacmanItem();
    scene->addItem(pacmanTexture);
    pacmanTexture->setPos(13 * 20 + 10, 23 * 20);

    mainLayout = new QVBoxLayout();
    mainLayout->addWidget(scoreText);
    mainLayout->addWidget(view);

    this->setLayout(mainLayout);

    timer.start(50);
    connect(&timer, &QTimer::timeout, this, &GameWidget::clock);
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
    QPoint pos = pacmanTexture->move(map);
    if (-1 < pos.x() && pos.x() < 28 && map[pos.y()][pos.x()] == 0) {
        map[pos.y()][pos.x()] = 2;
        score++;
        scoreText->setText("Score: " + QString::number(score));
        for (int i = 0; i < biscuitTextures.size(); i++) {
            if ((int) (biscuitTextures[i]->pos().x() / 20) == pos.x() &&
                (int) (biscuitTextures[i]->pos().y() / 20) == pos.y()) {
                scene->removeItem(biscuitTextures[i]);
                biscuitTextures.erase(biscuitTextures.begin() + i);
                break;
            }
        }
    }
    timer.start(50);
}


GameWidget::~GameWidget() {
    for (auto &it: this->biscuitTextures)
        delete it;
    delete scene;
    delete view;
    delete pacmanTexture;
    delete scoreText;
    delete mainLayout;
}
