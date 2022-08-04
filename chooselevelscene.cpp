#include "chooselevelscene.h"
#include <QMenuBar>
#include <QPainter>
#include "mypushbutton.h"
#include "playscene.h"
#include <QDebug>
#include <QLabel>
#include <QTimer>

ChooseLevelScene::ChooseLevelScene(QWidget *parent) : QMainWindow(parent)
{
    //配置选择关卡场景
    this->setFixedSize(320, 588);
    this->setWindowIcon(QPixmap(":/res/coin0001.png"));

    this->setWindowTitle("选择关卡场景");

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

    // 创建关卡按钮
    for (int i = 0; i < 20; i++) {
        MyPushButton *menuBtn = new MyPushButton(":/res/LevelIcon.png");
        menuBtn->setParent(this);
        menuBtn->move(i%4*70+25, i/4*80+130);

        QLabel *label = new QLabel;
        label->setParent(this);
        label->setFixedSize(QSize(menuBtn->width(), menuBtn->height()));
        label->setText((QString::number(i+1)));
        label->move(i%4*70+25, i/4*80+130);
        label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        // 设置让鼠标进行穿透
        label->setAttribute(Qt::WA_TransparentForMouseEvents);

        connect(menuBtn, &MyPushButton::clicked, this, [=](){
            // 进入游戏场景
            this->hide();
            play = new PlayScene(i+1);
            play->show();
            connect(play, &PlayScene::chooseSceneBack, this, [=](){
                QTimer::singleShot(200, this, [=](){
                    play->close();
                    delete play;
                    play = nullptr;
                    this->show();
                });
            });
        });
    }

}

void ChooseLevelScene::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/OtherSceneBg.png");
    painter.drawPixmap(0, 0, this->width(), this->height(), pix);

    pix.load(":/res/Title.png");
    painter.drawPixmap((this->width()-pix.width())*0.5, 30, pix.width(), pix.height(), pix);
}
