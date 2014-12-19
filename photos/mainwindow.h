#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "custombutton.h"
#include <vector>
#include <stdio.h>
#include <stdlib.h>

namespace Ui {

class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
protected:
    void paintEvent(QPaintEvent *);
    void createButtons(int, int);
    void makeGray(QPixmap, int );
    QString abc;
    QPushButton *resizeButton;
    std::vector <CustomButton*> picButton;
    unsigned int x,y, picsQuantity;
    QLineEdit *columns, *lines;
public slots:
    void picButtons();
    void lineEdit();

private:
    Ui::MainWindow *ui;
};


#endif // MAINWINDOW_H
