#include "jointcontrolwidget.h"
#include "ui_jointcontrolwidget.h"
#include "freckle_protocol.h"
#include "FreckleProtocol.h" 
#include "canQueue.h"
#include "can.hpp"
#include <QTimer>

JointControlWidget::JointControlWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::JointControlWidget)
{
    ui->setupUi(this);

    connect(ui->commandValueSlider, &QScrollBar::valueChanged, &joint, &Joint::send_command);
    connect(ui->commandModeSelector, &QComboBox::currentIndexChanged, &joint, &Joint::set_mode);
    connect(ui->enableButton, &QPushButton::clicked, &joint, &Joint::enable);
    connect(ui->disableButton, &QPushButton::clicked, &joint, &Joint::disable);
    connect(ui->commandValueSlider, &QScrollBar::valueChanged, this, &JointControlWidget::tempDisplay);


    connect(ui->jointTypeInput, QOverload<int>::of(&QSpinBox::valueChanged), this, &JointControlWidget::sendJointSettings);
    connect(ui->legNumberInput, QOverload<int>::of(&QSpinBox::valueChanged), this, &JointControlWidget::sendJointSettings);
    connect(ui->gearRatioInput, QOverload<int>::of(&QSpinBox::valueChanged), this, &JointControlWidget::sendJointSettings);
    connect(ui->minAngleInput, QOverload<int>::of(&QSpinBox::valueChanged), this, &JointControlWidget::sendJointSettings);
    connect(ui->maxAngleInput, QOverload<int>::of(&QSpinBox::valueChanged), this, &JointControlWidget::sendJointSettings);
    connect(ui->nodeIdInput, QOverload<int>::of(&QSpinBox::valueChanged), this, &JointControlWidget::sendJointSettings);
    connect(ui->telemetryPeriodInput, QOverload<int>::of(&QSpinBox::valueChanged), this, &JointControlWidget::sendTelemetrySettings);
    connect(ui->commandModeSelector, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &JointControlWidget::sendCommandSettings);

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

int map_value2(int x, int in_min, int in_max, int out_min, int out_max) {
    return out_min +  (out_max - out_min) * ((double) (x - in_min) / (in_max - in_min));
}

void JointControlWidget::tempDisplay(int value)
{
    int commandValue;
    switch (joint.settings.command.mode)
    {
    case CMD_PWM:
        commandValue = map_value2(value, -100, 100, -65535, 65535);
        break;
    case CMD_POSITION:
        commandValue = map_value2(value, -100, 100, -1800, 1800);
        break;
    case CMD_VELOCITY:
    case CMD_TORQUE:
    default:
        commandValue = 0;
        break;
    }
    ui->commandDisplay->display(commandValue);

}

void JointControlWidget::sendJointSettings()
{
    JointSettings_t jointSettings;
    jointSettings.jointType = ui->jointTypeInput->value();
    jointSettings.legNumber = ui->legNumberInput->value();
    jointSettings.gearRatio = ui->gearRatioInput->value();
    jointSettings.minAngle = ui->minAngleInput->value();
    jointSettings.maxAngle = ui->maxAngleInput->value();
    jointSettings.nodeId = ui->nodeIdInput->value();

    joint.send_jointSettings(jointSettings);
}

void JointControlWidget::sendTelemetrySettings()
{
    TelemetrySettings_t telemetrySettings;
    telemetrySettings.transmitPeriod = ui->telemetryPeriodInput->value();

    joint.send_telemetrySettings(telemetrySettings);
}

void JointControlWidget::sendCommandSettings()
{
    CommandSettings_t commandSettings;
    commandSettings.mode = ui->commandModeSelector->currentIndex();

    joint.send_commandSettings(commandSettings);
}

void JointControlWidget::refresh_widget()
{
    ui->voltageDisplay->display(joint.settings.statusB.voltage);
    ui->currentDisplay->display(joint.settings.statusB.current);
    ui->externalADCDisplay->display(joint.settings.statusB.externalADC);
    ui->debugDisplay->display(static_cast<int>(joint.settings.statusC.debugValue));
    ui->angularPositionDisplay->display(static_cast<int>(joint.settings.statusA.position));
    ui->angularVelocityDisplay->display(static_cast<int>(joint.settings.statusA.velocity));




    ui->enableIcon->setEnabled(joint.settings.statusA.enabled);
    ui->errorIcon->setEnabled(joint.settings.statusA.error);
    ui->movingIcon->setEnabled(joint.settings.statusA.moving);
    ui->calibratedIcon->setEnabled(joint.settings.statusA.calibrated);
    ui->calibratingIcon->setEnabled(joint.settings.statusA.calibrating);
    ui->directionIcon->setEnabled(joint.settings.statusA.moving);
    ui->directionIcon->setPixmap(joint.settings.statusA.direction ? QPixmap(":/icons/rotate.svg") : QPixmap(":/icons/rotate-clockwise.svg"));


    ui->commandModeSelector->setCurrentIndex(joint.settings.command.mode);

    ui->jointTypeInput->updateSpinBox(joint.settings.joint.jointType);
    ui->legNumberInput->updateSpinBox(joint.settings.joint.legNumber);
    ui->gearRatioInput->updateSpinBox(joint.settings.joint.gearRatio);
    ui->minAngleInput->updateSpinBox(joint.settings.joint.minAngle);
    ui->maxAngleInput->updateSpinBox(joint.settings.joint.maxAngle);
    ui->nodeIdInput->updateSpinBox(joint.settings.joint.nodeId);
    ui->telemetryPeriodInput->updateSpinBox(joint.settings.telemetry.transmitPeriod);
}

