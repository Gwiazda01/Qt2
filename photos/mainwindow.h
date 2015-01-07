#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "custombutton.h"
#include "variable.h"
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
    static int const EXIT_CODE_REBOOT;
    static bool appFirstStarted, katalog;
    static QString filePath;
    static unsigned int absolutePicsQuantity, endPicsDisplay, startPicsDisplay, part, totalParts, picsPerPart, iterator;
protected:
    void paintEvent(QPaintEvent *);
    void makeGray(QPixmap, int );

    QString abc, root;
    QPushButton *resizeButton, *nextPage, *previousPage, *okButton, *acceptButton, *changePart;
    std::vector <CustomButton*> picButton;
    unsigned int x,y, picsQuantity, page, k, w, size;
    QLineEdit *columns, *lines, *partEditLine;
    bool isStarted;

public slots:
    void picButtons();
    void createButtons();
    void nextButton();
    void previousButton();
    void resizeBtn();
    void acceptAction();
    void restartAction();
private:
    Ui::MainWindow *ui;
};


#endif // MAINWINDOW_H
