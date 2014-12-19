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
    QFile f("C:/Users/Marta/Desktop/Podlogi/sciezki.txt");
    if(!f.open(QIODevice::ReadOnly | QIODevice::Text))
        QMessageBox::information(this,
           "File open error",
           "Nie mozna otworzyc katalogu ze sciazkami do zdjec."
           );
    QTextStream in(&f);
    in.setCodec("UTF-8");
    while(!in.atEnd())
    {
        QString line = in.readLine();
        QFileInfoList info = QDir(line).entryInfoList(QStringList()<<"*.jpg"<<"*.jpeg"<<"*.png",
                                                                                       QDir::Files, QDir::Name);
        foreach(const QFileInfo &inf, info)
        {
            picButton.push_back(new CustomButton(inf.absoluteFilePath(), this));
            picButton[picsQuantity]->fileName = inf.fileName();
            picButton[picsQuantity]->setObjectName(QString::number(picsQuantity));
            ++picsQuantity;
        }
    }
    f.close();


    QDir dir("C:/Users/Marta/Desktop/Podlogi/");
    dir.mkpath("C:/Users/Marta/Desktop/Podlogi/Usuniete");
    dir.mkpath("C:/Users/Marta/Desktop/Podlogi/Do rozpatrzenia");
    dir.mkpath("C:/Users/Marta/Desktop/Podlogi/Zaakceptowane");
    QRect rec = QApplication::desktop()->screenGeometry();
    x = rec.width();
    y = rec.height();
    lines->setGeometry(x-200,30,100,20);
    columns->setGeometry(x-320,30,100,20);

    resizeButton = new QPushButton("Resize",this);
    resizeButton->setGeometry(x-95,30,50,20);
    connect(resizeButton, SIGNAL(released()), this, SLOT(resizeBtn()));

    page = 1;
    nextPage = new QPushButton("Next Page",this);
    previousPage = new QPushButton("Previous Page", this);
    nextPage->setGeometry(x-425,30,75,20);
    previousPage->setGeometry(x-500,30,75,20);
    connect(nextPage, SIGNAL(released()), this, SLOT(nextButton()));
    connect(previousPage, SIGNAL(released()), this, SLOT(previousButton()));
    k=5, w=3;
    createButtons();

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
    delete columns;
    delete lines;

    delete ui;
}
//***************************************************************
void MainWindow::createButtons()
{
    if(picsQuantity%(k*w))
            size = picsQuantity/(k*w) + 1;
        else
            size = picsQuantity/(k*w);

    if(page!=1)
        previousPage->setEnabled(true);
    else
        previousPage->setEnabled(false);


    if(page!=size)
        nextPage->setEnabled(true);
    else
        nextPage->setEnabled(false);



    if(k<=0 || w<=0 || k>10 || w>10)
    {
        QMessageBox::information(this,
           "File input error",
           "Bledne dane wprowadzone do funkcji CreateButtons\nDane wejsciowe musza zmiescic sie w zakresie (1; 10)"
           );
    }
    else
    {
        for(unsigned int i=page*(unsigned int)k*w ; i<picsQuantity; ++i)
        {
            picButton[i]->setGeometry(0,0,0,0);
        }
        for(unsigned int i=0 ; i<( (page-1)*k*w); ++i)
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
            if(!picButton[i]->isGray)
                picButton[i]->picBrush.setTexture(picButton[i]->picture);
            else
                picButton[i]->picBrush.setTexture(picButton[i]->grayPicture);
            picButton[i]->picPalette.setBrush(QPalette::Button,picButton[i]->picBrush);
            picButton[i]->setPalette(picButton[i]->picPalette);
        }

        for(unsigned int j=0; j<(unsigned int)w; ++j)
        {
            for(unsigned int i=0 ; i<(unsigned int)k; ++i)
            {
                index = i+(unsigned int)k*j+ (page-1)*k*w;
                if(index>=picsQuantity)
                    break;
                picButton[index]->setGeometry((gapX+i*(picX+gapX)),(gapY+j*(picY+gapY)),picX,picY);
            }
            if(index>=picsQuantity)
                break;
        }
    }
    update();
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
        QMessageBox msgBox;
        msgBox.setWindowTitle("Do jakiego folderu przeniesc zdjecie?");
        msgBox.setIcon(QMessageBox::Question);
        QPushButton *deleteButton = msgBox.addButton(tr("Usuniete"), QMessageBox::ActionRole);
        QPushButton *forConsiderationButton = msgBox.addButton(tr("Do rozpatrzenia"), QMessageBox::ActionRole);
        QPushButton *acceptButton = msgBox.addButton(tr("Zaakceptowane"), QMessageBox::ActionRole);

        msgBox.exec();
        if (msgBox.clickedButton() == deleteButton)
        {
            picButton[a]->picBrush.setTexture(picButton[a]->grayPicture);
            picButton[a]->picPalette.setBrush(QPalette::Button,picButton[a]->picBrush);
            picButton[a]->setPalette(picButton[a]->picPalette);
            QFile::rename(picButton[a]->filePath, ("C:/Users/Marta/Desktop/Podlogi/Usuniete/"+picButton[a]->fileName) );
            picButton[a]->filePath = "C:/Users/Marta/Desktop/Podlogi/Usuniete/"+picButton[a]->fileName;
            picButton[a]->isGray = true;
        }
        else if (msgBox.clickedButton() == forConsiderationButton)
        {
            picButton[a]->picBrush.setTexture(picButton[a]->grayPicture);
            picButton[a]->picPalette.setBrush(QPalette::Button,picButton[a]->picBrush);
            picButton[a]->setPalette(picButton[a]->picPalette);
            QFile::rename(picButton[a]->filePath, ("C:/Users/Marta/Desktop/Podlogi/Do rozpatrzenia/"+picButton[a]->fileName) );
            picButton[a]->filePath = "C:/Users/Marta/Desktop/Podlogi/Do rozpatrzenia/"+picButton[a]->fileName;
            picButton[a]->isGray = true;
        }
        else if(msgBox.clickedButton() == acceptButton)
        {
            picButton[a]->picBrush.setTexture(picButton[a]->picture);
            picButton[a]->picPalette.setBrush(QPalette::Button,picButton[a]->picBrush);
            picButton[a]->setPalette(picButton[a]->picPalette);
            QFile::rename(picButton[a]->filePath, ("C:/Users/Marta/Desktop/Podlogi/Zaakceptowane/"+picButton[a]->fileName) );
            picButton[a]->filePath = "C:/Users/Marta/Desktop/Podlogi/Zaakceptowane/"+picButton[a]->fileName;
            picButton[a]->isGray = false;

        }
}
//********************************************************************
void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setFont(QFont("Arial", 14));
    painter.drawText(x-216,46, "X");
    painter.setFont(QFont("Times", 10));
    painter.drawText(x-315,28, "Columns:");
    painter.drawText(x-195,28, "Lines:");
}
//*********************************************************************
void MainWindow::nextButton()
{
        if(page!=size)
            ++page;

    createButtons();
}
//*********************************************************************
void MainWindow::previousButton()
{
    if(page!=1)
        --page;

    createButtons();
}
//********************************************************************
void MainWindow::resizeBtn()
{
    page = 1;
    if(!columns->text().isEmpty())
        k = columns->text().toInt();

    if(!lines->text().isEmpty())
        w = lines->text().toInt();
    createButtons();
}
