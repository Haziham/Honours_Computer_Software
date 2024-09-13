
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "joint.h"
// #include "usb2can.hpp"
#include "can.hpp"
#include "legcontrolwidget.h"
#include "hexapodcontrolwidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE




class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();



private slots:
    void displayConnectedDevices();


private:
    Ui::MainWindow *ui;

    QHexapod hexapod;
    HexapodControlWidget hexapodControlWidget = HexapodControlWidget(&hexapod);    
    QLeg legs[6];


};
#endif // MAINWINDOW_H
