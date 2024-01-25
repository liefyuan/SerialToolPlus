#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDateTime>
#include <QTimer>
#include <QDebug>
#include <QThread>
#include <QSettings>
#include "qcustomplot.h"
#include <fftw-3.3.5-dll64/fftw3.h>

#include"serialportplus.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    //界面初始化函数
    void initUI();
    //端口初始化函数
    void initSerialPort();
    // 初始化图表
    void initPlot();
    //界面关闭事件
    void closeEvent(QCloseEvent *event);

private:
    Ui::MainWindow *ui;

    //创建一个自定义的串口类对象
    serialportplus m_serial;
    //创建一个线程对象
    QThread m_thread;
    //创建一个定时器对象
    QTimer m_timer;
    //串口号定时更新定时器
    QTimer m_port_timer;
    // 标记串口的开关状态
    bool gSerialSwitchFlg;
    // 记录上一次的配置
    QSettings *gSetting;

    QPointF g_new_data;

    QPointF g_last_data;

    QVector<double> mSamples;
    QVector<double> mIndices;
    QVector<double> mFftIndices;

    fftw_plan mFftPlan;
    double *mFftIn;
    double *mFftOut;

signals:

    // 分别是界面对串口发出的启动、停止和发送数据的信号
    void sigStart(serialportplus::Settings s);
    void sigStop();
    void sigSend(QByteArray data);

public slots:

    // 分别是串口对界面发出的启动、停止和接收数据的信号时，所要执行的操作
    void started();
    void stoped(int status);
    void receiveData(QByteArray data);
    void rawDataDecode(QByteArray data);


private slots:
    void timeUp();
    void on_btnOpenPort_clicked();
    void on_btnSend_clicked();
    void on_checkBox_stateChanged(int arg1);
    void timerUpdate();
};
#endif // MAINWINDOW_H
