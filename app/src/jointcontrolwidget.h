#ifndef JOINTCONTROLWIDGET_H
#define JOINTCONTROLWIDGET_H

#include <QWidget>
// #include "joint.h"

class Joint;

namespace Ui {
class JointControlWidget;
}

class JointControlWidget : public QWidget
{
    Q_OBJECT

public:
    explicit JointControlWidget(Joint* temp, QWidget *parent = nullptr);
    ~JointControlWidget();

private:
    Ui::JointControlWidget *ui;
    Joint* joint;

    void tempFunctio(Joint* tempParam);


private slots:
    void refresh_widget();

    void tempDisplay(int value);
    void sendJointSettings();
    void sendTelemetrySettings();
    void sendCommandSettings();
    void sendControlSettings();
    void sendCalibrationSettings();

    void updateInputExtremes();


};

#endif // JOINTCONTROLWIDGET_H
