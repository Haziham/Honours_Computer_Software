#ifndef JOINTLISTITEM_H
#define JOINTLISTITEM_H

#include <QWidget>
#include "QJoint.h"
#include "jointcontrolwidget.h"
#include "FreckleProtocol.h"

namespace Ui {
class JointListItem;
}

class JointListItem : public QWidget
{
    Q_OBJECT

public:
    explicit JointListItem(QWidget *parent = nullptr, QJoint* joint = nullptr);
    ~JointListItem();
    int get_nodeId() { return m_joint->get_nodeId(); }
    QJoint* get_joint() { return m_joint; }
    void set_joint(QJoint* joint);

protected:
    void mouseDoubleClickEvent(QMouseEvent *event) override {
        Q_UNUSED(event);
       emit doubleClicked();
    }

signals: 
    void doubleClicked();

public slots:
    void update();
    void display_jointControlWidget();

private:
    Ui::JointListItem *ui;
    QJoint* m_joint;

    void display_noJoint();
};

#endif // JOINTLISTITEM_H
