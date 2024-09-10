#pragma once
#include <QPushButton>
#include "QLeg.h"
#include "legcontrolwidget.h"

class LegPushButton : public QPushButton
{
public:
    explicit LegPushButton(QWidget *parent);

    void set_leg(QLeg* leg) { m_leg = leg; }
    void display_legControlWidget();

private:
    QLeg* m_leg;
        
};