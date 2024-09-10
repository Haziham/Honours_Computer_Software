#include "legpushbutton.h"

LegPushButton::LegPushButton(QWidget *parent) : QPushButton(parent)
{
    connect(this, &QPushButton::clicked, this, &LegPushButton::display_legControlWidget);
}

void LegPushButton::display_legControlWidget()
{
    if (m_leg != nullptr)
    {
        LegControlWidget* legControlWidget = new LegControlWidget(m_leg);
        legControlWidget->show();
    }
}
