#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>

#include <QBasicTimer>
#include <QTimerEvent>

#include "lifegame.h"


class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    LifeGame *map;
    QPushButton *startButton;
    QPushButton *pauseButton;
    QPushButton *resetButton;
    QPushButton *quitButton;
    QLabel *genLabel;
    QLabel *genCountLabel;
    QBasicTimer timer;

    QHBoxLayout *buttonLayout;
    QVBoxLayout *mainLayout;

    bool ispaused;

private slots:
    void start();
    void pause();
    void reset();

protected:
    void timerEvent(QTimerEvent *event);

};

#endif // MAINWINDOW_H
