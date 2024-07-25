#ifndef JOINTLISTITEM_H
#define JOINTLISTITEM_H

#include <QWidget>
#include "joint.h"

namespace Ui {
class JointListItem;
}

class JointListItem : public QWidget
{
    Q_OBJECT

public:
    explicit JointListItem(Joint** joint, QWidget *parent = nullptr);
    ~JointListItem();
    void update();
    int get_nodeId() { return m_joint->get_nodeId(); }
    void display_jointControlWidget();

private:
    Ui::JointListItem *ui;
    Joint* m_joint;
};

#endif // JOINTLISTITEM_H
