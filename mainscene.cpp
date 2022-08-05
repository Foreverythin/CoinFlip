#include "mainscene.h"
#include "ui_mainscene.h"
#include <QPainter>
#include <QDebug>
#include <QSound>
#include <QTimer>
#include <mypushbutton.h>


MainScene::MainScene(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainScene)
{   
    ui->setupUi(this);
    ui->menubar->setNativeMenuBar(false);
    setFixedSize(320, 588); // set the window size fixed
    setWindowIcon(QIcon(":/res/Coin0001.ico")); // set the icon
    setWindowTitle("CoinFlip"); // set the title of the window
    connect(ui->actionQuit, &QAction::triggered, this, [=](){
        this->close();
    });
    // 开始按钮
    MyPushButton * startBtn = new MyPushButton(":/res/MenuSceneStartButton.png");
    startBtn->setParent(this);
    startBtn->move(this->width()*0.5-startBtn->width()*0.5, this->height()*0.7);

    // 开始的音效
    QSound * startSound = new QSound(":/res/TapButtonSound.wav", this);

    chooseScene = new ChooseLevelScene;

    // 监听点击返回按钮发送的信号
    connect(chooseScene, &ChooseLevelScene::chooseSceneBack, this, [=](){
        QTimer::singleShot(200, this, [=](){
            this->setGeometry(chooseScene->geometry());
            chooseScene->hide();
            this->show();
        });
    });

    connect(startBtn, &MyPushButton::clicked, this, [=](){
        startSound->play();
        // 弹起的特效
        startBtn->zoom1();
        startBtn->zoom2();
        QTimer::singleShot(400, this, [=](){
            this->hide();
            chooseScene->setGeometry(this->geometry());
            chooseScene->show();
        });
    });
}

MainScene::~MainScene()
{
    delete ui;
}

void MainScene::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0, 0, this->width(), this->height(), pix);

    pix.load(":/res/Title.png");
    pix = pix.scaled(pix.width()*0.5, pix.height()*0.5);
    painter.drawPixmap(10, 30, pix.width(), pix.height(), pix);
}

