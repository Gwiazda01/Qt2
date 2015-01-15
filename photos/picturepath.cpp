#include "picturepath.h"
#include <QMessageBox>

PicturePath::PicturePath()
{

}

PicturePath::~PicturePath()
{

}
//***************************************************************
QString PicturePath::getAbsFilePath(QString pathToFileWithPaths, unsigned int position)
{
    QFile file(pathToFileWithPaths);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
            qDebug()<<"ERROR!";
    QTextStream in(&file);
    in.setCodec("UTF-8");
    unsigned int iterator = 0;
    QString line;

    while(!in.atEnd())
    {
        line = in.readLine();
        if(iterator == position)
            break;
        iterator ++;
    }

    file.close();
    return line;
}
