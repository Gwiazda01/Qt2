#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    game_state=not_started;
    counter=0;
    e_button = new QPushButton("EASY", this);
    e_button->setGeometry(QRect(QPoint(100, 100),
                                    QSize(200, 50)));
    connect(e_button, SIGNAL(released()), this, SLOT(easyButton()));

    m_button = new QPushButton("MEDIUM", this);
    m_button->setGeometry(QRect(QPoint(100, 150),
                                    QSize(200, 50)));
    connect(m_button, SIGNAL(released()), this, SLOT(mediumButton()));

    h_button = new QPushButton("HARD", this);
    h_button->setGeometry(QRect(QPoint(100, 200),
                                    QSize(200, 50)));
    connect(h_button, SIGNAL(released()), this, SLOT(hardButton()));

    score=0;
    fruits_to_level_up=5;
    fruit = new QPoint();
    a=new QPoint(32,32);
    d=new QPoint(192,192);
    b=new QPoint(32,192);
    c=new QPoint(192,32);
    line = new QLine(32,104,88,104);
    line2 = new QLine(134,104,192,104);
    direction = backward;
    point = new QPoint();
    point2 = new QPoint();
    point3 = new QPoint();
    point -> setX(120);
    point -> setY(64);
    point2 -> setX(120);
    point2 -> setY(56);
    point3 -> setX(120);
    point3 -> setY(48);
    snake.push_back(point);
    snake.push_back(point2);
    snake.push_back(point3);
    game_level=1;
    addFruit();
    pause=false;

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

}

if(game_state==started)
{
    painter.setPen(Qt::black);
    painter.drawRect(8,8,208,208);
    QPen apen;
    apen.setColor(Qt::black);
    apen.setWidth(8);
    painter.setFont(QFont("Arial Black", 20));
    painter.drawText(rect(),Qt::AlignRight, "\nLevel: "+QString::number(game_level)+"     ");
    painter.setFont(QFont("Times", 18));
    painter.drawText(rect(),Qt::AlignRight, "\n\n\n\nNext level in:    ");
    painter.setFont(QFont("Arial", 15));
    painter.drawText(rect(),Qt::AlignRight, "\n\n\n\n\n\n"+QString::number(fruits_to_level_up)+"              ");
    painter.setFont(QFont("Arial Black", 12));
    painter.drawText(rect(),Qt::AlignRight, "\n\n\n\n\n\n\n\n\nScore:"+QString::number(score)+"            ");


    switch(game_level)
    {
        case 2:
            //a=new QPoint(32,32);
            //d=new QPoint(192,192);
            painter.setPen(apen);
            painter.drawPoint(*a);
            painter.drawPoint(*d);
            break;
        case 3:
            //b=new QPoint(32,192);
            //c=new QPoint(192,32);
            painter.setPen(apen);
            painter.drawPoint(*a);
            painter.drawPoint(*b);
            painter.drawPoint(*c);
            painter.drawPoint(*d);
            break;
        case 4:
            //line = new QLine(32,104,88,104);
            painter.setPen(apen);
            painter.drawPoint(*a);
            painter.drawPoint(*b);
            painter.drawPoint(*c);
            painter.drawPoint(*d);
            painter.drawLine(*line);
        break;
        case 5:
           //line2 = new QLine(134,104,192,104);
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
        painter.setFont(QFont("Times", 10));
        painter.drawText(rect(), Qt::AlignBottom,"PRESS SPACE TO START");
        update();
    }
    else
    {
        painter.setFont(QFont("Times", 10));
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

    for(unsigned i=0; i<snake.size()-3; i++)
    {
        delete snake[i];
        snake[i]= 0;
    }
    snake.clear();
    timer->stop();
    delete timer;
    delete point;
    delete point2;
    delete point3;
    delete a;
    delete d;
    delete b;
    delete c;
    delete line;
    delete line2;
    delete fruit;
        QString result;
        painter.setPen(Qt::black);
        painter.setFont(QFont("Times", 45));
        painter.drawText(rect(),Qt::AlignCenter, "GAME OVER!!");
        painter.setFont(QFont("Times", 25));
        result = "Score: "+QString::number(score);
        painter.drawText(rect(), Qt::AlignBottom,result);
}
else if(game_state==lvl_up)
{
    painter.setPen(Qt::black);
    painter.setFont(QFont("Times", 40));
    painter.drawText(rect(),Qt::AlignCenter,"Level UP !!");
    update();
}

}

//********************************************************
void MainWindow::TimerSlot()
{

if((!pause) && (game_state!=lvl_up))
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
            if(game_level!=5)--fruits_to_level_up;
            fruit_exist=false;
            snake.insert(snake.begin(),new QPoint(fruit->x(),fruit->y()));

            switch(gm_level)
            {
                case easy:
                    score+=points_for_fruit;
                    break;
                case medium:
                    score+=points_for_fruit;
                    break;
                case hard:
                    score+=points_for_fruit;
                    break;
            }
            levelUp();
            addFruit();
        }

    if(game_state!=lvl_up)setPossition();
    snake_pos_x.clear();
    snake_pos_y.clear();
    update();
    gameOver();



    }
