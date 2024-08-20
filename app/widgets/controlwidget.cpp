#include "controlwidget.h"


ControlWidget::ControlWidget(QWidget *parent)
{
    connect(&refreshTimer, &QTimer::timeout, this, &ControlWidget::refresh_widget);
}

ControlWidget::~ControlWidget()
{
}

void ControlWidget::refresh_widget()
{
}
