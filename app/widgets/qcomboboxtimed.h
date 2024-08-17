#pragma once
#include <QComboBox>
#include <QTimer>

class QComboBoxTimed : public QComboBox
{
public:
    explicit QComboBoxTimed(QWidget *parent);
    void updateComboBox(int value);

public slots:
    void enableSettable(); // Prevent the spinbox from being set by code
    void disableSettable(); // Allow the spinbox to be set by code

private:
    QTimer m_timer;
    bool m_settable = true;

    
};