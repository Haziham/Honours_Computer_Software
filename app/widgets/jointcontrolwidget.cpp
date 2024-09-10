#include "jointcontrolwidget.h"
#include "ui_jointcontrolwidget.h"
#include "freckle_protocol.h"
#include "FreckleProtocol.h" 
#include "canQueue.h"
#include "can.hpp"
#include <QTimer>

JointControlWidget::JointControlWidget(QJoint* temp, QWidget *parent)
    : ControlWidget(parent)
    , ui(new Ui::JointControlWidget)
    , joint(temp)
{
    ui->setupUi(this);

    for (int i = 0; i < CMD_END_ENUM; i++)
    {
        ui->commandModeSelector->addItem(QString(commandModes_EnumLabel(i)).remove("CMD_"));
    }
    ui->commandModeSelector->enableSettable();

    for (int i = 0; i < JOINT_END_ENUM; i++)
    {
        ui->jointTypeSelector->addItem(QString(jointTypes_EnumLabel(i)).remove("JOINT_"));
    }
    ui->jointTypeSelector->enableSettable();

    // If joint is lost from list, delete this widget
    connect(joint, &QJoint::jointDestroyed, this, &JointControlWidget::deleteLater);

    // connect(ui->commandModeSelector, &QComboBox::currentIndexChanged, joint, &QJoint::set_modeSlot);
    connect(ui->enableButton, &QPushButton::clicked, joint, &QJoint::enableSlot);
    connect(ui->disableButton, &QPushButton::clicked, joint, &QJoint::disableSlot);


    connect(ui->jointTypeSelector, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &JointControlWidget::sendJointSettings);
    connect(ui->legNumberInput, QOverload<int>::of(&QSpinBox::valueChanged), this, &JointControlWidget::sendJointSettings);
    connect(ui->gearRatioInput, QOverload<int>::of(&QSpinBox::valueChanged), this, &JointControlWidget::sendJointSettings);
    connect(ui->nodeIdInput, QOverload<int>::of(&QSpinBox::valueChanged), this, &JointControlWidget::sendJointSettings);
    connect(ui->telemetryPeriodInput, QOverload<int>::of(&QSpinBox::valueChanged), this, &JointControlWidget::sendTelemetrySettings);
    connect(ui->commandModeSelector, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &JointControlWidget::sendCommandSettings);

    connect(ui->proportionalGainInput, QOverload<int>::of(&QSpinBox::valueChanged), this, &JointControlWidget::sendControlSettings);
    connect(ui->derivativeGainInput, QOverload<int>::of(&QSpinBox::valueChanged), this, &JointControlWidget::sendControlSettings);
    connect(ui->integralGainInput, QOverload<int>::of(&QSpinBox::valueChanged), this, &JointControlWidget::sendControlSettings);

    connect(ui->minAngleInput, QOverload<int>::of(&QSpinBox::valueChanged), this, &JointControlWidget::sendCalibrationSettings);
    connect(ui->maxAngleInput, QOverload<int>::of(&QSpinBox::valueChanged), this, &JointControlWidget::sendCalibrationSettings);
    connect(ui->angleOffsetInput, QOverload<int>::of(&QSpinBox::valueChanged), this, &JointControlWidget::sendCalibrationSettings);

    connect(ui->commandValueSlider, &QScrollBar::valueChanged, joint, &QJoint::send_commandSlot);
    connect(ui->commandValueSlider, &QScrollBar::valueChanged, ui->commandDisplay, QOverload<int>::of(&QLCDNumber::display));
    connect(ui->commandValueInput, QOverload<int>::of(&QSpinBox::valueChanged), joint, &QJoint::send_commandSlot);
    connect(ui->commandValueInput, QOverload<int>::of(&QSpinBox::valueChanged), ui->commandDisplay, QOverload<int>::of(&QLCDNumber::display));




    // ui->commandModeSelector->setCurrentIndex(0);
    ui->errorIcon->setPixmap(QPixmap(":/icons/exclamation-circle.svg"));
    ui->errorIcon->setEnabled(true);

    //  If node id is 1F this is a broadcast node.
    if (joint->get_nodeId() != 0x1F)
    {
        start_refresh_timer();
    }

}

JointControlWidget::~JointControlWidget()
{
    delete ui;
}

int map_value2(int x, int in_min, int in_max, int out_min, int out_max) {
    return out_min +  (out_max - out_min) * ((double) (x - in_min) / (in_max - in_min));
}

void JointControlWidget::tempFunctio(QJoint *tempParam)
{

}

void JointControlWidget::tempDisplay(int value)
{
    int commandValue;
    switch (joint->settings.command.mode)
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
    jointSettings.jointType = ui->jointTypeSelector->currentIndex();
    jointSettings.legNumber = ui->legNumberInput->value();
    jointSettings.gearRatio = ui->gearRatioInput->value();
    jointSettings.nodeId = ui->nodeIdInput->value();

    joint->send_jointSettings(jointSettings);
}

