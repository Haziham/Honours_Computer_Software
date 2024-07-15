#ifndef JOINTCONTROLWIDGET_H
#define JOINTCONTROLWIDGET_H

#include <QWidget>
#include "joint.h"

namespace Ui {
class JointControlWidget;
}

class JointControlWidget : public QWidget
{
    Q_OBJECT

public:
    explicit JointControlWidget(QWidget *parent = nullptr);
    ~JointControlWidget();

private:
    Ui::JointControlWidget *ui;
    // Joint testJoint;
private slots:
    void refresh_widget();




};

#endif // JOINTCONTROLWIDGET_H
