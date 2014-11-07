#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    scene->setSceneRect(-200,-200,300,300);

    QPen mypen = QPen(Qt::red);
    QLine TopLine(scene->sceneRect().topLeft(), scene->sceneRect().topRight());
    QLine LeftLine(scene->sceneRect().topLeft(), scene->sceneRect().bottomLeft());
    QLine RightLine(scene->sceneRect().topRight(), scene->sceneRect().bottomRight());
    QLine BottomLine(scene->sceneRect().bottomLeft(), scene->sceneRect().bottomRight());

    scene->addLine(TopLine,mypen);
    scene->addLine(LeftLine,mypen);
    scene->addLine(RightLine,mypen);
    scene->addLine(BottomLine,mypen);

}

Dialog::~Dialog()
{
    delete ui;

}