void JointControlWidget::sendTelemetrySettings()
{
    TelemetrySettings_t telemetrySettings;
    telemetrySettings.transmitPeriod = ui->telemetryPeriodInput->value();

    joint->send_telemetrySettings(telemetrySettings);
}

void JointControlWidget::sendCommandSettings()
{
    CommandSettings_t commandSettings;
    commandSettings.mode = ui->commandModeSelector->currentIndex();
    joint->send_commandSettings(commandSettings);

    switch (joint->settings.command.mode)
    {
    case CMD_PWM:
        ui->commandValueInput->setMaximum(65535);
        ui->commandValueInput->setMinimum(-65535);   
        break;
    case CMD_POSITION:
        ui->commandValueInput->setMaximum(1800);
        ui->commandValueInput->setMinimum(-1800);
        break;
    case CMD_VELOCITY:
    case CMD_TORQUE:
    default:
        break;
    }
}

void JointControlWidget::sendControlSettings()
{
    ControlSettings_t controlSettings;
    controlSettings.pGain = ui->proportionalGainInput->value();
    controlSettings.dGain = ui->derivativeGainInput->value();
    controlSettings.iGain = ui->integralGainInput->value();

    joint->send_controlSettings(controlSettings);
}

void JointControlWidget::sendCalibrationSettings()
{
    CalibrationSettings_t calibrationSettings;
    calibrationSettings.minAngle = ui->minAngleInput->value();
    calibrationSettings.maxAngle = ui->maxAngleInput->value();
    calibrationSettings.angleOffset = ui->angleOffsetInput->value();

    joint->send_calibrationSettings(calibrationSettings);
}

void JointControlWidget::updateInputExtremes()
{
    switch (joint->settings.command.mode)
    {
    case CMD_PWM:
        ui->commandValueInput->setMaximum(65535);
        ui->commandValueInput->setMinimum(-65535);
        ui->commandValueSlider->setMaximum(65535);
        ui->commandValueSlider->setMinimum(-65535);

        break;
    case CMD_POSITION:
        ui->commandValueInput->setMaximum(1800);
        ui->commandValueInput->setMinimum(-1800);
        ui->commandValueSlider->setMaximum(1800);
        ui->commandValueSlider->setMinimum(-1800);
    
        break;
    case CMD_VELOCITY:
    case CMD_TORQUE:
    default:
        break;
    }
}

void JointControlWidget::refresh_widget()
{
    ui->voltageDisplay->display(joint->statusB.voltage);
    ui->currentDisplay->display(joint->statusB.current);
    ui->externalADCDisplay->display(joint->statusB.externalADC);
    ui->debugDisplay->display(static_cast<int>(joint->statusC.debugValue));
    ui->angularPositionDisplay->display(static_cast<int>(joint->statusA.position));
    ui->angularVelocityDisplay->display(static_cast<int>(joint->statusA.velocity));




    ui->enableIcon->setEnabled(joint->statusA.enabled);
    ui->errorIcon->setEnabled(joint->statusA.error);
    ui->movingIcon->setEnabled(joint->statusA.moving);
    ui->calibratedIcon->setEnabled(joint->statusA.calibrated);
    ui->calibratingIcon->setEnabled(joint->statusA.calibrating);
    ui->directionIcon->setEnabled(joint->statusA.moving);
    ui->directionIcon->setPixmap(joint->statusA.direction ? QPixmap(":/icons/rotate.svg") : QPixmap(":/icons/rotate-clockwise.svg"));


    ui->commandModeSelector->updateComboBox(joint->settings.command.mode);
    // display mode

    ui->jointTypeSelector->updateComboBox(joint->settings.joint.jointType);
    ui->legNumberInput->updateSpinBox(joint->settings.joint.legNumber);
    ui->gearRatioInput->updateSpinBox(joint->settings.joint.gearRatio);
    ui->nodeIdInput->updateSpinBox(joint->settings.joint.nodeId);
    ui->telemetryPeriodInput->updateSpinBox(joint->settings.telemetry.transmitPeriod);

    ui->minAngleInput->updateSpinBox(joint->settings.calibration.minAngle);
    ui->maxAngleInput->updateSpinBox(joint->settings.calibration.maxAngle);
    ui->angleOffsetInput->updateSpinBox(joint->settings.calibration.angleOffset);

    ui->proportionalGainInput->updateSpinBox(joint->settings.control.pGain);
    ui->derivativeGainInput->updateSpinBox(joint->settings.control.dGain);
    ui->integralGainInput->updateSpinBox(joint->settings.control.iGain);

    updateInputExtremes();
}

