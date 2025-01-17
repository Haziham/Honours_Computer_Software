#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "jointcontrolwidget.h"
// #include "libusb.h"
#include <QThread>
#include "canQueue.h"
#include "freckle_protocol.h"
#include "jointlistitem.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    qDebug() << "Hello World!";

    graphWidget = new GraphWidget();
    connect(ui->requestAllSettingButton, &QPushButton::clicked, &g_joints, &JointsList::request_allSettings);
    connect(ui->hexapodButton, &QPushButton::clicked, &hexapodControlWidget, &HexapodControlWidget::show);
    connect(ui->showGraphButton, &QPushButton::clicked, graphWidget, &GraphWidget::show); 


    // connect(ui->devicesButton, &QPushButton::clicked, this, &Maiiiindow::displayConnectedDevices);

    // QJoint newJoint = QJoint(0x1F);
    // g_joints.add_joint(&newJoint);



    // Joint* newJoint = new Joint(7);
    // g_joints.add_joint(newJoint);
    // newJoint->settings_changed(); 
    // newJoint->settings_changed(); 
    // newJoint->settings_changed(); 
    // newJoint->settings_changed(); 
    // newJoint->settings_changed(); 
    // Joint* newJoint2 = new Joint(6);
    // g_joints.add_joint(newJoint2);

    // g_joints.remove_joint(5);

    ui->jointsList->assign_joints(&g_joints);
    QJoint* newJoint = new QJoint(0x1F);
    newJoint->settings.joint.legNumber = 8;
    g_joints.add_joint(newJoint); 



    for (int i = 0; i < 6; i++)
    {
        legs[i].set_legNumber(i);
    }

    // ui->leg0Button->set_leg(&legs[0]);
    // ui->leg1Button->set_leg(&legs[1]);
    // ui->leg2Button->set_leg(&legs[2]);
    // ui->leg3Button->set_leg(&legs[3]);
    // ui->leg4Button->set_leg(&legs[4]);
    // ui->leg5Button->set_leg(&legs[5]);



    // // CAN_Message_t message;
    // // QElapsedTimer timer;
    // // uint16_t counter = 0;
    // // JointCommand_t jointCommand;
    // // jointCommand.mode = CMD_PWM;


    // // timer.start();
    // // while(true)
    // // {
    // //     while(usb2can.get_CAN_message(&message) == EXIT_SUCCESS)
    // //     {
    // //         CAN_print_message(&message);
    // //     }

    //     // if (timer.hasExpired(10))
    //     // {
    //     //     counter+=1;
    //     //     jointCommand.mode = counter;

    //     //     encodeJointCommandPacketStructure(&message, &jointCommand);

    //     //     usb2can.send_CAN_message(&message);
    //     //     timer.restart();
    //     // }
    // }

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

    // libusb_device **devices;
    // libusb_context *context = NULL;

    // int errorCode;
    // ssize_t deviceCount;
    // errorCode = libusb_init(&context);

    // if (errorCode < 0)
    // {
    //     qDebug() << "Error initializing libusb: " << errorCode;
    //     return;
    // }

    // libusb_set_debug(context, 3);
    // deviceCount = libusb_get_device_list(context, &devices);

    // if (deviceCount < 0)
    // {
    //     qDebug() << "Error getting device list: " << deviceCount;
    //     return;
    // }

    // qDebug() << "Number of devices: " << deviceCount;
    
    // for (int i = 0; i < deviceCount; i++)
    // {
    //     libusb_device *device = devices[i];
    //     libusb_device_descriptor descriptor;
    //     errorCode = libusb_get_device_descriptor(device, &descriptor);

    //     if (errorCode < 0)
    //     {
    //         qDebug() << "Error getting device descriptor: " << errorCode;
    //         return; 
    //     }

    //     qDebug() << "Device number: " << i;
    //     qDebug() << "Vendor ID: " << descriptor.idVendor;
    //     qDebug() << "Manufacturer: " << descriptor.iManufacturer;
    //     qDebug() << "Product ID: " << descriptor.idProduct;
    //     qDebug() << "Device Class: " << descriptor.bDeviceClass;
    //     qDebug() << "Device Subclass: " << descriptor.bDeviceSubClass;
    //     qDebug() << "Device Protocol: " << descriptor.bDeviceProtocol;
    //     qDebug() << "Max Packet Size: " << descriptor.bMaxPacketSize0;
    //     qDebug() << "Number of Configurations: " << descriptor.bNumConfigurations;
    //     qDebug() << "-------------------------------------------";

    //     // Print string descriptors
    //     libusb_device_handle *handle;
    //     errorCode = libusb_open(device, &handle);

    //     if (errorCode < 0)
    //     {
    //         qDebug() << "Error opening device: " << errorCode;
    //         continue;
    //     }

    //     unsigned char string[256];
    //     errorCode = libusb_get_string_descriptor_ascii(handle, descriptor.iManufacturer, string, 256);
    //     QString manufacturer = QString::fromUtf8((char*)string);
    //     qDebug() << "Manufacturer: " << manufacturer;
    // }
}
