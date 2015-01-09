#include "mainwindow.h"
#include "ui_mainwindow.h"

<<<<<<< HEAD
=======
int const MainWindow::EXIT_CODE_REBOOT = -123456789;
bool MainWindow::appFirstStarted = true;
bool MainWindow::katalog;
QString MainWindow::filePath;
unsigned int MainWindow::absolutePicsQuantity = 0;
unsigned int MainWindow::part, MainWindow::totalParts, MainWindow::picsPerPart = 10;
>>>>>>> 3d5f9023ee077e77f3f392262345152719041c72

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
<<<<<<< HEAD
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
=======
    if(appFirstStarted)
    {
        QMessageBox fPath;
        fPath.setWindowTitle("Wybór ścieżki");
        fPath.setText("Do czego ścieżki będziesz wpisywać?");
        fPath.setIcon(QMessageBox::Question);
        QPushButton *catalogButton = fPath.addButton(tr("Katalogi"), QMessageBox::ActionRole);
        QPushButton *fileButton = fPath.addButton(tr("Pliki"), QMessageBox::ActionRole);

        fPath.exec();
        if (fPath.clickedButton() == catalogButton)
            katalog = true;
        else if (fPath.clickedButton() == fileButton)
            katalog = false;

    //QFileDialog dialog(this, tr("Ścieżki"), QDir::homePath(), "Text files (*.txt);; Any file (*)");
        if(katalog)
            filePath = QFileDialog::getOpenFileName(this, tr("Ścieżki do katalogów"),
                                                            QDir::homePath(),
                                                            tr("Text files (*.txt);;Any file (*)"));
        //filePath = dialog.getOpenFileName();
        else
            filePath = QFileDialog::getOpenFileName(this, tr("Ścieżki do plików"),
                                                        QDir::homePath(),
                                                        tr("Text files (*.txt);;Any file (*)"));
        //filePath = dialog.getOpenFileName();
    }
        isStarted = true;
    if(!filePath.isEmpty())
    {
        QFile file(MainWindow::filePath);
        if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
                QMessageBox::information(this,
                "File open error",
                "Nie mozna otworzyc katalogu ze sciazkami do zdjec."
                );
        QTextStream in(&file);
        in.setCodec("UTF-8");
        if(appFirstStarted)
        {
            qint64 posBefore = in.pos();
            while(!in.atEnd())
            {
                if(katalog)
                {
                    QString line = in.readLine();
                    QFileInfoList info = QDir(line).entryInfoList(QStringList()<<"*.jpg"<<"*.jpeg"<<"*.png",
                                                                                        QDir::Files, QDir::Name);
                    foreach(const QFileInfo &inf, info)
                        ++absolutePicsQuantity;
                }
                else
                        ++absolutePicsQuantity;
            }
            in.seek(posBefore);
            part = 1;
        }

        if(absolutePicsQuantity % picsPerPart)
            totalParts = absolutePicsQuantity/picsPerPart + 1;
        else
            totalParts = absolutePicsQuantity;

        endPicsDisplay = part * picsPerPart;
        startPicsDisplay = endPicsDisplay - picsPerPart;
        while(!in.atEnd())
        {
            QString line = in.readLine();
            int iterator = 0;
            if(katalog)
            {
                QFileInfoList info = QDir(line).entryInfoList(QStringList()<<"*.jpg"<<"*.jpeg"<<"*.png",
                                                                                        QDir::Files, QDir::Name);
                foreach(const QFileInfo &inf, info)
                {
                    ++picsQuantity;
                    if( (picsQuantity - 1 >= startPicsDisplay) && ( picsQuantity-1 < endPicsDisplay) )
                    {
                        picButton.push_back(new CustomButton(inf.absoluteFilePath(), this));
                        picButton[iterator]->fileName = inf.fileName();
                        picButton[iterator]->setObjectName(QString::number(iterator));
                        ++iterator;
                    }

                }
            }
            else
            {
                    QFileInfo file(line);
                    ++picsQuantity;
                    if( (picsQuantity - 1 >= startPicsDisplay) && (picsQuantity - 1 < endPicsDisplay) )
                    {
                        picButton.push_back(new CustomButton(file.absoluteFilePath(), this));
                        picButton[iterator]->fileName = file.fileName();
                        picButton[iterator]->setObjectName(QString::number(iterator));
                        ++iterator;
                    }


            }
        }
        file.close();
    }
    else
        QMessageBox::information(this,
        "File path error",
        "Błąd odczytu ścieżki pliku."
        );
    page = 1;

    columns = new QLineEdit(this);
    lines = new QLineEdit(this);
    partEditLine = new QLineEdit(this);
    picsPerPartEditLine = new QLineEdit(this);
    resizeButton = new QPushButton("Resize",this);
    nextPage = new QPushButton("Next Page",this);
    previousPage = new QPushButton("Previous Page", this);
    acceptButton = new QPushButton("Accept photos", this);
    changePart = new QPushButton("Go", this);
    changePicsPerPart = new QPushButton("Change", this);

    lines->setGeometry(x-200,30,100,20);
    columns->setGeometry(x-320,30,100,20);
    partEditLine->setGeometry(x-855,30,50,20);
    picsPerPartEditLine->setGeometry(175,30,50,20);

    resizeButton->setGeometry(x-95,30,50,20);
    nextPage->setGeometry(x-425,30,85,20);
    previousPage->setGeometry(x-510,30,90,20);
    acceptButton->setGeometry(x-630,30,95,20);
    changePart->setGeometry(x-800,30,50,20);
    changePicsPerPart->setGeometry(230,30,50,20);


    connect(resizeButton, SIGNAL(released()), this, SLOT(resizeBtn()));
    connect(nextPage, SIGNAL(released()), this, SLOT(nextButton()));
    connect(previousPage, SIGNAL(released()), this, SLOT(previousButton()));
    connect(acceptButton, SIGNAL(released()), this, SLOT(acceptAction()));
    connect(changePart, SIGNAL(released()), this, SLOT(restartAction()));
    connect(changePicsPerPart, SIGNAL(released()), this, SLOT(changePicsPerPartAction()));

    k=5, w=3;
    createButtons();
    for(unsigned int i=0; i<picsPerPart && ((part-1)*picsPerPart + i < absolutePicsQuantity); ++i)
        connect(picButton[i], SIGNAL(released()), this, SLOT(picButtons()));

    QDir dir = QDir::home();
    root = dir.absolutePath();
    dir.mkpath(root + "/Zdjecia/Usuniete/");
    dir.mkpath(root + "/Zdjecia/Do rozpatrzenia/");
    dir.mkpath(root + "/Zdjecia/Zaakceptowane/");

