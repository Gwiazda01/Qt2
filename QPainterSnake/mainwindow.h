#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <vector>
#include <time.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    enum steering
    {
        forward,
        backward,
        left,
        right
    };
    steering direction;
    std::vector <int> snake_pos_x;
    std::vector <int> snake_pos_y;
    bool fruit_exist;
    bool game;
    bool start;
    bool pause;
    int score;


protected:
    void paintEvent(QPaintEvent *);
    void keyPressEvent(QKeyEvent *key);
    QTimer *timer;
    QPoint *point,*point2,*point3,*fruit,*point5;

    std::vector <QPoint*> snake;
    void setPossition();
    void addFruit();
    void gameOver();

public slots:
    void TimerSlot();
};

#endif // MAINWINDOW_H
