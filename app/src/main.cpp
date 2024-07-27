#include "jointcontrolwidget.h"
#include "mainwindow.h"
#include <QApplication>
#include <QTimer>


#ifdef _WIN32
    #include <Windows.h>
#endif



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
    // Joint * tempJoint = new Joint(1);
    // JointControlWidget jointControlWidget(tempJoint);
    // jointControlWidget.show();

    // Joint joint = Joint(1);
    // joint.display.show();
    return a.exec();
}
