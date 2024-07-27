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
    explicit JointListItem(Joint* joint, QWidget *parent = nullptr);
    ~JointListItem();
    int get_nodeId() { return m_joint->get_nodeId(); }
    Joint* get_joint() { return m_joint; }
    void display_jointControlWidget();

public slots:
    void update();

private:
    Ui::JointListItem *ui;
    Joint* m_joint;
};

#endif // JOINTLISTITEM_H
