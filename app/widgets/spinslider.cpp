#include "spinslider.h"
#include "ui_spinslider.h"

SpinSlider::SpinSlider(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SpinSlider)
{
    ui->setupUi(this);
    // ui->slider->setStyleSheet(
    //      "QSlider::groove:horizontal {"
    //     "    border: 1px;" // Make the groove invisible
    //     "    height: 1px;" // Set height to 0px to hide the track
    //     "    background: #777777;" // Make background transparent
    //     "}"
    //     "QSlider::handle:horizontal {"
    //     "    border: 1px solid #5c5c5c;" // Customize handle border
    //     "    width: 18px;" // Set handle width
    //     "    margin: -2px 0;"
    //     "    border-radius: 3px;"
    //     "}"
    // );

    // Connect spinbox and slider together
    connect(ui->spinBox, QOverload<int>::of(&QSpinBox::valueChanged), ui->slider, &QSlider::setValue);
    connect(ui->slider, &QSlider::valueChanged, ui->spinBox, &QSpinBox::setValue);
    connect(ui->spinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &SpinSlider::valueChanged);
}

SpinSlider::~SpinSlider()
{
    delete ui;
}

void SpinSlider::set_minimum(int min)
{
    ui->spinBox->setMinimum(min);
    ui->slider->setMinimum(min);
}

void SpinSlider::set_maximum(int max)
{
    ui->spinBox->setMaximum(max);
    ui->slider->setMaximum(max);
}

void SpinSlider::set_value(int value)
{
    ui->spinBox->setValue(value);
    ui->slider->setValue(value);
}
