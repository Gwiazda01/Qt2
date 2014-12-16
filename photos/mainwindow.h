#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <QLineEdit>

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
    void createGrayPics();
    bool isGray[15];
    QPixmap *pic[15];
    QPixmap *grayPic[15];
    QPushButton *picButton[15];
    QBrush *picBrush[15];
    QPalette *picPalette[15];
    int x,y;
    QLineEdit *columns, *lines;
public slots:
    void picButtons();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
