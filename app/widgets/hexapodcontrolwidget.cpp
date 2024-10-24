#include "hexapodcontrolwidget.h"
#include "ui_hexapodcontrolwidget.h"
#include <math.h>

HexapodControlWidget::HexapodControlWidget(QHexapod* hexapod, QWidget *parent)
    : ControlWidget(parent)
    , ui(new Ui::HexapodControlWidget)
{
    ui->setupUi(this);
    m_hexapod = hexapod;

    this->setFocus();
    setFocusPolicy(Qt::StrongFocus);

    ui->leg0Button->set_leg(&hexapod->leg0);
    ui->leg1Button->set_leg(&hexapod->leg1);
    ui->leg2Button->set_leg(&hexapod->leg2); ui->leg3Button->set_leg(&hexapod->leg3);
    ui->leg4Button->set_leg(&hexapod->leg4);
    ui->leg5Button->set_leg(&hexapod->leg5);

    connect(ui->calibrateButton, &QPushButton::clicked, m_hexapod, &QHexapod::start_calibration);
    connect(ui->allocateJointsButton, &QPushButton::clicked, m_hexapod, &QHexapod::allocate_joints);
    connect(ui->enableButton, &QPushButton::clicked, m_hexapod, &QHexapod::enable);
    connect(ui->disableButton, &QPushButton::clicked, m_hexapod, &QHexapod::disable);

    // ui->heightInput->set_label("Height");
    // ui->directionAngleInput->set_label("Direction Angle");
    ui->globalXInput->set_label("Global X");
    ui->globalXInput->set_minimum(0);
    ui->globalXInput->set_value(160);
    ui->globalXInput->set_maximum(320);
    ui->globalYInput->set_label("Global Y");
    ui->globalYInput->set_minimum(-160);
    ui->globalYInput->set_maximum(160);
    ui->globalZInput->set_label("Global Z");
    ui->globalZInput->set_minimum(-160);
    ui->globalZInput->set_maximum(160);

    ui->stepDirectionAngle->set_label("Direction Angle");
    ui->stepDirectionAngle->set_maximum(3600);
    ui->stepDirectionAngle->set_minimum(0);
    ui->stepDirectionAngle->set_value(0);

    ui->stepHeightOffset->set_label("Step Height Offset");
    ui->stepHeightOffset->set_maximum(300);
    ui->stepHeightOffset->set_minimum(-300);
    ui->stepHeightOffset->set_value(0);

    ui->stepSpeed->set_label("Walking Speed (mm/s)");
    ui->stepSpeed->set_maximum(300);
    ui->stepSpeed->set_minimum(0);
    ui->stepSpeed->set_value(50);

    ui->stepRadius->set_label("Step Radius");
    ui->stepRadius->set_maximum(300);
    ui->stepRadius->set_minimum(0);
    ui->stepRadius->set_value(25);


    ui->stepHeightOffset->set_value(-60);
    // ui->heightInput->set_value(-60);


    ui->legCombinationSelect->addItem("All");
    ui->legCombinationSelect->addItem("Odd");
    ui->legCombinationSelect->addItem("Even");
    connect(ui->legCombinationSelect, &QComboBox::currentIndexChanged, this, &HexapodControlWidget::newLegCombination);
    // ui->stepTime->set_label("Step Time");
    // ui->stepTime->set_maximum(20000);
    // ui->stepTime->set_minimum(0);

    // connect(ui->stepTime, &SpinSlider::valueChanged, m_hexapod, &QHexapod::step);

    connect(ui->globalXInput, SIGNAL(valueChanged(int)), this, SLOT(set_globalPosition()));
    connect(ui->globalYInput, SIGNAL(valueChanged(int)), this, SLOT(set_globalPosition()));
    connect(ui->globalZInput, SIGNAL(valueChanged(int)), this, SLOT(set_globalPosition()));


    connect(ui->stepDirectionAngle, SIGNAL(valueChanged(int)), this, SLOT(set_stepSettings()));
    connect(ui->stepHeightOffset, SIGNAL(valueChanged(int)), this, SLOT(set_stepSettings()));
    connect(ui->stepSpeed, SIGNAL(valueChanged(int)), this, SLOT(set_stepSettings()));
    connect(ui->stepRadius, SIGNAL(valueChanged(int)), this, SLOT(set_stepSettings()));

// int test;

    // connect(ui->stepButton, &QPushButton::clicked, m_hexapod, &QHexapod::start_stepping);


    configure_virtualPad(ui->movePadInput);
    configure_virtualPad(ui->spinPadInput);
    configure_virtualPad(ui->tildPadInput);

    connect(ui->movePadInput, &QVirtualPad::positionUpdate, this, &HexapodControlWidget::move);
    connect(ui->heightInput_2, &QSlider::valueChanged, ui->stepHeightOffset, &SpinSlider::set_value);
    connect(ui->footWidthInput, SIGNAL(valueChanged(int)), this, SLOT(update_hexapodPosition()));

    connect(ui->startControlButton, &QPushButton::clicked, m_hexapod, &QHexapod::start_moving);
    connect(ui->stopControlButton, &QPushButton::clicked, m_hexapod, &QHexapod::stop_moving);
    connect(ui->idleButton, &QPushButton::clicked, m_hexapod, &QHexapod::toggle_idle);


    connect(ui->powerOffButton, &QPushButton::clicked, m_hexapod, &QHexapod::power_off);
    connect(ui->powerOnButton, &QPushButton::clicked, m_hexapod, &QHexapod::power_on);

    ui->tildPadInput->setMomentary(false);


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

void HexapodControlWidget::showEvent(QShowEvent *event)
{
    QWidget::showEvent(event);  // Call base class implementation
    m_hexapod->allocate_joints();
}

void HexapodControlWidget::set_stepSettings()
{
    m_hexapod->settings.walking.direction = ui->stepDirectionAngle->value();
    m_hexapod->settings.position.height = ui->stepHeightOffset->value();
    m_hexapod->settings.walking.speed = ui->stepSpeed->value();
    m_hexapod->settings.step.radius = ui->stepRadius->value();
    m_hexapod->update_offsets();
}

void HexapodControlWidget::move(QPointF direction)
{
    float x = direction.x();
    float y = direction.y();
    uint16_t directionAngle = (atan2(y, x) * 180.0f / M_PI) * 10 + 1800;
    float speed = sqrt(x*x + y*y)/sqrt(2.0f);

    ui->stepDirectionAngle->set_value(directionAngle);
    ui->stepSpeed->set_value(speed * 400);
    
    // printf("x*x: %f, y*y: %f\n", x*x, y*y);
    // printf("sqrt(x*x + y*y): %f\n", sqrt(x*x + y*y));
    // printf("sqrt(x*x + y*y)/sqrt(2.0f): %f\n", sqrt(x*x + y*y)/sqrt(2.0f));
}

void HexapodControlWidget::tilt(QPointF direction)
{
}

void HexapodControlWidget::newLegCombination(int combination)
{
    saveLegCombination(m_legCombination);
    m_legCombination = (enum LegCombination) combination;
    loadLegCombination((enum LegCombination) combination);
}

void HexapodControlWidget::saveLegCombination(LegCombination combination)
{
    legCombinationHistory[combination][0] = ui->globalXInput->value();
    legCombinationHistory[combination][1] = ui->globalYInput->value();
    legCombinationHistory[combination][2] = ui->globalZInput->value();
}

void HexapodControlWidget::loadLegCombination(LegCombination combination)
{
    ui->globalXInput->set_value(legCombinationHistory[combination][0]);
    ui->globalYInput->set_value(legCombinationHistory[combination][1]);
    ui->globalZInput->set_value(legCombinationHistory[combination][2]);
}

void HexapodControlWidget::update_hexapodPosition()
{
    Hexapod::PositionSettings_t settings;
    settings.height = ui->heightInput_2->value();
    settings.xOffset = ui->footWidthInput->value();
    m_hexapod->update_positionSettings(settings);
}


void HexapodControlWidget::spin(QPointF direction)
{
}

void HexapodControlWidget::configure_virtualPad(QVirtualPad *pad)
{
    pad->setPadSizeRatio(0.3);
    pad->setBackgroundColor(QColor(93, 85, 89, 200));
    // pad->setDeadZone(0.1);
    pad->setBorderColor(QColor(157, 20, 89, 200));
    pad->setBorderWidth(10);

}

void HexapodControlWidget::set_globalPosition()
{
    switch (m_legCombination)
    {
    case ALL:
        m_hexapod->set_allLegPositions(ui->globalXInput->value(), ui->globalYInput->value(), ui->globalZInput->value());
        break;
    case ODD:
        m_hexapod->set_legPosition(1,ui->globalXInput->value(), ui->globalYInput->value(), ui->globalZInput->value());
        m_hexapod->set_legPosition(3,ui->globalXInput->value(), ui->globalYInput->value(), ui->globalZInput->value());
        m_hexapod->set_legPosition(5,ui->globalXInput->value(), ui->globalYInput->value(), ui->globalZInput->value());
        break;
    case EVEN:
        m_hexapod->set_legPosition(0,ui->globalXInput->value(), ui->globalYInput->value(), ui->globalZInput->value());
        m_hexapod->set_legPosition(2,ui->globalXInput->value(), ui->globalYInput->value(), ui->globalZInput->value());
        m_hexapod->set_legPosition(4,ui->globalXInput->value(), ui->globalYInput->value(), ui->globalZInput->value());
        break;
    }
}


void HexapodControlWidget::determineDirection() {
        // Direction in degrees (0 is right, 90 is up, 180 is left, 270 is down)

        this->setFocus();
        int direction = -1;

        bool up = pressedKeys.contains(Qt::Key_Up);
        bool down = pressedKeys.contains(Qt::Key_Down);
        bool left = pressedKeys.contains(Qt::Key_Left);
        bool right = pressedKeys.contains(Qt::Key_Right);

        if (up && right) {
            direction = 45;  // Up-right
        } else if (up && left) {
            direction = 135;  // Up-left
        } else if (down && right) {
            direction = 315;  // Down-right
        } else if (down && left) {
            direction = 225;  // Down-left
        } else if (up) {
            direction = 90;  // Up
        } else if (down) {
            direction = 270;  // Down
        } else if (left) {
            direction = 180;  // Left
        } else if (right) {
            direction = 0;  // Right
        }

        // qDebug() << "Direction:" << direction << "degrees";



        if (direction != -1) {
            // qDebug() << "Direction:" << direction << "degrees";
            direction = (direction + 180) % 360;
            ui->stepDirectionAngle->set_value(direction*10);
            ui->stepSpeed->set_value(100);
        }
        else {
            ui->stepSpeed->set_value(0);
        }
    }