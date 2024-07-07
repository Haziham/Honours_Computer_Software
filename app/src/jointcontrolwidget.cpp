#include "jointcontrolwidget.h"
#include "ui_jointcontrolwidget.h"
#include "freckle_protocol.h"
#include "FreckleProtocol.h"
#include "canQueue.h"
#include "usb2can.hpp"

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
    
}

JointControlWidget::~JointControlWidget()
{
    delete ui;
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
