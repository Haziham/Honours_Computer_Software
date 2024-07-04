#include "mainwindow.h"
#include <QApplication>
#include <QTimer>


#ifdef _WIN32
    #include <Windows.h>
#endif

int main(int argc, char *argv[])
{
    // Enable console output when developing on Windows
    #ifdef _WIN32
    if (AttachConsole(ATTACH_PARENT_PROCESS)) {
        freopen("CONOUT$", "w", stdout);
        freopen("CONOUT$", "w", stderr);
        qDebug() << "\n";
    }
    #endif

    QApplication a(argc, argv);
// QSerialPort serial;
//     serial.setPortName("ttyUSB0"); // Example port, adjust as needed
//     serial.setBaudRate(2000000);
//     serial.setDataBits(QSerialPort::Data8);
//     serial.setParity(QSerialPort::NoParity);
//     serial.setStopBits(QSerialPort::OneStop);
//     serial.setFlowControl(QSerialPort::NoFlowControl);
    
//     if (serial.open(QIODevice::ReadWrite)) {
//         qDebug() << "Serial port opened successfully";
//     } else {
//         qCritical() << "Failed to open serial port:" << serial.errorString();
//         return 1;
//     }

//     while (true)
//     {
//         serial.waitForReadyRead(10);
//         if (serial.bytesAvailable())
//         {
//             QByteArray data = serial.readAll();
//             qDebug() << "Read data:" << data.toHex();

//         }
//     }
    // const int pollInterval = 1000; // Polling interval in milliseconds
    //     while (true) {
    //         // if (serial.waitForReadyRead(pollInterval)) {
    //             QByteArray data = serial.readAll();
    //             qDebug() << "Read data:" << data.toHex();
    //         // } else {
    //             qDebug() << "No data available";
    //         // }
            
    //         // Add delay before next poll (adjust as needed)
    //         QThread::msleep(pollInterval); // usleep takes microseconds, so multiply by 1000
    //     }
    // QTimer timer;
    // timer.setInterval(1000); // Adjust interval as needed
    // QObject::connect(&timer, &QTimer::timeout, [&]() {
    //     if (serial.bytesAvailable() > 0) {
    //         QByteArray data = serial.readAll();
    //         qDebug() << "Read data:" << data.toHex();
    //     } else {
    //         qDebug() << "No data available";
    //     }
    // });
    // timer.start();
    // int numberOfBytes = serial.bytesAvailable();
    // while (numberOfBytes < 20)
    // {
    //     qDebug() << "Number of bytes: " << numberOfBytes;
    //     numberOfBytes = serial.bytesAvailable();
    //     QThread::msleep(1000);
    // }
    // Connect signals and slots for reading
    // QObject::connect(&serial, &QSerialPort::readyRead, [&]() {
    //     qDebug () << "Data available:" << serial.bytesAvailable();
    //     QByteArray data = serial.readAll();
    //     qDebug() << "Read data:" << data.toHex();
    // });

    MainWindow w;
    w.show();
    return a.exec();
}
