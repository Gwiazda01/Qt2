#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    picsQuantity = 0;
    isStarted = false;

    QRect rec = QApplication::desktop()->screenGeometry();
    x = rec.width();
    y = rec.height();

    bool katalog;

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


    QString filePath;
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
    isStarted = true;
    if(!filePath.isEmpty())
    {
        QFile file(filePath);
        if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
                QMessageBox::information(this,
                "File open error",
                "Nie mozna otworzyc katalogu ze sciazkami do zdjec."
                );
        QTextStream in(&file);
        in.setCodec("UTF-8");
        while(!in.atEnd())
        {
            QString line = in.readLine();
            if(katalog)
            {
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
            else
            {
                    QFileInfo file(line);
                    picButton.push_back(new CustomButton(file.absoluteFilePath(), this));
                    picButton[picsQuantity]->fileName = file.fileName();
                    picButton[picsQuantity]->setObjectName(QString::number(picsQuantity));
                    ++picsQuantity;

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
    resizeButton = new QPushButton("Resize",this);
    nextPage = new QPushButton("Next Page",this);
    previousPage = new QPushButton("Previous Page", this);
    acceptButton = new QPushButton("Accept photos", this);

    lines->setGeometry(x-200,30,100,20);
    columns->setGeometry(x-320,30,100,20);
    resizeButton->setGeometry(x-95,30,50,20);
    nextPage->setGeometry(x-425,30,85,20);
    previousPage->setGeometry(x-510,30,90,20);
    acceptButton->setGeometry(x-630,30,95,20);

    connect(resizeButton, SIGNAL(released()), this, SLOT(resizeBtn()));
    connect(nextPage, SIGNAL(released()), this, SLOT(nextButton()));
    connect(previousPage, SIGNAL(released()), this, SLOT(previousButton()));
    connect(acceptButton, SIGNAL(released()), this, SLOT(acceptAction()));

    k=5, w=3;
    createButtons();
    for(unsigned int i=0; i<picsQuantity; ++i)
        connect(picButton[i], SIGNAL(released()), this, SLOT(picButtons()));


    QDir dir = QDir::home();
    root = dir.absolutePath();
    dir.mkpath(root + "/Zdjecia/Usuniete/");
    dir.mkpath(root + "/Zdjecia/Do rozpatrzenia/");
    dir.mkpath(root + "/Zdjecia/Zaakceptowane/");

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


    if(page<size)
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
            picButton[i]->picture = picButton[i]->originalPicture.scaled(picX,picY,Qt::IgnoreAspectRatio,Qt::FastTransformation);
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
        msgBox.setWindowTitle("Przeniesienie zdjęcia");
        msgBox.setText("Do jakiego folderu przeniesc zdjecie?");
        msgBox.setIcon(QMessageBox::Question);
        QPushButton *deleteButton = msgBox.addButton(tr("Usuniete"), QMessageBox::ActionRole);
        QPushButton *forConsiderationButton = msgBox.addButton(tr("Do rozpatrzenia"), QMessageBox::ActionRole);
        QPushButton *acptButton = msgBox.addButton(tr("Zaakceptowane"), QMessageBox::ActionRole);
        QPushButton *abortButton = msgBox.addButton(tr("Cofnij zmiany/Anuluj"), QMessageBox::ActionRole);

        msgBox.exec();

        picButton[a]->picBrush.setTexture(picButton[a]->grayPicture);
        picButton[a]->picPalette.setBrush(QPalette::Button,picButton[a]->picBrush);
        picButton[a]->setPalette(picButton[a]->picPalette);
        picButton[a]->isGray = true;

/*filePath przechowuje sciezke do folderu, do ktorego zostal skopiowany obrazek, dzieki czemu bedzie mozna pozniej
cofnac zaznaczenie przyciskiem abortButton*/

        if (msgBox.clickedButton() == deleteButton)
        {
            QFile::copy(picButton[a]->filePath, (root + "/Zdjecia/Usuniete/"+picButton[a]->fileName) );
            picButton[a]->filePath = root + "/Zdjecia/Usuniete/"+picButton[a]->fileName;
        }
        else if (msgBox.clickedButton() == forConsiderationButton)
        {
            QFile::copy(picButton[a]->filePath, (root + "/Zdjecia/Do rozpatrzenia/"+picButton[a]->fileName) );
            picButton[a]->filePath = root + "/Zdjecia/Do rozpatrzenia/"+picButton[a]->fileName;
        }
        else if (msgBox.clickedButton() == acptButton)
        {
            QFile::copy(picButton[a]->filePath, (root + "/Zdjecia/Zaakceptowane/"+picButton[a]->fileName) );
            picButton[a]->filePath = root + "/Zdjecia/Zaakceptowane/"+picButton[a]->fileName;
        }
        else if(msgBox.clickedButton() == abortButton)
        {
            picButton[a]->picBrush.setTexture(picButton[a]->picture);
            picButton[a]->picPalette.setBrush(QPalette::Button,picButton[a]->picBrush);
            picButton[a]->setPalette(picButton[a]->picPalette);
            if(picButton[a]->isGray)
                QFile::remove(picButton[a]->filePath);
            picButton[a]->isGray = false;

        }
}
//********************************************************************
void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    if(isStarted)
    {
        painter.setFont(QFont("Arial", 14));
        painter.drawText(x-216,46, "X");
        painter.setFont(QFont("Times", 10));
        painter.drawText(x-315,28, "Columns:");
        painter.drawText(x-195,28, "Lines:");
    }
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
//****************************************************************************
void MainWindow::acceptAction()
{
        QMessageBox acceptBox;
        acceptBox.setWindowTitle("Akceptacja zdjęć?");
        acceptBox.setText("Czy przenieść niezaznaczone zdjęcia do folderu \"Zaakceptowane\"?");
        acceptBox.setIcon(QMessageBox::Question);
        QPushButton *YesButton = acceptBox.addButton(tr("Tak"), QMessageBox::ActionRole);
        QPushButton *NoButton = acceptBox.addButton(tr("Nie"), QMessageBox::ActionRole);
        acceptBox.exec();
        if(acceptBox.clickedButton() == YesButton)
        {
                for(unsigned int i=0; i<picsQuantity; ++i)
                {
                    if(!picButton[i]->isGray)
                    {
                        picButton[i]->picBrush.setTexture(picButton[i]->grayPicture);
                        picButton[i]->picPalette.setBrush(QPalette::Button,picButton[i]->picBrush);
                        picButton[i]->setPalette(picButton[i]->picPalette);
                        QFile::copy(picButton[i]->filePath, (root + "/Zdjecia/Zaakceptowane/"+picButton[i]->fileName) );
                        picButton[i]->filePath = root + "/Zdjecia/Zaakceptowane/"+picButton[i]->fileName;
                        picButton[i]->isGray = true;
                    }
                }
        }
        else if(acceptBox.clickedButton() == NoButton)
        {
            acceptBox.close();
        }
}
