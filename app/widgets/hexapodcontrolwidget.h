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

    QSet<int> pressedKeys;

public:
    explicit HexapodControlWidget(QHexapod* hexapod, QWidget *parent = nullptr);
    ~HexapodControlWidget();

    void refresh_widget() override;

    void showEvent(QShowEvent *event) override;

    // enum of leg combinations
    enum LegCombination
    {
        ALL,
        ODD,
        EVEN
    };

    int legCombinationHistory[3][3] = {
        {50, 0, 0},
        {50, 0, 0},
        {50, 0, 0}};
    

public slots:
    void set_globalPosition();
    void set_stepSettings();

    void move(QPointF direction);
    void spin(QPointF direction);
    void tilt(QPointF direction);
    void newLegCombination(int combination);
    void saveLegCombination(LegCombination combination);
    void loadLegCombination(LegCombination combination);;
    void update_hexapodPosition();




private:
    Ui::HexapodControlWidget *ui;
    QHexapod* m_hexapod;
    enum LegCombination m_legCombination = ALL;

    void configure_virtualPad(QVirtualPad* pad);

protected:
void keyPressEvent(QKeyEvent *event) override {
    pressedKeys.insert(event->key());
    determineDirection();
}

void keyReleaseEvent(QKeyEvent *event) override {
    pressedKeys.remove(event->key());
    determineDirection();
}


    void determineDirection(); 
};

#endif // HEXAPODCONTROLWIDGET_H
