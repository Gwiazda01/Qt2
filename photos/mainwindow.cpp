#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QtGui"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    columns = new QLineEdit(this);
    lines = new QLineEdit(this);
    for(unsigned int i=0; i<15; ++i)
    {
        pic[i] = new QPixmap();
        grayPic[i] = new QPixmap();
        picButton[i] = new QPushButton(this);
        picButton[i]->setObjectName(QString::number(i));
        picBrush[i] = new QBrush();
        picPalette[i] = new QPalette();
    }
    QRect rec = QApplication::desktop()->screenGeometry();
    x = rec.width();
    y = rec.height();
    lines->setGeometry(x-200,20,100,30);
    columns->setGeometry(x-320,20,100,30);
    lines->setText("Type lines");
    columns->setText("Type columns");

    createButtons(10,10);
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
void MainWindow::createButtons(unsigned int k, unsigned int w)
{
    QString abc;
    unsigned int picsQuantity = 15;
    unsigned int index;
    int picX;
    int picY;
    float scale;
    if(k>w) scale = (float)5/(float)k;
    else scale = (float)5/(float)w;
    picX = (float)200*scale;
    picY = (float)150*scale;
    int gapX = (x-(k*picX))/(k+1);
    int gapY = (y-(w*picY))/(w+1);
    if(gapX<15)
    {
        int moreSpace =(15-gapX)*(k+1);
        picX = picX - moreSpace/k;
        gapX=15;
    }
    if(gapY<20)
    {
        int moreSpace = (20-gapY)*(w+1);
        picY = picY - moreSpace/w;
        gapY=20;
    }
    for(unsigned int i=0; i<picsQuantity; ++i) // ładuje obrazki do tablicy pic
    {
        abc = ":pics/car";
        abc.append(QString::number(i));
        abc.append(".jpeg");

       pic[i]->load(abc);
       *pic[i]=pic[i]->scaled(picX,picY,Qt::IgnoreAspectRatio,Qt::FastTransformation);

       picBrush[i]->setTexture(*pic[i]);

       picPalette[i]->setBrush(QPalette::Button,*(picBrush[i]));


       picButton[i]->setFlat(true);
       picButton[i]->setAutoFillBackground(true);
       picButton[i]->setPalette(*picPalette[i]);
    }

    for(unsigned int j=0; j<w; ++j)
        for(unsigned int i=0 ; i<k; ++i)
        {
            index = i+k*j;
            if(index>=picsQuantity)
                break;
            picButton[index]->setGeometry((gapX+i*(picX+gapX)),(gapY+j*(picY+gapY)),picX,picY);
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
            gray = qGray(0);
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
//********************************************************************
void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setFont(QFont("Times", 20));
    painter.drawText(x-220,45, "X");
}
