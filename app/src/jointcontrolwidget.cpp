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
    connect(ui->enableCheckbox, &QCheckBox::stateChanged, &joint, &Joint::set_enabled);
    connect(ui->enableButton, &QPushButton::clicked, &joint, &Joint::enable);
    connect(ui->disableButton, &QPushButton::clicked, &joint, &Joint::disable);


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
    ui->voltageDisplay->display(joint.statusB.voltage);
    ui->currentDisplay->display(joint.statusB.current);
    ui->externalADCDisplay->display(joint.statusB.externalADC);


    ui->enableIcon->setEnabled(joint.statusA.enabled);
    ui->errorIcon->setEnabled(joint.statusA.error);
    ui->movingIcon->setEnabled(joint.statusA.moving);
    ui->calibratedIcon->setEnabled(joint.statusA.calibrated);
    ui->calibratingIcon->setEnabled(joint.statusA.calibrating);
    ui->directionIcon->setEnabled(joint.statusA.moving);
    ui->directionIcon->setPixmap(joint.statusA.direction ? QPixmap(":/icons/rotate.svg") : QPixmap(":/icons/rotate-clockwise.svg"));
}

