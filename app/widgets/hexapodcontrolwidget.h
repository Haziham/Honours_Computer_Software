#ifndef HEXAPODCONTROLWIDGET_H
#define HEXAPODCONTROLWIDGET_H

#include <QWidget>
#include "QHexapod.h"
#include "controlwidget.h"

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


private:
    Ui::HexapodControlWidget *ui;
    QHexapod* m_hexapod;

};

#endif // HEXAPODCONTROLWIDGET_H
