#include "catalogpath.h"

CatalogPath::CatalogPath()
{

}

CatalogPath::~CatalogPath()
{

}
//*********************************************************************************
QString CatalogPath::getAbsFilePath(QString pathToFileWithPaths, unsigned int position)
{
    QFile file(pathToFileWithPaths);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
            qDebug()<<"ERROR!";
    QTextStream in(&file);
    in.setCodec("UTF-8");
    QString line, x;

    while(!in.atEnd())
    {
        line = in.readLine();

        QFileInfoList info = QDir(line).entryInfoList(QStringList()<<"*.jpg"<<"*.jpeg"<<"*.png",
                                                                            QDir::Files, QDir::Name);
        int iterator = 0;
        bool found = false;
        foreach(const QFileInfo &inf, info)
        {
            if( iterator == position )
            {
                x = inf.absoluteFilePath();
                found = true;
                break;
            }
            ++iterator;
        }
        if(found)
            break;
    }
        return x;

    file.close();

}



