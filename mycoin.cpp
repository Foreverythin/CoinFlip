#include "mycoin.h"

#include <QDebug>

MyCoin::MyCoin(QString btnImg) {
    QPixmap pix;
    bool ret = pix.load(btnImg);
    if (!ret) {
        qDebug() << "图片加载失败";
    }

    this->setFixedSize(QSize(pix.width(), pix.height()));
    this->setStyleSheet("QPushButton{border:0px;}");
    this->setIcon(pix);
    this->setIconSize(QSize(pix.width(), pix.height()));

    timer1 = new QTimer(this);
    timer2 = new QTimer(this);

    connect(timer1, &QTimer::timeout, this, [=](){
        QPixmap pix;
        QString str = QString(":/res/Coin000%1.png").arg(this->min++);
        pix.load(str);
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(), pix.height()));
        if (this->min > this->max) {
            this->min = 1;
            isAnimation = false;
            timer1->stop();
        }
    });

    connect(timer2, &QTimer::timeout, this, [=](){
        QPixmap pix;
        QString str = QString(":/res/Coin000%1.png").arg(this->max--);
        pix.load(str);
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(), pix.height()));
        if (this->min > this->max) {
            this->max = 8;
            isAnimation = false;
            timer2->stop();
        }
    });
}

void MyCoin::changeFlag() {
    if (this->flag) {
        timer1->start(30);
        isAnimation = true;
        this->flag = false;
    } else {
        timer2->start(30);
        isAnimation = true;
        this->flag = true;
    }
}

void MyCoin::mousePressEvent(QMouseEvent *e) {
    if (this->isAnimation || this->isWin) return;
    else QPushButton::mousePressEvent(e);
}
