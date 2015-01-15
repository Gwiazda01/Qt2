#ifndef PICTUREPATH_H
#define PICTUREPATH_H

#include "interface.h"

class PicturePath : public Interface
{
public:
    PicturePath();
    ~PicturePath();
    QString getAbsFilePath(QString pathToFileWithPaths, unsigned int position);
};

#endif // PICTUREPATH_H
