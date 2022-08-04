#include "playscene.h"
#include <QDebug>
#include <QMenuBar>
#include <QLabel>
#include <QFont>
#include "mypushbutton.h"

PlayScene::PlayScene(int levelNum) {
    QString str = QString("进入了第 %1 关。").arg(levelNum);
    qDebug() << str;
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

    // 返回按钮
    MyPushButton *backBtn = new MyPushButton(":/res/BackButton.png", ":/res/BackButtonSelected.png");
    backBtn->setParent(this);
    backBtn->move(this->width() - backBtn->width(), this->height() - backBtn->height());

    // 点击返回
    connect(backBtn, &MyPushButton::clicked, this, [=](){
        qDebug() << "点击了返回";
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
}

void PlayScene::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/OtherSceneBg.png");
    painter.drawPixmap(0, 0, this->width(), this->height(), pix);

    pix.load(":/res/Title.png");
    painter.drawPixmap((this->width()-pix.width())*0.5, 30, pix.width(), pix.height(), pix);
}
