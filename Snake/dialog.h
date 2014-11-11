#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsView>
#include <QTimer>
#include <QKeyEvent>
#include <ctime>
#include <vector>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private:
    Ui::Dialog *ui;
    QGraphicsLineItem *fruit;
    QGraphicsScene *scene;
    QGraphicsRectItem *rect;
    QTimer *timer;
    QGraphicsEllipseItem *point, *point1;
    std::vector <QGraphicsLineItem*> snake;
    struct roznice
    {
        std::vector<signed> dx;
        std::vector<signed> dy;
    };

    enum sterowanie
    {
        forward, backward, left, right
    };
    sterowanie kierunek;
    roznice diff;

    void keyPressEvent(QKeyEvent *key);
    void addFruit();
    void obl_roz();
public slots:
    void TimerSlot();
};

#endif // DIALOG_H
