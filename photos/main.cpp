#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    int currentExitCode = 0;

    MainWindow *w;

        QApplication a(argc, argv);
        w = new MainWindow();
        w->showMaximized();
        a.exec();
    //while( currentExitCode == MainWindow::EXIT_CODE_REBOOT);

    return currentExitCode;
}
//*****************************************
