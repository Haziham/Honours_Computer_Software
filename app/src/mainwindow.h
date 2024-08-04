
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "joint.h"
// #include "usb2can.hpp"
#include "can.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE




class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QList<QJoint> joints;
    QThread *serialThread = new QThread();


private slots:
    void displayConnectedDevices();

private:
    Ui::MainWindow *ui;



};
#endif // MAINWINDOW_H
