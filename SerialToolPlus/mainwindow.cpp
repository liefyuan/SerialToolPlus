#include "mainwindow.h"
#include "ui_mainwindow.h"

#define NUM_SAMPLES 96000
#define SAMPLE_FREQ 48000

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    qDebug() <<"main" <<QThread::currentThread();
    qRegisterMetaType<serialportplus::Settings>("serialportplus::Settings");

    initUI();
    initSerialPort();
    initPlot();
}

MainWindow::~MainWindow()
{
    delete ui;

    fftw_free(mFftIn);
    fftw_free(mFftOut);
    fftw_destroy_plan(mFftPlan);
}

/*
 * 函数功能：完成对串口助手界面的初始化
 */
void MainWindow::initUI()
{
    //增加端口号选择项
//    for (int i = 1; i <= 15; i++)
//    {
//        ui->cboPortName->addItem(QString("COM%1").arg(i));
//    }
//    ui->cboPortName->addItem(QString("COM%1").arg(14));

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
    qDebug() << gSetting->value("LastSelectSerialPort").toString();
    ui->cboPortName->setCurrentText(gSetting->value("LastSelectSerialPort").toString());
    ui->cboPortName->addItem(gSetting->value("LastSelectSerialPort").toString());
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

void MainWindow::initPlot()
{
    /* Setup timePlot */
    ui->timePlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    ui->timePlot->legend->setVisible(true);
    QFont legendFont = font();
    legendFont.setPointSize(10);
    ui->timePlot->legend->setFont(legendFont);
    ui->timePlot->legend->setSelectedFont(legendFont);
    ui->timePlot->legend->setSelectableParts(QCPLegend::spItems);
    ui->timePlot->yAxis->setLabel("Amplitude");
    ui->timePlot->xAxis->setLabel("Sample");
    ui->timePlot->xAxis->setRange(0, 300);
    ui->timePlot->yAxis->setRange(0, 300);
    ui->timePlot->clearGraphs();
    ui->timePlot->addGraph();

    ui->timePlot->graph()->setPen(QPen(Qt::black));
    ui->timePlot->graph()->setName("TimeDomainWave");

    /* Setup freqPlot */
    ui->freqPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    ui->freqPlot->legend->setVisible(true);
    legendFont.setPointSize(10);
    ui->freqPlot->legend->setFont(legendFont);
    ui->freqPlot->legend->setSelectedFont(legendFont);
    ui->freqPlot->legend->setSelectableParts(QCPLegend::spItems);
    ui->freqPlot->yAxis->setLabel("Pmax");
    ui->freqPlot->xAxis->setLabel("Hz");
    ui->freqPlot->xAxis->setRange(0, 1000);
    ui->freqPlot->yAxis->setRange(0, 1000);
    ui->freqPlot->clearGraphs();
    ui->freqPlot->addGraph();

    ui->freqPlot->graph()->setPen(QPen(Qt::black));
    ui->freqPlot->graph()->setName("FrqDomainWave");


    /********************fft*******************/
    for (int i = 0; i < NUM_SAMPLES; i ++) {
        mIndices.append((double)i);
        mSamples.append(0);
    }

    double freqStep = (double)SAMPLE_FREQ / (double)NUM_SAMPLES;
    double f = 20;
    while (f < 20000) {
        mFftIndices.append(f);
        f += freqStep;
    }

    /* Set up FFT plan */
    mFftIn  = fftw_alloc_real(NUM_SAMPLES);
    mFftOut = fftw_alloc_real(NUM_SAMPLES);
    mFftPlan = fftw_plan_r2r_1d(NUM_SAMPLES, mFftIn, mFftOut, FFTW_R2HC,FFTW_ESTIMATE);
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

        gSerialSwitchFlg = true;
    }
     //当按钮打开时，关闭串口，向串口子线程发送串口关闭信号
    else
    {
        emit sigStop();
        gSerialSwitchFlg = false;
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

void MainWindow::rawDataDecode(QByteArray data)
{
    static int32_t cnt = 0;
    //协议数据结构
    struct serial_protocol
    {
        uint16_t header; // 协议头
        uint8_t function; // 功能码
        uint8_t length; // 数据长度
        uint8_t data; // 数据
        uint8_t crc_sum; // CRC校验码
    };

    struct serial_protocol m_serial_data;
#if 0
    char*  ch;
    uint8_t len;
    ch = data.data();
    len = data.size();

    memcpy(&m_serial_data, ch, len);
#else
    memcpy(&m_serial_data, data.data(), data.size());
#endif

//    ui->RecveeiveplainTextEdit->appendPlainText( "header:" + QString::number(m_serial_data.header, 16) + "\n" );
//    ui->RecveeiveplainTextEdit->appendPlainText( "function:" + QString::number(m_serial_data.function, 16) + "\n" );
//    ui->RecveeiveplainTextEdit->appendPlainText( "length:" + QString::number(m_serial_data.length, 16) + "\n" );
//    ui->RecveeiveplainTextEdit->appendPlainText( "data:" + QString::number(m_serial_data.data, 16) + "\n" );
//    ui->RecveeiveplainTextEdit->appendPlainText( "crc_sum:" + QString::number(m_serial_data.crc_sum, 16) + "\n" );


    if(m_serial_data.header == 0xAAAA)
    {
        qDebug() << "find out header!";

        ui->RecveeiveplainTextEdit->appendPlainText(QString::number(m_serial_data.data, 10));

        g_new_data.setX(cnt++);
        g_new_data.setY(m_serial_data.data);
        ui->timePlot->graph(0)->addData(g_last_data.x(), g_last_data.y());
        //ui->timePlot->xAxis->rescale();

        g_last_data.setX(g_new_data.x());
        g_last_data.setY(g_new_data.y());

        ui->timePlot->xAxis->setRange(cnt-300, cnt);
        //      ui->timePlot->yAxis->setRange(-100, 100);
        ui->timePlot->replot();

        /*********************fft*************************/
        mSamples.append(m_serial_data.data);

        int n = mSamples.length();
        if (n > 96000)
        {
            mSamples = mSamples.mid(n - NUM_SAMPLES,-1);

            memcpy(mFftIn, mSamples.data(), NUM_SAMPLES*sizeof(double));

            fftw_execute(mFftPlan);

            QVector<double> fftVec;

            for (int i = (NUM_SAMPLES/SAMPLE_FREQ)*20;
                     i < (NUM_SAMPLES/SAMPLE_FREQ)*20000;
                     i ++) {
                fftVec.append(abs(mFftOut[i]));
            }

            ui->freqPlot->graph(0)->setData(mIndices,mSamples);
            ui->freqPlot->xAxis->setRange(0, 20000);
            //ui->freqPlot->xAxis->rescale();
            ui->freqPlot->replot();

            ui->freqPlot->graph(0)->setData(mFftIndices.mid(0,fftVec.length()),fftVec);
            ui->freqPlot->yAxis->rescale(); // 自动设置最大范围
            ui->freqPlot->replot();
        }
    }
    else
    {
        qDebug() << "Format error!";
    }

//    g_new_data.setX(cnt++);
//    g_new_data.setY(m_serial_data.data);
//    ui->timePlot->graph(0)->addData(g_last_data.x(), g_last_data.y());
//    //ui->timePlot->xAxis->rescale();

//    g_last_data.setX(g_new_data.x());
//    g_last_data.setY(g_new_data.y());

//    ui->timePlot->xAxis->setRange(cnt-2000, cnt);
//    //      ui->timePlot->yAxis->setRange(-100, 100);
//    ui->timePlot->replot();
}

/*
 * 函数功能：接收串口子线程发出数据接收的信号，界面接收串口子线程发送的数据，并将其显示到界面上
 */
void MainWindow::receiveData(QByteArray data)
{
#if 0
    //将接收的数据进行转换
    QString strText = QString(data.toHex());
    //获取当前接收数据的时间
    QDateTime current_date_time = QDateTime::currentDateTime();
    //显示当前接收数据的时间
    QString  t  = current_date_time.toString("yyyy-MM-dd hh:mm:ss.zzz : ");
    //显示当前接收的数据
    ui->RecveeiveplainTextEdit->appendPlainText( t + strText + "\n" );
#endif
    //解析数据
    rawDataDecode(data);
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
