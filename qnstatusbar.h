#ifndef QNSTATUSBAR_H
#define QNSTATUSBAR_H

#include <QWidget>
#include <QTime>
#include <QTimer>
#include <QLabel>
#include <QPainter>
#include <QEvent>


#define SIGNAL_LEVEL_LAB_W    30
#define SIGNAL_CLIENT_LAB_W    80
#define DATE_LAB_W    40
#define TIME_LAB_W    60
#define AMPM_LAB_W    20
#define LED_LAB_W (TIME_LAB_W+AMPM_LAB_W+25)
#define BATERRY_LAB_W   30
#define CHARGE_LAB_W    30
#define MODEM_LAB_W 30
#define ETH_LAB_W   20
#define WIFI_LAB_W 20
#define SIGNAL_TYPE_LAB_W    20
#define BLUETOOTH_W    10
#define STATUSBAR_ICON_PATH "/system/Qt/icons/small/"


class QNStatusBar : public QWidget
{
    Q_OBJECT
public:
    explicit QNStatusBar(QWidget *parent = 0,int x=0,int y=0,int showflag=0x3f);
    ~QNStatusBar();
    typedef enum{
        SIGNAL_LVEL_SHOW=0x01,
        SIGNAL_CLIENT_SHOW=0x02,
        TIME_SHOW=0x04,
        AMPM_SHOW=0x08,
        BATTERY_BACKGROUND_SHOW=0x10,
        BATTERY_LEVEL_SHOW=0x20,
        WIFI_SHOW=0x40,
        LED_SHOW=0x80,
        SIGNAL_TYPE_SHOW=0x100,
        DATE_SHOW=0x200,//same postion with SIGNAL_CLIENT_SHOW
        MODEM_SHOW=0x400,
        ETH_SHOW=0x800,
        BLUETOOTH_SHOW=0x1000,
    }QNStatusFlag;
    /**************************
     * 1<<0--->show signal level lab,0<<0 is hide
     * 1<<1--->show signal client level lab,0<<1 is hide
     * 1<<2--->show time lab ,0<<2 is hide
     * 1<<3--->show am pm lab ,0<<3 is hide
     * 1<<4--->show battery lab,0<<3 is hide
     * 1<<5--->show charge lab,0<<4 is hide
     * 1<<6--->show wifi ,this lab position keep the same with signal client,if wifi show,signal client message will clean
     * 1<<7--->show led,this lab position keep the same with time lab, if led show,time message will clean
     *******************/
    typedef enum{
        FIRST_LED_ON=0x01,
        SECOND_LED_ON=0x02,
        THIRD_LED_ON=0x04,
        FOURTH_LED_ON=0x08,
        ALL_LED_OFF=0x00,
    }QNLEDFLAG;
    /**************************************************
     * 1<<0 ---->first led on,0<<0 is first led off
     * 1<<1 ---->second led on,0<<1 is second led off
     * 1<<2 ---->third led on, 0<<2 is third led off
     * 1<<3 ---->fouth led on, 0<<3 is fourth led off
     * ************************************************/
    typedef enum {
        ETH_LINKED=0X02,
        ETH_UNLINKED=0X01,
        ETH_UNINIT=0X00,
    }QNETHSTATUSFLAG;
    typedef enum {
        MODEM_DIALING=0X02,
        MODEM_LINKED=0X00,
        MODEM_UNLINKED=0X01,
    }QNMODEMSTATUSFLAG;

    void setShowFlag(int flag);
    void resetGeometry(QRect rec);
	int getShowFlag(void);
    void setbackground(QColor c);
    void updateSignalLevel(int level);
    void updateSignalType(QString type);
    void updateWiFiLevel(int level);
    void updateSignalClient(const QString txt);
    void updateBatteryLevel(int lev);
    //void updateChargeStatus(bool status);
    void updateEthStatus(int status);
    void updateModemStatus(int status);
    void updateBluetoothStatus(int status);
    void updateCalenderType(int type=0);
    void setStatusbarVisible();
    void showLed(int ledflag);
    void setLedColor(QList<QColor> Col);
    bool eventFilter(QObject *watched, QEvent *event);
    //void paint_battery_volume(void);
    void paint_led(void);
    void Led_Flick(int lednum,bool status);
    QDate current_date;
signals:

public slots:
    void updateTime_slot(void);
    void updateDate_slot(int format);

private:
    void gregorian_to_jalali(long gy,long gm,long gd,int *year,int *mon,int *day);//Iran calendar
    QTime current_time;

    QTimer *oneSec_timer;
    QLabel *bluetooth_lab;
    QLabel *signalLevel_lab,*signalClient_lab,*time_lab,*ampm_lab,*battery_lab,*battery_lev_lab,*wifi_lab,*led_lab,*signalType_lab,*date_lab,*modem_lab,*eth_lab;
    QList<QLabel *> labs;
    int showFlag,battery_lev;
    int ledFlag,dateformat,CalenderType;//CalenderType==1 Iran calender

    QList<QColor> led_colors;
};

#endif // QNSTATUSBAR_H