>>>>>>> 3d5f9023ee077e77f3f392262345152719041c72
}



MainWindow::~MainWindow()
{
    for(unsigned int i=0; i<picsQuantity; ++i)
    {
        delete picButton[i];

    }
    delete resizeButton;
<<<<<<< HEAD
    delete ui;
}
//***************************************************************
void MainWindow::createButtons(unsigned int k, unsigned int w)
{
    if(k<=0) k=1;
    if(w<=0) w=1;
    for(unsigned int i=k*w ; i<picsQuantity; ++i)
=======
    delete changePart;
    delete changePicsPerPart;
    delete partEditLine;
    delete picsPerPartEditLine;
    delete columns;
    delete lines;
    delete nextPage;
    delete previousPage;
    delete ui;
}
//*************************************************************************************************
void MainWindow::createButtons()
{

        if( absolutePicsQuantity < part * picsPerPart )
        {
            if( (absolutePicsQuantity - (part-1) * picsPerPart) % (k*w) && (absolutePicsQuantity - (part-1) * picsPerPart) > (k*w))
                size = (absolutePicsQuantity - (part-1) * picsPerPart)/(k*w) + 1;
            else if((absolutePicsQuantity - (part-1) * picsPerPart) > (k*w))
                size = (absolutePicsQuantity - (part-1) * picsPerPart)/(k*w);
            else
                size = 1;

        }
        else
        {
            if(picsPerPart%(k*w))
                size = picsPerPart/(k*w) + 1;
            else
                size = picsPerPart/(k*w);
        }

    if(page!=1)
        previousPage->setEnabled(true);
    else
        previousPage->setEnabled(false);


    if(page<size)
        nextPage->setEnabled(true);
    else
        nextPage->setEnabled(false);



    if(k<=0 || w<=0 || k>10 || w>10)
>>>>>>> 3d5f9023ee077e77f3f392262345152719041c72
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
<<<<<<< HEAD
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
=======
        painter.setFont(QFont("Arial", 14));
        painter.drawText(x-216,46, "X");
        painter.setFont(QFont("Times", 10));
        painter.drawText(x-315,28, "Columns:");
        painter.drawText(x-195,28, "Lines:");
        painter.setFont(QFont("Times", 11));
        painter.drawText(x-940,44,"Choose part:");
        painter.drawText(335, 44, "Part: "+QString::number(part)+"/"+QString::number(totalParts));
        painter.drawText(50,32,"Pictures per part:");
        painter.drawText(75,48, QString::number(picsPerPart) + "/" + QString::number(absolutePicsQuantity));

>>>>>>> 3d5f9023ee077e77f3f392262345152719041c72
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
<<<<<<< HEAD
=======
//**********************************************************************************
void MainWindow::restartAction()
{
    MainWindow::appFirstStarted = false;
    if((!partEditLine->text().isEmpty() || !picsPerPartEditLine->text().isEmpty()) && (unsigned)partEditLine->text().toInt()<=totalParts && (unsigned)partEditLine->text().toInt()>0)
    {
        if((unsigned)partEditLine->text().toInt()!=part)
        {
            this->close();
            qApp->exit(MainWindow::EXIT_CODE_REBOOT);
            delete this;
            part = partEditLine->text().toInt();
        }
    }
    else
       QMessageBox::information(this,
           "Error",
           "Poza zakresem!"
           );
}
//*****************************************************************************************
void MainWindow::changePicsPerPartAction()
{
   if(!picsPerPartEditLine->text().isEmpty()&& picsPerPartEditLine->text().toInt()>0 && picsPerPartEditLine->text().toInt() <= 1000)
   {
       MainWindow::appFirstStarted = false;
       this->close();
       qApp->exit(MainWindow::EXIT_CODE_REBOOT);
       delete this;
       part = 1;
       picsPerPart = picsPerPartEditLine->text().toInt();
   }
   else
      QMessageBox::information(this,
          "Error",
          "Poza zakresem!"
          );
}
>>>>>>> 3d5f9023ee077e77f3f392262345152719041c72
