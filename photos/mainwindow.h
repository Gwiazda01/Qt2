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
<<<<<<< HEAD
    QString abc;
    QPushButton *resizeButton;
    CustomButton *picButton[21];
    unsigned int x,y, picsQuantity;
    QLineEdit *columns, *lines;
public slots:
    void picButtons();
    void lineEdit();

=======

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
>>>>>>> 3d5f9023ee077e77f3f392262345152719041c72
private:
    Ui::MainWindow *ui;
};


#endif // MAINWINDOW_H
