#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    qDebug() <<"main" <<QThread::currentThread();
    qRegisterMetaType<serialportplus::Settings>("serialportplus::Settings");

    initUI();
    initSerialPort();
}

MainWindow::~MainWindow()
{
    delete ui;
}

/*
 * 函数功能：完成对串口助手界面的初始化
 */
void MainWindow::initUI()
{
    //扫描当前系统上的端口号
    QStringList newPortStringList;
    static QStringList oldPortStringList;

    const auto infos = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &info : infos)
    {
        newPortStringList += info.portName();
    }
    //更新串口号
    if(newPortStringList.size() != oldPortStringList.size())
    {
        oldPortStringList = newPortStringList;
        ui->cboPortName->clear();
        ui->cboPortName->addItems(oldPortStringList);
    }

    //设置端口号波特率
    ui->cboBaudrate->addItem(QString("1200"),QSerialPort::Baud1200);
    ui->cboBaudrate->addItem(QString("2400"),QSerialPort::Baud2400);
    ui->cboBaudrate->addItem(QString("4800"),QSerialPort::Baud4800);
    ui->cboBaudrate->addItem(QString("9600"),QSerialPort::Baud9600);
    ui->cboBaudrate->addItem(QString("19200"),QSerialPort::Baud19200);
    ui->cboBaudrate->addItem(QString("38400"),QSerialPort::Baud38400);
    ui->cboBaudrate->addItem(QString("57600"),QSerialPort::Baud57600);
    ui->cboBaudrate->addItem(QString("115200"),QSerialPort::Baud115200);

    //设置端口数据位数
    ui->cboDataBit->addItem("8",QSerialPort::Data8);
    ui->cboDataBit->addItem("7",QSerialPort::Data7);
    ui->cboDataBit->addItem("6",QSerialPort::Data6);
    ui->cboDataBit->addItem("5",QSerialPort::Data5);

    //设置端口校验方式
    ui->cboParity->addItem("None",QSerialPort::NoParity);
    ui->cboParity->addItem("Odd",QSerialPort::OddParity);
    ui->cboParity->addItem("Even",QSerialPort::EvenParity);

    //设置端口停止位
    ui->cboStopBit->addItem("1",QSerialPort::OneStop);
    ui->cboStopBit->addItem("1.5",QSerialPort::OneAndHalfStop);
    ui->cboStopBit->addItem("2",QSerialPort::TwoStop);

    //设置端口流控制
    ui->cboFlowContral->addItem("None",QSerialPort::NoFlowControl);
    ui->cboFlowContral->addItem("RTS/CTS",QSerialPort::HardwareControl);
    ui->cboFlowContral->addItem("XON/XOFF",QSerialPort::SoftwareControl);

    //设置定时重发时间，单位ms
    ui->lineEdit->setText("1000");
    //定时时间到，则执行timeup函数
    connect(&m_timer, &QTimer::timeout, this,&MainWindow::timeUp);
    //定时更新串口号
    connect(&m_port_timer, &QTimer::timeout, this, &MainWindow::timerUpdate);
    //定时更新串口号,开始
    m_port_timer.start(1000);
    //串口初始化状态
    gSerialSwitchFlg = false;


    gSetting = new QSettings("./Setting.ini", QSettings::IniFormat);


    // 读取上次的设置
    ui->cboPortName->setCurrentText(gSetting->value("LastSelectSerialPort").toString());
    ui->cboBaudrate->setCurrentText(gSetting->value("LastSelectSerialBaud").toString());
}

/*
 * 函数功能：定时更新当前系统中的串口号
 */
void MainWindow::timerUpdate()
{
    if(!gSerialSwitchFlg)
    {
        QStringList newPortStringList;
        static QStringList oldPortStringList;

        const auto infos = QSerialPortInfo::availablePorts();
        for (const QSerialPortInfo &info : infos)
        {
            newPortStringList += info.portName();
        }
        //更新串口号
        if(newPortStringList.size() != oldPortStringList.size())
        {
            oldPortStringList = newPortStringList;
            ui->cboPortName->clear();
            ui->cboPortName->addItems(oldPortStringList);
        }

        // 读取上次的设置
        ui->cboPortName->setCurrentText(gSetting->value("LastSelectSerialPort").toString());
        ui->cboBaudrate->setCurrentText(gSetting->value("LastSelectSerialBaud").toString());
    }
}

/*
 * 函数功能：完成对串口的初始化，设置串口子线程
 */
