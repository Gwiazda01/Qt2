#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    direction = backward;
    point = new QPoint(16,16);
    point2 = new QPoint(16,24);
    point3 = new QPoint(16,32);
    snake.push_back(point);
    snake.push_back(point2);
    snake.push_back(point3);
    game_state=not_started;
    game_level=1;
    addFruit();
    start=false;
    pause=false;
    score=0;

    srand(time(NULL));
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    if(game_state==not_started)
    {

        painter.setFont(QFont("Times", 35));
        painter.drawText(rect(),Qt::AlignTop,"\t\t\t\t\t\t\t\t\tSNAKE");
        painter.setFont(QFont("Times",30));
        painter.drawText(rect(),Qt::AlignTop,"\n\t\t\t\t\t\t\tChoose level:");
        painter.setPen(Qt::blue);
        painter.setFont(QFont("Times", 30));
        painter.drawText(rect(),Qt::AlignCenter,"\n\nEasy - 1\nMedium - 2\nHard - 3 ");
    }

    if(game_state==started)
    {

    painter.setPen(Qt::black);
    painter.drawRect(8,8,208,208);
    QPen apen;
    apen.setColor(Qt::black);
    apen.setWidth(8);
    switch(game_level)
    {
        case 2:
            a=new QPoint(32,32);
            d=new QPoint(192,192);
            painter.setPen(apen);
            painter.drawPoint(*a);
            painter.drawPoint(*d);
            break;
        case 3:
            b=new QPoint(32,192);
            c=new QPoint(192,32);
            painter.setPen(apen);
            painter.drawPoint(*a);
            painter.drawPoint(*b);
            painter.drawPoint(*c);
            painter.drawPoint(*d);
            break;
        case 4:
            line = new QLine(32,104,88,104);
            painter.setPen(apen);
            painter.drawPoint(*a);
            painter.drawPoint(*b);
            painter.drawPoint(*c);
            painter.drawPoint(*d);
            painter.drawLine(*line);
        break;
        case 5:
           line2 = new QLine(134,104,192,104);
           painter.setPen(apen);
           painter.drawPoint(*a);
           painter.drawPoint(*b);
           painter.drawPoint(*c);
           painter.drawPoint(*d);
           painter.drawLine(*line);
           painter.drawLine(*line2);
        break;

    }
    if(pause)
    {
        painter.drawText(rect(), Qt::AlignBottom,"PRESS SPACE TO START");
        update();
    }
    else
    {
        painter.drawText(rect(), Qt::AlignBottom,"PRESS SPACE TO PAUSE");
        update();
    }
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
     else if(game_state==game_over)
    {

        //delete point;
        //delete point2;
        //delete point3;
        QString result;
        delete fruit;
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

if(!pause)
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
        if((snake[0]->x()==fruit->x()) &&(snake[0]->y()==fruit->y()))
        {
            fruit_exist=false;
            snake.insert(snake.begin(),fruit);
            switch(gm_level)
            {
                case easy:
                    score+=10;
                    break;
                case medium:
                    score+=20;
                    break;
                case hard:
                    score+=30;
                    break;
            }
            levelUp();
            addFruit();
        }
    setPossition();
    snake_pos_x.clear();
    snake_pos_y.clear();
    update();
    if(start)gameOver();
    start=true;


    }
}
//*********************************************************
void MainWindow::keyPressEvent(QKeyEvent *key)
{
    switch(key->key())
    {
        case Qt::Key_W:
            if(snake[1]->y()!= snake[0]->y()-8)
                direction=forward;
            break;
        case Qt::Key_Up:
            if(snake[1]->y()!= snake[0]->y()-8)
                direction=forward;
        break;
        case Qt::Key_S:
            if(snake[1]->y()!= snake[0]->y()+8)
                direction=backward;
            break;
        case Qt::Key_Down:
            if(snake[1]->y()!= snake[0]->y()+8)
                direction=backward;
            break;
        case Qt::Key_A:
            if(snake[1]->x()!= snake[0]->x()+8)
                direction=left;
            break;
        case Qt::Key_Left:
            if(snake[1]->x()!= snake[0]->x()+8)
                direction=left;
            break;
        case Qt::Key_D:
            if(snake[1]->x()!= snake[0]->x()+8)
                direction=right;
            break;
        case Qt::Key_Right:
            if(snake[1]->x()!= snake[0]->x()+8)
                direction=right;
            break;
        case Qt::Key_Space:
            pause= !pause;
            break;
        case Qt::Key_1:
            if(game_state==not_started)
            {
                timer = new QTimer(this);
                connect(timer,SIGNAL(timeout()),this,SLOT(TimerSlot()));
                timer->start(300);
                game_state = started;
                gm_level = easy;
            }
            break;
        case Qt::Key_2:
            if(game_state==not_started)
            {
                timer = new QTimer(this);
                connect(timer,SIGNAL(timeout()),this,SLOT(TimerSlot()));
                timer->start(200);
                game_state = started;
                gm_level = medium;
            }
            break;
        case Qt::Key_3:
            if(game_state==not_started)
            {
                timer = new QTimer(this);
                connect(timer,SIGNAL(timeout()),this,SLOT(TimerSlot()));
                timer->start(100);
                game_state = started;
                gm_level = hard;
            }
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
    x=rand()%198+16;
    y=rand()%198+16;

    for(unsigned i=0; i<snake.size(); ++i)
    {


        switch(game_level)
        {
            case 1:
                while((y%8) || y==snake[i]->y() ) y=rand()%198+16;
                while((x%8) || x==snake[i]->x() ) x=rand()%198+16;
                break;
            case 2:
                while((x==32 && y==32) || (x==192 && y==192) || (x%8) || x==snake[i]->x() || (y%8) || y==snake[i]->y() )
                {
                    y=rand()%198+16;
                    x=rand()%198+16;
                }
                break;
            case 3:
                while((x==32 && y==32) || (x==192 && y==192) || (x==32 && y==192) || (x==192 && y==32) || (x%8) || x==snake[i]->x() || (y%8) || y==snake[i]->y())
                {
                    y=rand()%198+16;
                    x=rand()%198+16;
                }
                break;
            case 4:
                while((x==32 && y==32) || (x==192 && y==192) || (x==32 && y==192) || (x==192 && y==32) || ((x>=32 && x<=88) && y==104) || (x%8) || x==snake[i]->x() || (y%8) || y==snake[i]->y())
                {
                    y=rand()%198+16;
                    x=rand()%198+16;
                }
                break;
            case 5:
                while((x==32 && y==32) || (x==192 && y==192) || (x==32 && y==192) || (x==192 && y==32) || ((x>=32 && x<=88) && y==104) || ((x>=134 && x<=192) && y==104) || (x%8) || x==snake[i]->x() || (y%8) || y==snake[i]->y() )
                {
                    y=rand()%198+16;
                    x=rand()%198+16;
                }
                break;

        }

    }
    fruit = new QPoint(x,y);
}
//******************************************************
void MainWindow::gameOver()
{
    for(unsigned i=1; i<snake.size(); ++i)
    {
        if((snake[0]->x()== snake[i]->x() && snake[0]->y() == snake[i]->y()) || (snake[0]->x()<10 || snake[0]->x()>215 ||snake[0]->y()<10 || snake[0]->y()>215 ))
            game_state=game_over;
    }

        switch(game_level)
        {
            case 2:
                if((snake[0]->x()==32 && snake[0]->y()==32) || (snake[0]->x()==192 && snake[0]->y()==192))
                game_state=game_over;
                break;
            case 3:
                if((snake[0]->x()==32 && snake[0]->y()==32) || (snake[0]->x()==192 && snake[0]->y()==192) || (snake[0]->x()==32 && snake[0]->y()==192) || (snake[0]->x()==192 && snake[0]->y()==32))
                game_state=game_over;
                break;
            case 4:
                if((snake[0]->x()==32 && snake[0]->y()==32) || (snake[0]->x()==192 && snake[0]->y()==192) || (snake[0]->x()==32 && snake[0]->y()==192) || (snake[0]->x()==192 && snake[0]->y()==32) || ((snake[0]->x()>=32 && snake[0]->x()<=88) && snake[0]->y()==104))
                    game_state=game_over;
                break;
            case 5:
                if((snake[0]->x()==32 && snake[0]->y()==32) || (snake[0]->x()==192 && snake[0]->y()==192) || (snake[0]->x()==32 && snake[0]->y()==192) || (snake[0]->x()==192 && snake[0]->y()==32) || ((snake[0]->x()>=32 && snake[0]->x()<=88) && snake[0]->y()==104) || ((snake[0]->x()>=134 && snake[0]->x()<=192) && snake[0]->y()==104))
                    game_state=game_over;
                break;

        }
}

//******************************************************
void MainWindow::levelUp()
{
    switch(gm_level)
    {
        case easy:
            if(!(score%50) && game_level<5)
                ++game_level;
            break;
        case medium:
            if(!(score%100) && game_level<5)
                ++game_level;
            break;
        case hard:
            if(!(score%150) && game_level<5)
                ++game_level;
            break;

    }
}
