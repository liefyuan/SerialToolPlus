#ifndef SERIALPORTPLUS_H
#define SERIALPORTPLUS_H

#include <QSerialPort>
#include<QThread>
#include<QDebug>

class serialportplus : public QSerialPort
{
    Q_OBJECT
public:

    //串口接收数据的函数
    serialportplus();

    //串口设置
    struct Settings
    {
       QString name;//端口名称COM1、COM2
       BaudRate baudRate;//波特率
       DataBits dataBits;//数据位
       Parity parity;//奇偶校验
       StopBits stopBits;//停止位
       FlowControl flowControl;//流控制
     };

public slots:
    // 分别是界面对串口发出的启动、停止和发送数据的信号时，所要执行的操作
    void startPort(Settings sets);
    void stopPort();
    void sendData(QByteArray arr);

signals:
    // 分别是串口对界面发出的启动、停止和接收数据的信号
    void sigStarted();
    void sigStop(int status);
    void sigReceived(QByteArray data);
};

#endif // SERIALPORTPLUS_H
