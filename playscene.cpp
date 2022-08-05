#include "playscene.h"
#include <QDebug>
#include <QMenuBar>
#include <QLabel>
#include <QSound>
#include <QFont>
#include <QPropertyAnimation>
#include "mypushbutton.h"
#include "mycoin.h"
#include "dataconfig.h"

PlayScene::PlayScene(int levelNum) {
    QString str = QString("进入了第 %1 关。").arg(levelNum);
    this->levelIndex = levelNum;

    this->setFixedSize(QSize(320, 588));
    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));
    this->setWindowTitle("翻金币场景");

    //创建菜单栏
    QMenuBar * bar = menuBar();
    this->setMenuBar(bar);
    bar->setNativeMenuBar(false);
    QMenu * startMenu = bar->addMenu("Start");
    QAction * quitAction = startMenu->addAction("Quit");
    connect(quitAction, &QAction::triggered, this, [=](){
        this->close();
    });

    // 返回音效
    QSound * backSound = new QSound(":/res/BackButtonSound.wav", this);

    // 胜利音效
    QSound * winSound = new QSound(":/res/LevelWinSound.wav", this);

    // 金币翻转音效
    QSound * coinflipSound = new QSound(":/res/ConFlipSound.wav", this);

    // 返回按钮
    MyPushButton *backBtn = new MyPushButton(":/res/BackButton.png", ":/res/BackButtonSelected.png");
    backBtn->setParent(this);
    backBtn->move(this->width() - backBtn->width(), this->height() - backBtn->height());

    // 点击返回
    connect(backBtn, &MyPushButton::clicked, this, [=](){
        backSound->play();
        emit this->chooseSceneBack();
    });

    // 显示当前关卡
    QLabel *label = new QLabel;
    QFont font;
    font.setFamily("华文新魏");
    font.setPointSize(23);
    QString levelStr = QString("Level: %1").arg(this->levelIndex);
    label->setParent(this);
    label->setFont(font);
    label->setText(levelStr);
    label->setGeometry(QRect(30, this->height()-70, 120, 50));

    dataConfig config;
    // 初始化每个关卡的二维数组
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            this->gameArray[i][j] = config.mData[this->levelIndex][i][j];
        }
    }

    QLabel* winLabel = new QLabel(this);
    QPixmap tmpPix;
    tmpPix.load(":/res/LevelCompletedDialogBg.png");
    winLabel->setPixmap(tmpPix);
    winLabel->setGeometry(0, 0, tmpPix.width(), tmpPix.height());
    winLabel->move((this->width()-tmpPix.width())*0.5, -tmpPix.height());


    // 显示金币背景图案
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            // 绘制背景图片
            QPixmap pix = QPixmap(":/res/BoardNode.png");
            QLabel* label = new QLabel;
            label->setParent(this);
            label->setGeometry(0, 0, pix.width(), pix.height());
            label->setPixmap(pix);
            label->move(57 + i*50,200+j*50);

            if (this->gameArray[i][j] == 1) {
                str = ":/res/Coin0001.png";
            } else {
                str = ":/res/Coin0008.png";
            }

            // 创建金币
            MyCoin * coin = new MyCoin(str);
            coin->setParent(this);
            coin->move(59 + i*50,204+j*50);

            coin->posX = i;
            coin->posY = j;
            coin->flag = this->gameArray[i][j]==1?true:false;

            this->coinBtn[i][j] = coin;

            // 点击金币 翻转
            connect(coin, &QPushButton::clicked, this, [=](){
                coinflipSound->play();
                coin->changeFlag();
                this->gameArray[i][j] = this->gameArray[i][j] == 0 ? 1 : 0;

                QTimer::singleShot(300, this, [=](){
                    // 翻转周围金币
                    if (coin->posX + 1 <= 3) {
                        coinBtn[coin->posX+1][coin->posY]->changeFlag();
                        this->gameArray[coin->posX+1][coin->posY] = this->gameArray[coin->posX+1][coin->posY] == 0 ? 1 : 0;
                    }
                    if (coin->posX - 1 >= 0) {
                        coinBtn[coin->posX-1][coin->posY]->changeFlag();
                        this->gameArray[coin->posX-1][coin->posY] = this->gameArray[coin->posX-1][coin->posY] == 0 ? 1 : 0;
                    }
                    if (coin->posY + 1 <= 3) {
                        coinBtn[coin->posX][coin->posY+1]->changeFlag();
                        this->gameArray[coin->posX][coin->posY+1] = this->gameArray[coin->posX][coin->posY+1] == 0 ? 1 : 0;
                    }
                    if (coin->posY - 1 >= 0) {
                        coinBtn[coin->posX][coin->posY-1]->changeFlag();
                        this->gameArray[coin->posX][coin->posY-1] = this->gameArray[coin->posX][coin->posY-1] == 0 ? 1 : 0;
                    }

                    this->isWin = true;
                    for (int i = 0; i < 4; i++) {
                        for (int j = 0; j < 4; j++) {
                            if (coinBtn[i][j]->flag == false) {
                                this->isWin = false;
                                break;
                            }
                        }
                    }
                    if (this->isWin == true) {
                        for (int i = 0; i < 4; i++) {
                            for (int j = 0; j < 4; j++) {
                                coinBtn[i][j]->isWin = true;
                            }
                        }
                        winSound->play();

                        // 将胜利图片移动下来
                        QPropertyAnimation *animation = new QPropertyAnimation(winLabel, "geometry");
                        animation->setParent(this);
                        animation->setDuration(1000);
                        animation->setStartValue(QRect(winLabel->x(), winLabel->y(), winLabel->width(), winLabel->height()));
                        animation->setEndValue(QRect(winLabel->x(), winLabel->y()+124, winLabel->width(), winLabel->height()));
                        animation->setEasingCurve(QEasingCurve::OutBounce);
                        animation->start();
                    }
                });
            });
        }
    }
}

void PlayScene::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/OtherSceneBg.png");
    painter.drawPixmap(0, 0, this->width(), this->height(), pix);

    pix.load(":/res/Title.png");
    painter.drawPixmap((this->width()-pix.width())*0.5, 30, pix.width(), pix.height(), pix);
}
