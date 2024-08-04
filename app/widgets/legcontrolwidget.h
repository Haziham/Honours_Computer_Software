#ifndef LEGCONTROLWIDGET_H
#define LEGCONTROLWIDGET_H

#include <QWidget>
#include "JointsList.h"
#include "QLeg.h"

namespace Ui {
class LegControlWidget;
}

class LegControlWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LegControlWidget(QWidget *parent = nullptr);
    ~LegControlWidget();

    void allocate_joints();

public slots:


private:
    Ui::LegControlWidget *ui;
    JointsList m_joints;
    QLeg m_leg;
};

#endif // LEGCONTROLWIDGET_H
