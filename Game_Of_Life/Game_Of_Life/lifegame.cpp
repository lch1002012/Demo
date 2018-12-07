#include "lifegame.h"

LifeGame::LifeGame(QWidget *parent)
    : QWidget(parent)
{
    generations = 0;
    isstarted = false;
    ispause = false;
    initmaps();
    setFixedSize((COL+2) * WIDTH,(ROW +2) * WIDTH);
}

void LifeGame::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(0,0,pixmap);
    drawGrid(&painter);
}

void LifeGame::mousePressEvent(QMouseEvent *event)
{
    if(isstarted){
        event->ignore();
        return;
    }
    x = event->x() / WIDTH;
    y = event->y() / WIDTH;
    if(x >=1 && x <= COL && y >= 1 && y <= ROW){
        if(lifemap[x - 1][y - 1] == 1) {
            lifemap[x - 1][y - 1] = 0;
        } else {
            lifemap[x - 1][y - 1] = 1;
        }
    }
    refreshPixmap();
}

void LifeGame::drawGrid(QPainter *painter)
{
    for(int i = 1;i <= ROW + 1;i ++)
        painter->drawLine(WIDTH,i * WIDTH,(COL + 1) * WIDTH,i * WIDTH);
    for(int j = 1;j <= COL + 1;j ++)
        painter->drawLine(j * WIDTH,WIDTH,j * WIDTH,(ROW + 1) *WIDTH);
}

void LifeGame::drawCell(QPainter *painter)
{
    for(int a = 0; a <= COL - 1;a ++){
        for(int b = 0; b <= ROW - 1; b++){
            if(lifemap[a][b])
                painter->drawPixmap((a+1) * WIDTH, (b+1) * WIDTH, WIDTH, WIDTH,cellpic);
        }
    }
}

void LifeGame::refreshPixmap()
{
    pixmap = QPixmap(size());
    pixmap.fill(this,0,0);
    QPainter painter(&pixmap);
    cellpic = QPixmap(":/cell.gif");
    drawCell(&painter);
    update();
}


void LifeGame::initmaps()
{
    for(int j = 0; j <= COL - 1;j ++){
        for(int k = 0; k <= ROW - 1; k ++){
            lifemap[j][k] = 0;
            tmplifemap[j][k] = 0;
        }
    }
}

void LifeGame::copyToTmp()
{
    for(int j = 0; j <= COL-1;j ++){
        for(int k = 0; k <= ROW-1; k ++){
            tmplifemap[j][k] = lifemap[j][k];
        }
    }
}


void LifeGame::generation()
{
    copyToTmp();
    for(int i= 0;i<=COL - 1;i++){
        for(int j = 0;j<=ROW - 1;j++){
            lifemap[i][j]=0;
            check(i,j);
        }
    }
    generations++;
    refreshPixmap();
}

void LifeGame::check(int i, int j)
{
    int count = 0;
    int up = j - 1;
    int down = j + 1;
    int left = i - 1;
    int right = i + 1;
    int k = 0;
    if(up < 0){
        up = COL - 1;
    }
    if(down > COL - 1){
        down = 0;
    }
    if(left < 0){
        left = ROW - 1;
    }
    if(right > ROW - 1){
        right = 0;
    }
    for(int x = 1;x <= 3;x ++){
    switch (x)
    {
    case 1:
        k=left;
        break;
    case 2:
        k=i;
        break;
    case 3:
        k=right;
        break;
    }
    if(tmplifemap[k][up])
        count ++;
    if(tmplifemap[k][down])
        count ++;
    }
    if(tmplifemap[left][j])
        count ++;
    if(tmplifemap[right][j])
        count ++;
    switch (count)
    {
    case 2:
        lifemap[i][j]=tmplifemap[i][j];
        break;
    case 3:
        lifemap[i][j] = 1;
        break;
        default:
        lifemap[i][j] = 0;
    }
}

/*
void LifeGame::start()
{
    isstarted = !isstarted;
    if(isstarted)
        generation();
        timer.start(1000,this);
}

void LifeGame::pause()
{
    if(ispause){
        timer.start(1000,this);
    }
    else {
        timer.stop();
    }
    ispause = !ispause;
}

void LifeGame::reset()
{
    isstarted=false;
    timer.stop();
    initmaps();
    refreshPixmap();
}

void LifeGame::timerEvent(QTimerEvent *event)
{
    if(event->timerId() == timer.timerId())
    {
        generation();
    }
}
*/

int LifeGame::gencount()
{
    return generations;
}

void LifeGame::setStartState(bool isstart)
{
    isstarted = isstart;
}

void LifeGame::resetGenCount()
{
    generations = 0;
}

LifeGame::~LifeGame()
{

}

