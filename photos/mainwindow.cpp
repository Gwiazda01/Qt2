#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    columns = new QLineEdit(this);
    lines = new QLineEdit(this);
    picsQuantity = 0;
    for(unsigned int i=0; i<21; ++i)
    {        
        abc = ":pics/car";
        abc.append(QString::number(i));
        abc.append(".jpeg");
        picButton[i] = new CustomButton(abc, this);
        picButton[i]->setObjectName(QString::number(i));
        ++picsQuantity;
    }
    QRect rec = QApplication::desktop()->screenGeometry();
    x = rec.width();
    y = rec.height();
    lines->setGeometry(x-200,20,100,30);
    columns->setGeometry(x-320,20,100,30);
    lines->setText("Type lines");
    columns->setText("Type columns");
    resizeButton = new QPushButton("Resize",this);
    resizeButton->setGeometry(x-95,20,50,30);
    connect(resizeButton, SIGNAL(released()), this, SLOT(lineEdit()));
    createButtons(5,3);

    for(unsigned int i=0; i<picsQuantity; ++i)
        connect(picButton[i], SIGNAL(released()), this, SLOT(picButtons()));
}



MainWindow::~MainWindow()
{
    for(unsigned int i=0; i<picsQuantity; ++i)
    {
        delete picButton[i];

    }
    delete resizeButton;
    delete ui;
}
//***************************************************************
void MainWindow::createButtons(unsigned int k, unsigned int w)
{
    if(k<=0) k=1;
    if(w<=0) w=1;
    for(unsigned int i=k*w ; i<picsQuantity; ++i)
    {
        picButton[i]->setGeometry(0,0,0,0);
    }
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
    if(gapX<50)
    {
        int moreSpace =(50-gapX)*(k+1);
        picX = picX - moreSpace/k;
        gapX=50;
    }
    if(gapY<50)
    {
        int moreSpace = (50-gapY)*(w+1);
        picY = picY - moreSpace/w;
        gapY=50;
    }
    for(unsigned int i=0; i<picsQuantity; ++i)
    {
        picButton[i]->picture = picButton[i]->orginalPicture.scaled(picX,picY,Qt::IgnoreAspectRatio,Qt::FastTransformation);
        makeGray(picButton[i]->picture, i);
        picButton[i]->picBrush.setTexture(picButton[i]->picture);
        picButton[i]->picPalette.setBrush(QPalette::Button,picButton[i]->picBrush);
        picButton[i]->setPalette(picButton[i]->picPalette);
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
    picButton[a]->grayPicture = pixmap;

}
//******************************************************************
void MainWindow::picButtons()
{
    int a = sender()->objectName().toInt();
    if(!picButton[a]->isGray)
    {
    picButton[a]->picBrush.setTexture(picButton[a]->grayPicture);
    picButton[a]->picPalette.setBrush(QPalette::Button,picButton[a]->picBrush);
    picButton[a]->setPalette(picButton[a]->picPalette);
    picButton[a]->isGray=true;
    }
    else
    {
    picButton[a]->picBrush.setTexture(picButton[a]->picture);
    picButton[a]->picPalette.setBrush(QPalette::Button,picButton[a]->picBrush);
    picButton[a]->setPalette(picButton[a]->picPalette);
    picButton[a]->isGray=false;
    }
}
//********************************************************************
void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setFont(QFont("Arial", 20));
    painter.drawText(x-219,45, "X");
}
//*********************************************************************
void MainWindow::lineEdit()
{

        int k = columns->text().toInt();
        int l = lines->text().toInt();
        if(k<0 || l<0)
        {
            QMessageBox box(this);
            box.setWindowTitle("Error!");
            box.setText("Wrong numbers... Try again ;)");
            box.setStandardButtons(QMessageBox::Ok);
            //box.setWindowFlags(Qt::WindowStaysOnBottomHint);
            box.setVisible(true);
        }
        else
        {
            createButtons(k, l);
            update();
        }
}
