#ifndef CHOOSELEVELSCENE_H
#define CHOOSELEVELSCENE_H

#include <QMainWindow>
#include "playscene.h"

class ChooseLevelScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit ChooseLevelScene(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent*);

    PlayScene *play = nullptr;

signals:
    // 自定义信号告诉主场景点击了返回
    void chooseSceneBack();

};

#endif // CHOOSELEVELSCENE_H
