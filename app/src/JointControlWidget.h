#pragma once

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class JointControlWidget; }
QT_END_NAMESPACE

class JointControlWidget : public QWidget
{
    Q_OBJECT

public:
    JointControlWidget(QWidget *parent = nullptr);
    ~JointControlWidget();

private:
    Ui::JointControlWidget *ui;
};