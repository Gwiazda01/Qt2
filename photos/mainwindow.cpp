#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QtGui"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    for(unsigned int i=0; i<15; ++i)
    {
        pic[i] = new QPixmap();
        grayPic[i] = new QPixmap();
        picButton[i] = new QPushButton(this);
        picButton[i]->setObjectName(QString::number(i));
        picBrush[i] = new QBrush();
        picPalette[i] = new QPalette();
    }
    createButtons();
    createGrayPics();
    for(int i=0; i<15; ++i)
        connect(picButton[i], SIGNAL(released()), this, SLOT(picButtons()));
}



MainWindow::~MainWindow()
{
    for(unsigned int i=0; i<15; ++i)
    {
        delete pic[i];
        delete grayPic[i];
        delete picButton[i];
        delete picBrush[i];
        delete picPalette[i];
    }
    delete ui;
}
//***************************************************************
void MainWindow::createButtons()
{
    for(unsigned int i=0; i<15; ++i)
    {
        abc = ":pics/car";
        abc.append(QString::number(i));
        abc.append(".jpeg");

       pic[i]->load(abc);
       *pic[i]=pic[i]->scaled(200,150,Qt::IgnoreAspectRatio,Qt::FastTransformation);
    }
    unsigned int a=0;
    if(sizeof(pic)/4%5)
        a=1;

    for(unsigned int j=0; j<sizeof(pic)/4/5 + a; ++j)
        for(unsigned int i=0 ; i<5; ++i)
        {
            if(i==(sizeof(pic)/4%5) && j==sizeof(pic)/4/5)
                break;

            picBrush[i+j*5]->setTexture(*pic[i+j*5]);

            picPalette[i+j*5]->setBrush(QPalette::Button,*(picBrush[i+j*5]));


            picButton[i+j*5]->setFlat(true);
            picButton[i+j*5]->setAutoFillBackground(true);
            picButton[i+j*5]->setPalette(*picPalette[i+j*5]);
            picButton[i+j*5]->setGeometry((50+i*250),(50+j*200),(*pic[0]).width(),(*pic[0]).height());
        }
}

//****************************************************************
void MainWindow::makeGray(QPixmap pixmap, int a)
{

    QImage image = pixmap.toImage();
    QRgb col;
    int gray;
    int width = pixmap.width();
    int height = pixmap.height();
    for (int i = 0; i < width; ++i)
    {
        for (int j = 0; j < height; ++j)
        {
            col = image.pixel(i, j);
            gray = qGray(col);
            image.setPixel(i, j, qRgb(gray, gray, gray));
        }
    }
    for(int z = 0; z < width; ++z)
    for (int i = z; i < width; i+=5)
    {
        for (int j = z; j < height; j+=5)
        {
            gray = qGray(0,0,0);
            image.setPixel(i, j, qRgb(gray, gray, gray));
        }
    }
    pixmap = pixmap.fromImage(image);
    *grayPic[a] = pixmap;

}
//*******************************************************************
void MainWindow::createGrayPics()
{
    for(unsigned int i=0; i<15; ++i)
        makeGray(*pic[i], i);
}
//******************************************************************
void MainWindow::picButtons()
{
    int a = sender()->objectName().toInt();
 if(!isGray[a])
 {
    picBrush[a]->setTexture(*grayPic[a]);
    picPalette[a]->setBrush(QPalette::Button,*(picBrush[a]));
    picButton[a]->setPalette(*picPalette[a]);
    isGray[a]=true;
 }
 else
 {
     picBrush[a]->setTexture(*pic[a]);
     picPalette[a]->setBrush(QPalette::Button,*(picBrush[a]));
     picButton[a]->setPalette(*picPalette[a]);
     isGray[a]=false;
 }

}


