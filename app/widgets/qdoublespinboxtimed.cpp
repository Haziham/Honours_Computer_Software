#include "qdoublespinboxtimed.h"

QDoubleSpinBoxTimed::QDoubleSpinBoxTimed(QWidget *parent) : QDoubleSpinBox(parent)
{
    // Start timer on spinbox value change
    connect(this, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &QDoubleSpinBoxTimed::disableSettable);
    connect(&m_timer, &QTimer::timeout, this, &QDoubleSpinBoxTimed::enableSettable);
    m_timer.setSingleShot(true);
}

void QDoubleSpinBoxTimed::updateSpinBox(double value)
{
    if (m_settable)
    {
        blockSignals(true);
        setValue(value);
        blockSignals(false);
    }
}

void QDoubleSpinBoxTimed::enableSettable()
{
    m_settable = true;
}

void QDoubleSpinBoxTimed::disableSettable()
{
    m_settable = false;
    m_timer.start(3000);
}
