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
    explicit LegControlWidget(QLeg* leg, QWidget *parent = nullptr);
    ~LegControlWidget();

    void allocate_joints();

public slots:
    void set_position();


private:
    Ui::LegControlWidget *ui;
    QLeg* m_leg;
};

#endif // LEGCONTROLWIDGET_H
