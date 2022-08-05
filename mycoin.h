#ifndef MYCOIN_H
#define MYCOIN_H

#include <QPushButton>
#include <QTimer>

class MyCoin : public QPushButton
{
    Q_OBJECT
public:
    MyCoin(QString btnImg); // 参数代表 传入的是金币路径还是银币路径
    int posX;
    int posY;
    bool flag; //金币正反

    void changeFlag();
    QTimer* timer1;
    QTimer* timer2;
    int min = 1;
    int max = 8;

    bool isAnimation = false;

    void mousePressEvent(QMouseEvent *e);

    bool isWin = false;

signals:

};

#endif // MYCOIN_H
