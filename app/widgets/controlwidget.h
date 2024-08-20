#ifndef CONTROLWIDGET_H
#define CONTROLWIDGET_H

#include <QWidget>
#include <QTimer>

#define REFRESH_RATE_MS 200

class ControlWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ControlWidget(QWidget *parent = nullptr);
    ~ControlWidget();

    void start_refresh_timer(int ms = REFRESH_RATE_MS) {refreshTimer.start(ms);}; // start the timer with the given ms interval
    void stop_refresh_timer() {refreshTimer.stop();}; // stop the timer

private:
    QTimer refreshTimer;
    virtual void refresh_widget();
};

#endif // CONTROLWIDGET_H
