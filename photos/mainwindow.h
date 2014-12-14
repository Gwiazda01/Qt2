#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>

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
    //void paintEvent(QPaintEvent *);
    void createButtons();
    void makeGray(QPixmap, int );
    void createGrayPics();
    bool isGray[15];
    QPixmap *pic[15];
    QPixmap *grayPic[15];
    QString abc;
    QPushButton *picButton[15];
    QBrush *picBrush[15];
    QPalette *picPalette[15];
public slots:
    //void picButton();
    //void picButton0();
    void picButtons();
    /*void picButton2();
    void picButton3();
    void picButton4();
    void picButton5();
    void picButton6();
    void picButton7();
    void picButton8();
    void picButton9();
    void picButton10();
    void picButton11();
    void picButton12();
    void picButton13();
    void picButton14();*/

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
