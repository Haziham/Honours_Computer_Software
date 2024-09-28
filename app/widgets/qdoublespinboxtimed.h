#pragma once
#include <QDoubleSpinBox>
#include <QTimer>

class QDoubleSpinBoxTimed : public QDoubleSpinBox
{
public:
    explicit QDoubleSpinBoxTimed(QWidget *parent);
    void updateSpinBox(double value);

public slots:
    void enableSettable(); // Prevent the spinbox from being set by code
    void disableSettable(); // Allow the spinbox to be set by code

private:
    QTimer m_timer;
    bool m_settable = true;

    
};