#include "mainwindow.h"
#include <QApplication>
#include <Windows.h>

int main(int argc, char *argv[])
{
    // Enable console output when developing on Windows
    #ifdef _WIN32
    if (AttachConsole(ATTACH_PARENT_PROCESS)) {
        freopen("CONOUT$", "w", stdout);
        freopen("CONOUT$", "w", stderr);
        qDebug() << "\n";
    }
    #endif


    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
