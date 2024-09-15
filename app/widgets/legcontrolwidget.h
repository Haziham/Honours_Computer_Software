#ifndef LEGCONTROLWIDGET_H
#define LEGCONTROLWIDGET_H

#include "JointsList.h"
#include "QLeg.h"
#include "controlwidget.h"

namespace Ui {
class LegControlWidget;
}

class LegControlWidget : public ControlWidget
{
    Q_OBJECT

public:
    explicit LegControlWidget(QLeg* leg, QWidget *parent = nullptr);
    ~LegControlWidget();

    void allocate_joints();

public slots:
    void set_position();
    void enable() { m_leg->enable(); }
    void disable() { m_leg->disable(); }
    void calibrate();


private:


    Ui::LegControlWidget *ui;
    QLeg* m_leg;


    void refresh_widget() override;
};

#endif // LEGCONTROLWIDGET_H
