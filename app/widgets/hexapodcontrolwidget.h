#ifndef HEXAPODCONTROLWIDGET_H
#define HEXAPODCONTROLWIDGET_H

#include <QWidget>
#include "QHexapod.h"
#include "controlwidget.h"
#include "qvirtualpad.h"

namespace Ui {
class HexapodControlWidget;
}

class HexapodControlWidget : public ControlWidget
{
    Q_OBJECT

public:
    explicit HexapodControlWidget(QHexapod* hexapod, QWidget *parent = nullptr);
    ~HexapodControlWidget();

    void refresh_widget() override;

    void showEvent(QShowEvent *event) override;

public slots:
    void set_globalPosition();
    void set_stepSettings();

    void move(QPointF direction);
    void spin(QPointF direction);
    void tilt(QPointF direction);
    void update_hexapodPosition();


private:
    Ui::HexapodControlWidget *ui;
    QHexapod* m_hexapod;

    void configure_virtualPad(QVirtualPad* pad);

};

#endif // HEXAPODCONTROLWIDGET_H
