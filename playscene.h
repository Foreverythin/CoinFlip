#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QMainWindow>
#include <QPainter>

class PlayScene : public QMainWindow
{
    Q_OBJECT
public:
    PlayScene(int levelNum);

    int levelIndex;

void paintEvent(QPaintEvent *);

signals:
    void chooseSceneBack();
};

#endif // PLAYSCENE_H
