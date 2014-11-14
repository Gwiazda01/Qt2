#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    direction = backward;
    timer = new QTimer(this);
    point = new QPoint(14,14);
    point2 = new QPoint(14,22);
    point3 = new QPoint(14,30);
    snake.push_back(point);
    snake.push_back(point2);
    snake.push_back(point3);
    addFruit();
    game=true;
    start=false;
    score=0;
    connect(timer,SIGNAL(timeout()),this,SLOT(TimerSlot()));
    timer->start(200);
    srand(time(NULL));
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    if(game)
    {

    painter.setPen(Qt::black);
    painter.drawRect(10,10,205,205);
    QPen pen(Qt::blue);
    pen.setWidth(8);
    painter.setPen(pen);

        for(unsigned i = 0; i<snake.size(); ++i)
            painter.drawPoint(*snake[i]);
        if(fruit_exist)
        {
            pen.setColor(Qt::red);
            pen.setWidth(8);
            painter.setPen(pen);
            painter.drawPoint(*fruit);
        }
     }
     else
    {
        painter.setPen(Qt::black);
        painter.setFont(QFont("Times", 45));
        painter.drawText(rect(),Qt::AlignCenter, "GAME OVER!!");
        painter.setFont(QFont("Times", 25));
        result = "Score: "+QString::number(score);
        painter.drawText(rect(), Qt::AlignBottom,result);
    }

}

//********************************************************
void MainWindow::TimerSlot()
{
    for(unsigned i=0; i<snake.size(); ++i)
    {
        snake_pos_x.push_back(snake[i]->x());
        snake_pos_y.push_back(snake[i]->y());
    }

    switch(direction)
    {
        case forward:
            snake[0]->setY(snake[0]->y()-8);

            break;
        case backward:
            snake[0]->setY(snake[0]->y()+8);

            break;
        case left:
            snake[0]->setX(snake[0]->x()-8);

            break;
        case right:
            snake[0]->setX(snake[0]->x()+8);

            break;
    }
    if(fruit_exist)
        if((snake[0]->x()<=fruit->x()+4 && snake[0]->x()>=fruit->x()-4)&&(snake[0]->y()<=fruit->y()+4 && snake[0]->y()>=fruit->y()-4))
        {
            fruit_exist=false;
            snake.insert(snake.begin(),fruit);
            score+=10;
            addFruit();
        }
    setPossition();
    snake_pos_x.clear();
    snake_pos_y.clear();
    update();
    if(start)gameOver();
    start=true;


    }
//*********************************************************
void MainWindow::keyPressEvent(QKeyEvent *key)
{
    switch(key->key())
    {
        case Qt::Key_W:
            if(direction!=backward)
                direction=forward;
            break;
        case Qt::Key_S:
            if(direction!=forward)
                direction=backward;
            break;
        case Qt::Key_A:
            if(direction!=right)
                direction=left;
            break;
        case Qt::Key_D:
            if(direction!=left)
                direction=right;
            break;

    }
}
//****************************************************
void MainWindow::setPossition()
{
    for(unsigned i=1; i<snake.size(); ++i)
    {
        snake[i]->setX(snake_pos_x[i-1]);
        snake[i]->setY(snake_pos_y[i-1]);
    }
}
//*****************************************************
void MainWindow::addFruit()
{
    fruit_exist=true;
    int x,y;
    x=rand()%201;
    y=rand()%201;
    while(!(x%8)) x=rand()%201;
    while(!(x%8)) y=rand()%201;
    fruit = new QPoint(x+12,y+12);
}
//*****************************************************
void MainWindow::gameOver()
{
    for(unsigned i=1; i<snake.size(); ++i)
    {
        if((snake[0]->x()== snake[i]->x() && snake[0]->y() == snake[i]->y()) || (snake[0]->x()<10 || snake[0]->x()>215 ||snake[0]->y()<10 || snake[0]->y()>215 ))
            game=false;
    }
}
//******************************************************

