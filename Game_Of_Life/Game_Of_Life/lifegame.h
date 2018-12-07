#ifndef LIFEGAME_H
#define LIFEGAME_H

#include <QtGui/QWidget>
#include <QMouseEvent>
#include <QPainter>
#include <QBasicTimer>
#include <QTimerEvent>

#define ROW 36
#define COL 36
#define WIDTH 17

class LifeGame : public QWidget
{
    Q_OBJECT

public:
    LifeGame(QWidget *parent = 0);
    ~LifeGame();

protected:
    void paintEvent(QPaintEvent *);
    void drawGrid(QPainter *painter);
    void mousePressEvent(QMouseEvent *event);
    //void timerEvent(QTimerEvent *event);

private:
    int x;
    int y;
    int generations;
    QPixmap pixmap;
    QPixmap cellpic;
    QBasicTimer timer;
    int lifemap[COL][ROW];
    int tmplifemap[COL][ROW];
    bool ispause;
    bool isstarted;


    void drawCell(QPainter *painter);

    void copyToTmp();

    void check(int i, int j);


public:
    void initmaps();
    int gencount();
    void setStartState(bool isstart);
    void refreshPixmap();
    void generation();
    void resetGenCount();

private slots:
    //void start();
   // void pause();
    //void reset();
};

#endif // LIFEGAME_H
