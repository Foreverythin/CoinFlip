#include "mypushbutton.h"
#include <QDebug>
#include <QPropertyAnimation>

MyPushButton::MyPushButton(QString normalImg, QString pressImg)
{
    this->normalImgPath = normalImg;
    this->pressImgPath = pressImg;

    QPixmap pix;
    bool ret = pix.load(normalImg);
    if (!ret) {
        qDebug() << "图片加载失败";
        return;
    }
    this->setFixedSize(pix.width(), pix.height());
    this->setStyleSheet("QPushButton{border:0px;}");
    this->setIcon(pix);
    this->setIconSize(pix.size());
}

void MyPushButton::zoom1() {
    QPropertyAnimation * animation1 = new QPropertyAnimation(this, "geometry");
    animation1->setDuration(200);
    animation1->setStartValue(QRect(this->x(), this->y(), this->width(), this->height()));
    animation1->setEndValue(QRect(this->x(), this->y()+10, this->width(), this->height()));
    animation1->setEasingCurve(QEasingCurve::OutBounce);
    animation1->start();
}

void MyPushButton::zoom2() {
    QPropertyAnimation * animation2 = new QPropertyAnimation(this, "geometry");
    animation2->setDuration(200);
    animation2->setStartValue(QRect(this->x(), this->y()+10, this->width(), this->height()));
    animation2->setEndValue(QRect(this->x(), this->y(), this->width(), this->height()));
    animation2->setEasingCurve(QEasingCurve::OutBounce);
    animation2->start();
}

void MyPushButton::mousePressEvent(QMouseEvent *e) {
    if (this->pressImgPath != "") {
        QPixmap pix;
        bool ret = pix.load(this->pressImgPath);
        if (!ret) {
            qDebug() << "图片加载失败";
            return;
        }
        this->setFixedSize(pix.width(), pix.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pix);
        this->setIconSize(pix.size());
    }
    return QPushButton::mousePressEvent(e);
}

void MyPushButton::mouseReleaseEvent(QMouseEvent *e) {
    if (this->pressImgPath != "") {
        QPixmap pix;
        bool ret = pix.load(this->normalImgPath);
        if (!ret) {
            qDebug() << "图片加载失败";
            return;
        }
        this->setFixedSize(pix.width(), pix.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pix);
        this->setIconSize(pix.size());
    }
    return QPushButton::mouseReleaseEvent(e);
}

