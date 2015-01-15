#ifndef CATALOGPATH_H
#define CATALOGPATH_H

#include "interface.h"

class CatalogPath : public Interface
{
public:
    CatalogPath();
    ~CatalogPath();
    QString getAbsFilePath(QString pathToFileWithPaths, unsigned int position);
};

#endif // CATALOGPATH_H
