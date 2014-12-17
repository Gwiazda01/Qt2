#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "custombutton.h"

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
    void createButtons(unsigned int, unsigned int);
    void makeGray(QPixmap, int );
    QString abc;
    QPushButton *resizeButton;
    CustomButton *picButton[21];
    unsigned int x,y, picsQuantity;
    QLineEdit *columns, *lines;
public slots:
    void picButtons();
    void lineEdit();

private:
    Ui::MainWindow *ui;
};


#endif // MAINWINDOW_H
