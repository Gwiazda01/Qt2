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
    bool pause;
    int score;
    int counter;
    enum gstate
    {
        not_started,
        started,
        game_over,
        lvl_up
    };
    enum glevel
    {
        easy,
        medium,
        hard
    };

    unsigned short int game_level;
    gstate game_state;
    glevel gm_level;



protected:
    void paintEvent(QPaintEvent *);
    void keyPressEvent(QKeyEvent *key);
    QTimer *timer;
    QPoint *point,*point2,*point3,*fruit,*point5,*a,*b,*c,*d;
    QLine *line,*line2;

    std::vector <QPoint*> snake;
    void setPossition();
    void addFruit();
    void gameOver();
    void levelUp();
    void setSnakeStartPos();
    bool isSnakeBody(int, int);


public slots:
    void TimerSlot();
};

#endif // MAINWINDOW_H
