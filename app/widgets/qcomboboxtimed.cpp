#include "qcomboboxtimed.h"

QComboBoxTimed::QComboBoxTimed(QWidget *parent) : QComboBox(parent)
{
    // Start timer on spinbox value change
    connect(this, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &QComboBoxTimed::disableSettable);
    connect(&m_timer, &QTimer::timeout, this, &QComboBoxTimed::enableSettable);
    m_timer.setSingleShot(true);
}

void QComboBoxTimed::updateComboBox(int value)
{
    if (m_settable)
    {
        blockSignals(true);
        setCurrentIndex(value);
        blockSignals(false);
    }
}

void QComboBoxTimed::enableSettable()
{
    m_settable = true;
}

void QComboBoxTimed::disableSettable()
{
    m_settable = false;
    m_timer.start(3000);
}
