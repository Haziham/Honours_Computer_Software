#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

#include <QWidget>
#include <QTimer>
#include <QElapsedTimer>
#include <QJoint.h>
#include <QFile>
#include <QTextStream>

namespace Ui {
class GraphWidget;
}

class GraphWidget : public QWidget
{
    Q_OBJECT

public:
    explicit GraphWidget(QWidget *parent = nullptr);
    ~GraphWidget();
    
    void allocate_joint(QJoint* joint);

public slots:
    void realtimeDataSlot();
    void exportGraphToCSV();

protected:
    void showEvent(QShowEvent *event) override;
    void hideEvent(QHideEvent *event) override;

private:
    Ui::GraphWidget *ui;
    QTimer dataTimer;
    QElapsedTimer time;
    QJoint* joint;

};

extern GraphWidget* graphWidget;
#endif // GRAPHWIDGET_H
