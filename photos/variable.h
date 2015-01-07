#ifndef VARIABLE_H
#define VARIABLE_H

#include "mainwindow.h"

class Variable : public QObject
{
    Q_OBJECT
public:
    explicit Variable(QObject *parent = 0);
    ~Variable();
    static bool appFirstStarted, katalog;
    static QString filePath;

signals:

public slots:
};

#endif // VARIABLE_H
