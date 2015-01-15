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
    QFileInfoList info = QDir(pathToFileWithPaths).entryInfoList(QStringList()<<"*.jpg"<<"*.jpeg"<<"*.png",
                                                                            QDir::Files, QDir::Name);
    int iterator = 0;
    QString x;
    foreach(const QFileInfo &inf, info)
    {
        if( iterator == position )
        {
            x = inf.absoluteFilePath();
            break;
        }
        ++iterator;
    }
    return x;
}



