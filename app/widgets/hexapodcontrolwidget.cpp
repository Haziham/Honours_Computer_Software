#include "hexapodcontrolwidget.h"
#include "ui_hexapodcontrolwidget.h"

HexapodControlWidget::HexapodControlWidget(QHexapod* hexapod, QWidget *parent)
    : ControlWidget(parent)
    , ui(new Ui::HexapodControlWidget)
{
    ui->setupUi(this);
    m_hexapod = hexapod;

    ui->leg0Button->set_leg(&hexapod->leg0);
    ui->leg1Button->set_leg(&hexapod->leg1);
    ui->leg2Button->set_leg(&hexapod->leg2);
    ui->leg3Button->set_leg(&hexapod->leg3);
    ui->leg4Button->set_leg(&hexapod->leg4);
    ui->leg5Button->set_leg(&hexapod->leg5);

    connect(ui->calibrateButton, &QPushButton::clicked, m_hexapod, &QHexapod::calibrate);

    start_refresh_timer();

}

HexapodControlWidget::~HexapodControlWidget()
{
    delete ui;
}

void HexapodControlWidget::refresh_widget()
{
    ui->leg0ForceDisplay->display(m_hexapod->leg0.get_force());
    ui->leg1ForceDisplay->display(m_hexapod->leg1.get_force());
    ui->leg2ForceDisplay->display(m_hexapod->leg2.get_force());
    ui->leg3ForceDisplay->display(m_hexapod->leg3.get_force());
    ui->leg4ForceDisplay->display(m_hexapod->leg4.get_force());
    ui->leg5ForceDisplay->display(m_hexapod->leg5.get_force());


}
