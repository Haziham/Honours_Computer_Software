#include "qspinboxtimed.h"

QSpinBoxTimed::QSpinBoxTimed(QWidget *parent) : QSpinBox(parent)
{
    // Start timer on spinbox value change
    connect(this, QOverload<int>::of(&QSpinBox::valueChanged), this, &QSpinBoxTimed::disableSettable);
    connect(&m_timer, &QTimer::timeout, this, &QSpinBoxTimed::enableSettable);
    m_timer.setSingleShot(true);
}

void QSpinBoxTimed::updateSpinBox(int value)
{
    if (m_settable)
    {
        blockSignals(true);
        setValue(value);
        blockSignals(false);
    }
}

void QSpinBoxTimed::enableSettable()
{
    m_settable = true;
    qDebug() << "Settable";
}

void QSpinBoxTimed::disableSettable()
{
    m_settable = false;
    m_timer.start(3000);
}
