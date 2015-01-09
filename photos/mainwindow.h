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
    static unsigned int absolutePicsQuantity, part, totalParts, picsPerPart;
protected:
    void paintEvent(QPaintEvent *);
    void makeGray(QPixmap, int );

    QString abc, root;
    QPushButton *resizeButton, *nextPage, *previousPage, *okButton, *acceptButton, *changePart, *changePicsPerPart;
    std::vector <CustomButton*> picButton;
    unsigned int x,y, picsQuantity, page, k, w, size, startPicsDisplay, endPicsDisplay;
    QLineEdit *columns, *lines, *partEditLine, *picsPerPartEditLine;
    bool isStarted;

public slots:
    void picButtons();
    void createButtons();
    void nextButton();
    void previousButton();
    void resizeBtn();
    void acceptAction();
    void restartAction();
    void changePicsPerPartAction();
private:
    Ui::MainWindow *ui;
};


#endif // MAINWINDOW_H
