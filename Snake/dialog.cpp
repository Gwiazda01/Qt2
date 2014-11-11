#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);

    QPen pen(Qt::black);
    pen.setWidth(4);

    //snake.push_back(scene->addLine(-100,-100,-100,-101,pen));
   // snake.push_back(scene->addLine(-100,-96,-100,-97,pen));
   // snake.push_back(scene->addLine(-100,-92,-100,-93,pen));
    rect = scene->addRect(-200,-200,200,200);
    point = new QGraphicsEllipseItem(-100,-100,1,1);
    point->setPen(pen);
    scene->addItem(point);
    point1 = new QGraphicsEllipseItem(-100,-96,1,1);
    point1->setPen(pen);
    scene->addItem(point1);
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(TimerSlot()));
    timer->start(200);
    srand(time(NULL));



}
Dialog::~Dialog()
{
    delete ui;
}

void Dialog::TimerSlot()
{

    switch(kierunek)
    {
    case forward:
        //snake[0]->moveBy(0,-1);
        point->moveBy(0,-1);
        break;
    case backward:
        //snake[0]->moveBy(0,1);
        point->moveBy(0,1);
        break;
    case left:
        //snake[0]->moveBy(-1,0);
        point->moveBy(-1,0);
        break;
    case right:
        //snake[0]->moveBy(1,0);
        point->moveBy(1,0);
        break;
    }
    point1->setPos(point->x()-1,point->y());
    /*for(int i=1; i< snake.size();++i)
    {

        snake[i]->setPos(snake[i-1]->x(),snake[i-1]->y());
    }*/

}
//***************************************************************
void Dialog::keyPressEvent(QKeyEvent *key)
{
    switch(key->key())
    {
    case Qt::Key_S:
     kierunek=backward;
     break;
    case Qt::Key_W:
     kierunek=forward;
     break;
    case Qt::Key_A:
     kierunek=left;
     break;
    case Qt::Key_D:
     kierunek=right;
     break;
    case Qt::Key_E:
     addFruit();
     break;
    }

}
//******************************************************************
void Dialog::addFruit()
{
    QPen fruitPen(Qt::red);
    fruitPen.setWidth(3);
    signed x = -(rand()%200 + 1);
    signed y = -(rand()%200 + 1);
    fruit = scene->addLine(x,y,x,y+1,fruitPen);
}
//*************************************************************


