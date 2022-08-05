#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QMainWindow>
#include <QPainter>
#include "mycoin.h"

class PlayScene : public QMainWindow
{
    Q_OBJECT
public:
    PlayScene(int levelNum);

    int levelIndex;

    int gameArray[4][4];

    MyCoin * coinBtn[4][4];

    bool isWin;

void paintEvent(QPaintEvent *);

signals:
    void chooseSceneBack();
};

#endif // PLAYSCENE_H
