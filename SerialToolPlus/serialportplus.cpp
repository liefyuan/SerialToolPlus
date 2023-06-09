#include "serialportplus.h"

/*
 * 函数功能：对串口接收到数据的信号进行响应，并向界面主线程发送接收到的数据
 */
serialportplus::serialportplus()
{
    //当串口子线程接收到数据时，向界面主线程发出数据接收的信号
    connect(this, &QSerialPort::readyRead, [this]()
    {
        //qDebug() << QStringLiteral ("接收") << QThread::currentThread();
        //读取串口接收的数据
        QByteArray arr = readAll();
        //将数据通过信号发给界面主线程
        emit sigReceived(arr);
    });
}

/*
 * 函数功能：接收界面主线程发出开始信号，接收串口参数并对设置，
 *         同时根据串口状态发出启动或停止信号。
 */
void serialportplus::startPort(serialportplus::Settings sets)
{
    /*设置串口参数*/
    setPortName(sets.name);
    setParity(sets.parity);
    setBaudRate(sets.baudRate);
    setDataBits(sets.dataBits);
    setStopBits(sets.stopBits);
    setFlowControl(sets.flowControl);

    qDebug() << QStringLiteral ("启动") <<QThread::currentThread();

    //判断串口是否处于可读写状态
    if(open(QIODevice::ReadWrite))
    {
        //串口处于可读写状态,发出向界面主线程启动信号
        emit sigStarted();
    }
    else
    {
        //串口不处于可读写状态,发出向界面主线程停止信号
        emit sigStop(1);
    }
}

/*
 * 函数功能：接收界面主线程发送的停止信号，串口关闭
 */
void serialportplus::stopPort()
{
    qDebug() << QStringLiteral ("停止") <<QThread::currentThread();
    //判断串口是否关闭
    if(isOpen())
    {
        //关闭串口
        close();
    }
    //向界面主线程发出停止信号
    emit sigStop(0);
}

/*
 * 函数功能：接收界面主线程发出的数据发送信号，串口进行数据发送
 */
void serialportplus::sendData(QByteArray arr)
{
    qDebug() << QStringLiteral ("发送") <<QThread::currentThread();
    //判断串口是否关闭

    if(isOpen())
    {
        //发送数据
        write(arr);
    }
}
