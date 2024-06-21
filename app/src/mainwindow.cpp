#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "libusb.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    qDebug() << "Hello World!";
    qDebug() << "Testo";

    // Connect the button to the function
    connect(ui->devicesButton, &QPushButton::clicked, this, &MainWindow::displayConnectedDevices);

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
