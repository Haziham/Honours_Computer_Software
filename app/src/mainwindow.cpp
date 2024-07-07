#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "libusb.h"
#include <QThread>
#include "canQueue.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    qDebug() << "Hello World!";

    // Connect the button to the function
    connect(ui->devicesButton, &QPushButton::clicked, this, &MainWindow::displayConnectedDevices);

    int result = usb2can.open_port();
    if (result == EXIT_FAILURE)
    {
        qDebug() << "Error opening port!";
        return;
    }
    usb2can.moveToThread(serialThread);
    // connect(serialThread, &QThread::started, &usb2can, &USB2CAN::send_and_receive);
    serialThread->start();

    CAN_Message_t message;
    QElapsedTimer timer;
    timer.start();
    while(true)
    {
        while(usb2can.get_CAN_message(&message) == EXIT_SUCCESS)
        {
            CAN_print_message(&message);
        }

        if (timer.hasExpired(1000))
        {
            message.id = 3;
            message.len = 8;
            for (int i = 0; i < message.len; i++)
            {
                message.data[i] = i;
            }
            usb2can.send_CAN_message(&message);
            timer.restart();
        }
    }

    // RC_Car car;
    // car.test_class();
    
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::displayConnectedDevices()
{

    qDebug() << "Displaying connected devices...";
    // QString port_name;
    // int result = usb2can.find_port_name(port_name);
    // if (result == EXIT_FAILURE)
    // {
    //     qDebug() << "USB2CAN device not found!";
    //     return;
    // }
    // else if (result == EXIT_SUCCESS)
    // {
    //     qDebug() << "USB2CAN device found!";
    //     qDebug() << "Port name: " << port_name;
    // }

    // int numberOfBytes = usb2can.bytesAvailable();
    // while (numberOfBytes < 20)
    // {
    //     qDebug() << "Number of bytes: " << numberOfBytes;
    //     // outptu serial port settings
    //     qDebug() << "Baud rate: " << usb2can.baudRate();
    //     qDebug() << "Data bits: " << usb2can.dataBits();
    //     qDebug() << "Parity: " << usb2can.parity();
    //     qDebug() << "Stop bits: " << usb2can.stopBits();
    //     qDebug() << "Flow control: " << usb2can.flowControl();
    //     qDebug() << "Data terminal ready: " << usb2can.isDataTerminalReady();
    //     qDebug() << "Port name" << usb2can.portName();
    //     numberOfBytes = usb2can.bytesAvailable();
    //     QThread::msleep(1000);
    // }

    
    while(true)
    {

    }
    return;

    libusb_device **devices;
    libusb_context *context = NULL;

    int errorCode;
    ssize_t deviceCount;
    errorCode = libusb_init(&context);

    if (errorCode < 0)
    {
        qDebug() << "Error initializing libusb: " << errorCode;
        return;
    }

    libusb_set_debug(context, 3);
    deviceCount = libusb_get_device_list(context, &devices);

    if (deviceCount < 0)
    {
        qDebug() << "Error getting device list: " << deviceCount;
        return;
    }

    qDebug() << "Number of devices: " << deviceCount;
    
    for (int i = 0; i < deviceCount; i++)
    {
        libusb_device *device = devices[i];
        libusb_device_descriptor descriptor;
        errorCode = libusb_get_device_descriptor(device, &descriptor);

        if (errorCode < 0)
        {
            qDebug() << "Error getting device descriptor: " << errorCode;
            return; 
        }

        qDebug() << "Device number: " << i;
        qDebug() << "Vendor ID: " << descriptor.idVendor;
        qDebug() << "Manufacturer: " << descriptor.iManufacturer;
        qDebug() << "Product ID: " << descriptor.idProduct;
        qDebug() << "Device Class: " << descriptor.bDeviceClass;
        qDebug() << "Device Subclass: " << descriptor.bDeviceSubClass;
        qDebug() << "Device Protocol: " << descriptor.bDeviceProtocol;
        qDebug() << "Max Packet Size: " << descriptor.bMaxPacketSize0;
        qDebug() << "Number of Configurations: " << descriptor.bNumConfigurations;
        qDebug() << "-------------------------------------------";

        // Print string descriptors
        libusb_device_handle *handle;
        errorCode = libusb_open(device, &handle);

        if (errorCode < 0)
        {
            qDebug() << "Error opening device: " << errorCode;
            continue;
        }

        unsigned char string[256];
        errorCode = libusb_get_string_descriptor_ascii(handle, descriptor.iManufacturer, string, 256);
        QString manufacturer = QString::fromUtf8((char*)string);
        qDebug() << "Manufacturer: " << manufacturer;
    }
}
