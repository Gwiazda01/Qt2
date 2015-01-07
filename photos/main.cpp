#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    int currentExitCode = 0;
    QApplication *a;
    MainWindow *w;
    do
    {
        a = new QApplication(argc, argv);
        w = new MainWindow();
        w->showMaximized();
        currentExitCode = a->exec();
        delete a;
        //delete w;
    }
    while( currentExitCode == MainWindow::EXIT_CODE_REBOOT);

    return currentExitCode;
}
//*****************************************
