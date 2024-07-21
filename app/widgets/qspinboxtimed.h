#pragma once
#include <QSpinBox>
#include <QTimer>

class QSpinBoxTimed : public QSpinBox
{
public:
    explicit QSpinBoxTimed(QWidget *parent);
    void updateSpinBox(int value);

public slots:
    void enableSettable(); // Prevent the spinbox from being set by code
    void disableSettable(); // Allow the spinbox to be set by code

private:
    QTimer m_timer;
    bool m_settable = true;

    
};