#include "widget.h"
#include "ui_widget.h"
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QDebug>
#include <QTimer>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    // 串口号
//    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
//    {
//        qDebug() << "Name        : " << info.portName();
//        qDebug() << "Description : " << info.description();
//        qDebug() << "Manufacturer: " << info.manufacturer();


//        // Example use QSerialPort
//        QSerialPort serial;
//        serial.setPort(info);
//        if (serial.open(QIODevice::ReadWrite))
//        {
//            //ui->comboBox->addItem(info.portName());
//            ui->comboBox_ckh->addItem(info.portName());
//            serial.close();
//        }
//    }


//    ui->comboBox_ckh->addItem("/dev/ttyS1");
//    ui->comboBox_ckh->addItem("/dev/ttyS2");
//    ui->comboBox_ckh->addItem("/dev/ttyS3");
    ui->comboBox_ckh->addItem("/dev/ttyACM0");
    ui->comboBox_ckh->addItem("/dev/pts/6");
    ui->comboBox_ckh->addItem("/dev/pts/20");

    // 波特率
//    ui->comboBox_btl->addItem("9600");
    ui->comboBox_btl->addItem("57600");
//    ui->comboBox_btl->addItem("115200");

    // 数据位
    ui->comboBox_sjw->addItem("8");
    ui->comboBox_sjw->addItem("7");

    // 校验位
    ui->comboBox_jyw->addItem("无");
    ui->comboBox_jyw->addItem("奇");
    ui->comboBox_jyw->addItem("偶");

    // 停止位
    ui->comboBox_tzw->addItem("1");
    ui->comboBox_tzw->addItem("2");

    ui->pushButton_close->setEnabled(false);
    ui->pushButton_send->setEnabled(false);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_cmopen_clicked()
{
//    my_serialport= new QSerialPort();
//    qDebug()<<ui->comboBox->currentText();
//    my_serialport->setPortName(ui->comboBox->currentText());
//    my_serialport->open(QIODevice::ReadWrite);
//    qDebug()<<ui->lineEdit->text().toInt();
//    my_serialport->setBaudRate(ui->lineEdit->text().toInt());
//    my_serialport->setDataBits(QSerialPort::Data8);
//    my_serialport->setParity(QSerialPort::NoParity);
//    my_serialport->setStopBits(QSerialPort::OneStop);
//    my_serialport->setFlowControl(QSerialPort::NoFlowControl);

//    timer = new QTimer(this);
//    connect(timer, SIGNAL(timeout()), this, SLOT(updateAA()));
//    timer->start(1000);
}

void Widget::updateAA()
{
//    requestData = my_serialport->readAll();
//    if(requestData!= NULL)
//    {
//        ui->textEdit->append(requestData);
//    }
//    requestData.clear();
}

void Widget::on_pushButton_send_clicked()
{
//    QByteArray TxData = "aaaa";
//    my_serialport->write(TxData);
    my_serialport->write(ui->lineEdit->text().toLocal8Bit());
}

void Widget::on_pushButton_open_clicked()
{
    my_serialport= new QSerialPort();

    my_serialport->setPortName(ui->comboBox_ckh->currentText());
    my_serialport->open(QIODevice::ReadWrite);

    if(ui->comboBox_btl->currentText() == "9600")
        my_serialport->setBaudRate(QSerialPort::Baud9600);
    else if(ui->comboBox_btl->currentText() == "115200")
        my_serialport->setBaudRate(QSerialPort::Baud115200);
    else if(ui->comboBox_btl->currentText() == "57600")
        my_serialport->setBaudRate(QSerialPort::Baud57600);

    if(ui->comboBox_sjw->currentText() == "8")
        my_serialport->setDataBits(QSerialPort::Data8);
    else if(ui->comboBox_sjw->currentText() == "7")
        my_serialport->setDataBits(QSerialPort::Data7);

    if(ui->comboBox_jyw->currentText() == "无")
        my_serialport->setParity(QSerialPort::NoParity);
    else if(ui->comboBox_jyw->currentText() == "奇")
        my_serialport->setParity(QSerialPort::OddParity);
    else if(ui->comboBox_jyw->currentText() == "偶")
        my_serialport->setParity(QSerialPort::EvenParity);

    if(ui->comboBox_tzw->currentText() == "1")
        my_serialport->setStopBits(QSerialPort::OneStop);
    else if(ui->comboBox_tzw->currentText() == "2")
        my_serialport->setStopBits(QSerialPort::TwoStop);

    my_serialport->setFlowControl(QSerialPort::NoFlowControl);

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(receiveData()));
    timer->start(1000);

    ui->pushButton_open->setEnabled(false);
    ui->pushButton_close->setEnabled(true);
    ui->pushButton_send->setEnabled(true);
    ui->comboBox_btl->setEnabled(false);
    ui->comboBox_ckh->setEnabled(false);
    ui->comboBox_jyw->setEnabled(false);
    ui->comboBox_sjw->setEnabled(false);
    ui->comboBox_tzw->setEnabled(false);
}

void Widget::on_pushButton_close_clicked()
{
    my_serialport->close();

    ui->pushButton_open->setEnabled(true);
    ui->pushButton_close->setEnabled(false);
    ui->pushButton_send->setEnabled(false);
    ui->comboBox_btl->setEnabled(true);
    ui->comboBox_ckh->setEnabled(true);
    ui->comboBox_jyw->setEnabled(true);
    ui->comboBox_sjw->setEnabled(true);
    ui->comboBox_tzw->setEnabled(true);
}

void Widget::receiveData()
{
    requestData = my_serialport->readAll();
    qDebug()<< requestData;
    if(requestData!= NULL)
    {
        // 以十六进制显示
//        QString strDis;
//        QString str3 = requestData.toHex().data();//以十六进制显示
//        str3 = str3.toUpper ();//转换为大写
//        for(int i = 0;i<str3.length ();i+=2)//填加空格
//        {
//           QString st = str3.mid (i,2);
//           strDis += st;
//           strDis += " ";
//        }
//        ui->textEdit->append(strDis);
        ui->textEdit->append(requestData);
    }
    requestData.clear();
}
