#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
<<<<<<< HEAD
    int currentExitCode = 0;

    MainWindow *w;

        QApplication a(argc, argv);
        w = new MainWindow();
        w->showMaximized();
        a.exec();
    //while( currentExitCode == MainWindow::EXIT_CODE_REBOOT);
=======
    QApplication a(argc, argv);
    MainWindow w;
    w.showMaximized();
>>>>>>> 0560799f253d376cd92e8ef30b12ffaafd2b7628

    return a.exec();
}
