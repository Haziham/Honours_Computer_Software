#ifndef SPINSLIDER_H
#define SPINSLIDER_H

#include <QWidget>

namespace Ui {
class SpinSlider;
}

class SpinSlider : public QWidget
{
    Q_OBJECT

public:
    explicit SpinSlider(QWidget *parent = nullptr);
    ~SpinSlider();

    void set_minimum(int min);
    void set_maximum(int max);
    void set_value(int value);
    void set_label(QString string);
    int value();

signals:
    void valueChanged(int value);

private:
    Ui::SpinSlider *ui;
};

#endif // SPINSLIDER_H
