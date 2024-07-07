#include "JointControlWidget.h"
#include "./ui_JointControlWidget.h"

JointControlWidget::JointControlWidget(QWidget *parent) : QWidget(parent), ui(new Ui::JointControlWidget)
{
    ui->setupUi(this);
    // Additional initialization here
}

JointControlWidget::~JointControlWidget()
{
    delete ui;
}