void MainWindow::initSerialPort()
{
    //将串口对象的相关操作，放入子线程
    m_serial.moveToThread(&m_thread);
    //子线程启动
    m_thread.start();

    /*分别是界面对串口发出的启动、停止和发送数据的信号*/
    connect(this, &MainWindow::sigStart,&m_serial, &serialportplus::startPort);
    connect(this, &MainWindow::sigStop,&m_serial, &serialportplus::stopPort);
    connect(this, &MainWindow::sigSend,&m_serial, &serialportplus::sendData);

    /*分别是串口对界面发出的启动、停止和接收数据的信号*/
    connect(&m_serial, &serialportplus::sigStarted,this, &MainWindow::started);
    connect(&m_serial, &serialportplus::sigStop,this, &MainWindow::stoped);
    connect(&m_serial, &serialportplus::sigReceived,this, &MainWindow::receiveData);
}

/*
 * 函数功能：当界面关闭时，子线程也要进行关闭
 */
void MainWindow::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event);
    //打印界面主线程地址
    qDebug() <<"main" <<QThread::currentThread();
    //向发送串口发送串口停止的信号
    emit sigStop();

    //串口子线程关闭
    m_thread.quit();
    //等待串口子线程完全关闭
    m_thread.wait();
}

/*
 * 函数功能：根据串口打开按钮判断是否打开串口，
 *         当串口打开时，对串口参数进行设置，并向串口子线程发出串口打开信号，否则发出关闭信号
 */
void MainWindow::on_btnOpenPort_clicked()
{
    //获取串口打开按钮的文本
    QString text= ui->btnOpenPort->text();
    //当按钮关闭时，打开串口，并设置相关参数，向串口子线程发送串口打开信号
    if(text ==  QStringLiteral("打开串口"))
    {
        serialportplus::Settings s;
        s.name= ui->cboPortName->currentText();
        s.baudRate= (QSerialPort::BaudRate)ui->cboBaudrate->currentData().toInt();
        s.dataBits = (QSerialPort::DataBits)ui->cboDataBit->currentData().toInt();
        s.stopBits= (QSerialPort::StopBits)ui->cboStopBit->currentData().toInt();
        s.parity= (QSerialPort::Parity)ui->cboParity->currentData().toInt();
        s.flowControl = (QSerialPort::FlowControl)ui->cboFlowContral->currentData().toInt();
        emit sigStart(s);

        // 保存设置
        gSetting->setValue("LastSelectSerialPort", ui->cboPortName->currentText());
        gSetting->setValue("LastSelectSerialBaud", ui->cboBaudrate->currentText());
    }
     //当按钮打开时，关闭串口，向串口子线程发送串口关闭信号
    else
    {
        emit sigStop();
    }
}

/*
 * 函数功能：点击发送按钮时，执行串口发送
 */
void MainWindow::on_btnSend_clicked()
{
    //获取所要发送的文本
    QString strSend = ui->SendplainTextEdit->toPlainText();
    //将所要发送的文本存入arr变量
    QByteArray arr = strSend.toUtf8();
    //将arr变量通过信号发给串口子线程
    emit sigSend(arr);
}

/*
 * 函数功能：接收串口子线程发出启动的信号，对串口的按钮和参数设置的界面进行管理
 */
void MainWindow::started()
{
    //串口打开按钮文本切换，切换为“关闭串口”
    ui->btnOpenPort->setText(QStringLiteral("关闭串口"));
    //串口参数处于不可更改的状态
    ui->groupBox->setEnabled(false);
}

/*
 * 函数功能：接收串口子线程发出停止的信号，对串口的按钮和参数设置的界面进行管理
 */
void MainWindow::stoped(int status)
{
    Q_UNUSED(status);
    //串口打开按钮文本切换，切换为“打开串口”
    ui->btnOpenPort->setText(QStringLiteral("打开串口"));
    //串口参数处于可更改的状态
    ui->groupBox->setEnabled(true);
}

/*
 * 函数功能：接收串口子线程发出数据接收的信号，界面接收串口子线程发送的数据，并将其显示到界面上
 */
void MainWindow::receiveData(QByteArray data)
{
    //将接收的数据进行转换
    QString strText = QString(data.toHex());
    //获取当前接收数据的时间
    QDateTime current_date_time = QDateTime::currentDateTime();
    //显示当前接收数据的时间
    QString  t  = current_date_time.toString("yyyy-MM-dd hh:mm:ss.zzz : ");
    //显示当前接收的数据
    ui->RecveeiveplainTextEdit->appendPlainText( t + strText + "\n" );
}

/*
 * 函数功能：定时发送状态改变响应函数
 */
void MainWindow::on_checkBox_stateChanged(int arg1)
{
    //当定时发送被勾选时
    if(arg1)
    {
        //定时器启动
        m_timer.start(ui->lineEdit->text().toInt());
    }
    //当定时发送未被勾选时
    else
    {
        //定时器停止
        m_timer.stop();
    }
}

/*
 * 函数功能：定时时间到时，执行串口发送函数
 */
void MainWindow::timeUp()
{
    qDebug() << "timeup";

    //串口发送函数
    on_btnSend_clicked();
}
