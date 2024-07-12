#include "jointcontrolwidget.h"
#include "ui_jointcontrolwidget.h"
#include "freckle_protocol.h"
#include "FreckleProtocol.h"
#include "canQueue.h"
#include "usb2can.hpp"
#include <QTimer>
#include "joint.h"

JointControlWidget::JointControlWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::JointControlWidget)
{
    ui->setupUi(this);

    connect(ui->commandValueSlider, &QScrollBar::valueChanged, this, &JointControlWidget::send_joint_command);

    for (int i = 0; i < CMD_END_ENUM; i++)
    {
        ui->commandModeSelector->addItem(commandModes_EnumLabel(i));
    }

    ui->commandModeSelector->setCurrentIndex(0);
    ui->errorIcon->setPixmap(QPixmap(":/icons/exclamation-circle.svg"));
    ui->errorIcon->setEnabled(true);

    // set up timer to refresh widet 5hz
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &JointControlWidget::refresh_widget);
    timer->start(200);
}

JointControlWidget::~JointControlWidget()
{
    delete ui;
}

void JointControlWidget::refresh_widget()
{
    qDebug() << "Refreshing widget";    
    // print tghe 3 values
    qDebug() << "Voltage: " << joint.statusB.voltage;
    qDebug() << "Current: " << joint.statusB.current;
    qDebug() << "External ADC: " << joint.statusB.externalADC;
    ui->voltageDisplay->display(joint.statusB.voltage);
    ui->currentDisplay->display(joint.statusB.current);
    ui->externalADCDisplay->display(joint.statusB.externalADC);
}

uint32_t map_value(uint32_t x, uint32_t in_min, uint32_t in_max, uint32_t out_min, uint32_t out_max) {
    return out_min +  (out_max - out_min) * ((double) (x - in_min) / (in_max - in_min));
}

void JointControlWidget::send_joint_command(int value)
{
    JointCommand_t jointCommand;
    jointCommand.mode = ui->commandModeSelector->currentIndex();
    jointCommand.value = value;

    switch (jointCommand.mode)
    {
    case CMD_PWM:
        jointCommand.value = map_value(abs(value), 0, 100, 0, 65535);
        qDebug() << value;
        if (value < 0)
        {
            jointCommand.direction = DIR_BACKWARD;
        } else {
            jointCommand.direction = DIR_FORWARD;
        }
        break;
    case CMD_POSITION:
        // jointCommand.value = map(jointCommand.value, -50, 50, -1000, 1000);
        break;
    case CMD_VELOCITY:
        // jointCommand.value = map(jointCommand.value, -50, 50, -1000, 1000);
        break;
    default:
        jointCommand.value = 0;
    }

    CAN_Message_t message;
    encodeJointCommandPacketStructure(&message, &jointCommand);
    usb2can.send_CAN_message(&message);
}