else
    {
        if(game_state==lvl_up)
        {
            ++counter;
            switch(gm_level)
            {
                case easy:
                    if(counter==3)
                    {
                        game_state=started;
                        counter=0;
                    }
                 break;

                case medium:
                    if(counter==5)
                    {
                        game_state=started;
                        counter=0;
                    }
                break;
                case hard:
                    if(counter==10)
                    {
                        game_state=started;
                        counter=0;
                    }
                break;

            }
        }

    }
}
//*********************************************************
void MainWindow::keyPressEvent(QKeyEvent *key)
{
if(game_state!=lvl_up && game_state!= game_over)
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
            if(snake[1]->x()!= snake[0]->x()-8)
                direction=left;
            break;
        case Qt::Key_Left:
            if(snake[1]->x()!= snake[0]->x()-8)
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
    while( y%8 ) y=rand()%198+16;
    while( x%8 ) x=rand()%198+16;

        switch(game_level)
        {
            case 1:
                while(isSnakeBody(x,y))
                {
                    while( y%8 ) y=rand()%198+16;
                    while( x%8 ) x=rand()%198+16;
                }
                break;
            case 2:
                while((x==32 && y==32) || (x==192 && y==192) || (x%8) || (y%8) || isSnakeBody(x,y) )
                {
                    y=rand()%198+16;
                    x=rand()%198+16;
                }
                break;
            case 3:
                while((x==32 && y==32) || (x==192 && y==192) || (x==32 && y==192) || (x==192 && y==32) || (x%8) || (y%8) || isSnakeBody(x,y))
                {
                    y=rand()%198+16;
                    x=rand()%198+16;
                }
                break;
            case 4:
                while((x==32 && y==32) || (x==192 && y==192) || (x==32 && y==192) || (x==192 && y==32) || ((x>=32 && x<=88) && y==104) || (x%8) || (y%8) || isSnakeBody(x,y))
                {
                    y=rand()%198+16;
                    x=rand()%198+16;
                }
                break;
            case 5:
                while((x==32 && y==32) || (x==192 && y==192) || (x==32 && y==192) || (x==192 && y==32) || ((x>=32 && x<=88) && y==104) || ((x>=134 && x<=192) && y==104) || (x%8) || (y%8) || isSnakeBody(x,y) )
                {
                    y=rand()%198+16;
                    x=rand()%198+16;
                }
                break;

        }
    fruit -> setX(x);
    fruit -> setY(y);
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

            switch(game_level)
            {
                case 1:
                if(!(fruits_to_level_up))
                {
                    ++game_level;
                    fruits_to_level_up=6;
                    setSnakeStartPos();
                }
                break;
                case 2:
                if(!(fruits_to_level_up))
                {
                    ++game_level;
                    fruits_to_level_up=7;
                    setSnakeStartPos();
                }
                break;
                case 3:
                if(!(fruits_to_level_up))
                {
                    ++game_level;
                    fruits_to_level_up=8;
                    setSnakeStartPos();
                }
                break;
                case 4:
                if(!(fruits_to_level_up))
                {
                    ++game_level;
                    setSnakeStartPos();
                }
                break;
          }
}
//************************************************************
bool MainWindow::isSnakeBody(int x, int y)
{
    for(unsigned i=0; i<snake.size(); ++i)
    {
        if(snake[i]->x() == x && snake[i]->y() == y)
            return true;
    }
    return false;
}
//************************************************************
void MainWindow::setSnakeStartPos()
{
    game_state=lvl_up;
for(unsigned i=0; i<snake.size()-3; i++)
{
    delete snake[i];
    snake[i]= 0;
}

    snake.clear();

    point->setX(120);
    point->setY(64);

    point2->setX(120);
    point2->setY(56);

    point3->setX(120);
    point3->setY(48);

    snake.push_back(point);
    snake.push_back(point2);
    snake.push_back(point3);

    direction = backward;

}
//*************************************************************
void MainWindow::hardButton()
{
    if(game_state==not_started)
    {
        timer = new QTimer(this);
        connect(timer,SIGNAL(timeout()),this,SLOT(TimerSlot()));
        timer->start(100);
        game_state = started;
        gm_level = hard;
        points_for_fruit=30;
    }
   game_state=started;
   gm_level = hard;
   delete e_button;
   delete m_button;
   delete h_button;
}
//****************************************************************
void MainWindow::easyButton()
{
    if(game_state==not_started)
    {
        timer = new QTimer(this);
        connect(timer,SIGNAL(timeout()),this,SLOT(TimerSlot()));
        timer->start(300);
        game_state = started;
        gm_level = hard;
        points_for_fruit=10;
    }
   game_state=started;
   gm_level = easy;
   delete e_button;
   delete m_button;
   delete h_button;
}
//******************************************************************
void MainWindow::mediumButton()
{
    if(game_state==not_started)
    {
        timer = new QTimer(this);
        connect(timer,SIGNAL(timeout()),this,SLOT(TimerSlot()));
        timer->start(200);
        game_state = started;
        gm_level = hard;
        points_for_fruit=20;
    }
   game_state=started;
   gm_level = medium;
   delete e_button;
   delete m_button;
   delete h_button;
}
//*******************************************************************

