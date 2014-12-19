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

    void makeGray(QPixmap, int );
    QString abc;
    QPushButton *resizeButton, *nextPage, *previousPage;
    std::vector <CustomButton*> picButton;
    unsigned int x,y, picsQuantity, page, k, w, size;
    QLineEdit *columns, *lines;
public slots:
    void picButtons();
    void createButtons();
    void nextButton();
    void previousButton();
    void resizeBtn();

private:
    Ui::MainWindow *ui;
};


#endif // MAINWINDOW_H
