#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    ispaused = false;
    map = new LifeGame;
    startButton = new QPushButton("Start");
    pauseButton = new QPushButton("Pause");
    resetButton = new QPushButton("Reset");
    quitButton = new QPushButton("Quit");
    buttonLayout = new QHBoxLayout;
    genLabel = new QLabel("<h2>Generations:</h2>");
    genCountLabel = new QLabel("<h2>"+QString::number(map->gencount(),10)+"</h2>");
    mainLayout = new QVBoxLayout;

    buttonLayout->addWidget(startButton);
    buttonLayout->addWidget(pauseButton);
    buttonLayout->addWidget(resetButton);
    buttonLayout->addWidget(quitButton);
    buttonLayout->addWidget(genLabel);
    buttonLayout->addWidget(genCountLabel);

    connect(startButton,SIGNAL(clicked()),this,SLOT(start()));
    connect(pauseButton,SIGNAL(clicked()),this,SLOT(pause()));
    connect(resetButton,SIGNAL(clicked()),this,SLOT(reset()));
    connect(quitButton,SIGNAL(clicked()),this,SLOT(close()));

    mainLayout->addWidget(map);
    mainLayout->addLayout(buttonLayout);

    setLayout(mainLayout);
    setWindowTitle("GAME OF LIFE");
}

void MainWindow::start()
{
    map->setStartState(true);
    startButton->setEnabled(false);
    timer.start(1000,this);
}

void MainWindow::pause()
{
    if(!ispaused){
        timer.stop();
        pauseButton->setText("Continue");
    } else {
        timer.start(1000,this);
        pauseButton->setText("Pause");
    }
    ispaused = !ispaused;
}

void MainWindow::reset()
{
    timer.stop();
    genCountLabel->setText("<h2>0</h2>");
    startButton->setEnabled(true);
    map->setStartState(false);
    map->initmaps();
    map->refreshPixmap();
    map->resetGenCount();
}

void MainWindow::timerEvent(QTimerEvent *event)
{
    if(event->timerId() == timer.timerId()){
        map->generation();
        genCountLabel->setText("<h2>"+QString::number(map->gencount(),10)+"</h2>");
    }
}


MainWindow::~MainWindow()
{

}
