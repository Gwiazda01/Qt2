#ifndef INTERFACE_H
#define INTERFACE_H

#include <QtWidgets>

class Interface
{
public:
    //Interface();
    virtual ~Interface();
    virtual QString getAbsFilePath(QString pathToFileWithPaths, unsigned int position) = 0;
};

#endif // INTERFACE_H
