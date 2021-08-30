#include <QDebug>
#include "qnstatusbar.h"
#include<QCoreApplication>

QNStatusBar::QNStatusBar(QWidget *parent,int x,int y,int showflag) :
    QWidget(parent)
{
    this->setGeometry(x,y,320,30);//status bar size
    this->setAttribute(Qt::WA_StyledBackground,true);
    this->setStyleSheet("background-color:transparent;");

    signalLevel_lab=new QLabel(this);
    labs.append(signalLevel_lab);
    signalClient_lab=new QLabel(this);
    labs.append(signalClient_lab);
    time_lab=new QLabel(this);
    labs.append(time_lab);
    ampm_lab=new QLabel(this);
    labs.append(ampm_lab);
    battery_lab=new QLabel(this);
    labs.append(battery_lab);
    battery_lev_lab=new QLabel(this);
    labs.append(battery_lev_lab);
    wifi_lab=new QLabel(this);
    labs.append(wifi_lab);
    led_lab=new QLabel(this);
    labs.append(led_lab);
    signalType_lab=new QLabel(this);
    labs.append(signalType_lab);
    date_lab=new QLabel(this);
    labs.append(date_lab);
 	modem_lab=new QLabel(this);
    labs.append(modem_lab);
    eth_lab=new QLabel(this);
    labs.append(eth_lab);
    bluetooth_lab=new QLabel(this);
    labs.append(bluetooth_lab);

    QFont font;
    signalLevel_lab->setGeometry(0,0,SIGNAL_LEVEL_LAB_W,this->height());
    font.setPixelSize(15);
    signalClient_lab->setGeometry(SIGNAL_LEVEL_LAB_W,0,SIGNAL_CLIENT_LAB_W,this->height());
    signalClient_lab->setStyleSheet("color:white");
    signalClient_lab->setFont(font);
    date_lab->setGeometry(SIGNAL_LEVEL_LAB_W+SIGNAL_TYPE_LAB_W+10,0,DATE_LAB_W,this->height());//date lab with same postion with signal client
    date_lab->setStyleSheet("color:white");
    font.setPixelSize(15);
    date_lab->setAlignment(Qt::AlignCenter);
    date_lab->setFont(font);

    font.setPixelSize(20);
    time_lab->setGeometry(this->width()/2-TIME_LAB_W/2,0,TIME_LAB_W,this->height());
    time_lab->setStyleSheet("color:white;");
    time_lab->setAlignment(Qt::AlignCenter);
    time_lab->setFont(font);
    ampm_lab->setGeometry(time_lab->x()+TIME_LAB_W,0,AMPM_LAB_W,this->height());
    ampm_lab->setStyleSheet("color:white;");
    ampm_lab->setAlignment(Qt::AlignCenter);
    font.setPixelSize(15);
    ampm_lab->setFont(font);

    wifi_lab->setGeometry(date_lab->x()+DATE_LAB_W+5,0,WIFI_LAB_W,this->height());
    wifi_lab->raise();
    signalType_lab->setGeometry(signalLevel_lab->x()+SIGNAL_LEVEL_LAB_W,0,SIGNAL_TYPE_LAB_W,this->height());

    signalType_lab->setStyleSheet("color:white;font-size:15px");
    led_lab->setGeometry(time_lab->x(),0,LED_LAB_W,this->height());
    led_lab->installEventFilter(this);//安装事件过滤器,捕捉绘图事件

    battery_lev_lab->setGeometry(this->width()-CHARGE_LAB_W-BATERRY_LAB_W,0,BATERRY_LAB_W,this->height());
	battery_lev_lab->setAttribute(Qt::WA_TranslucentBackground, true);
    battery_lab->setGeometry(this->width()-CHARGE_LAB_W-BATERRY_LAB_W,0,BATERRY_LAB_W,this->height());
    //battery_lab->installEventFilter(this);//安装事件过滤器,捕捉绘图事件
    battery_lab->setPixmap(QPixmap(STATUSBAR_ICON_PATH"battery.png"));
    battery_lab->setStyleSheet("background:transparent");
    eth_lab->setGeometry(wifi_lab->x(),0,ETH_LAB_W,this->height());

    modem_lab->setGeometry(this->width()-MODEM_LAB_W,0,MODEM_LAB_W,this->height());

    bluetooth_lab->setGeometry(this->width()-MODEM_LAB_W-BATERRY_LAB_W-BLUETOOTH_W-5,0,BLUETOOTH_W,this->height());
    showFlag=showflag;
    setShowFlag(showflag);
    dateformat=0;
    CalenderType=0;
    for(int i=0;i<4;i++)//default is all green
        led_colors.append(Qt::green);

}


QNStatusBar::~QNStatusBar()
{
    for(int i=0;i<8;i++)
        delete labs[i];
}
 void QNStatusBar::setStatusbarVisible()
 {
    this->show();
     repaint();
 }

 void QNStatusBar::updateCalenderType(int type)
 {
     CalenderType=type;
 }

void QNStatusBar::setShowFlag(int flag)
{
    showFlag=flag;

	if(flag&(QNStatusBar::LED_SHOW))//led show ,time lab and ampm lab hide
	{
		showFlag&=~QNStatusBar::TIME_SHOW;
		showFlag&=~QNStatusBar::AMPM_SHOW;
	}
	if(flag&(QNStatusBar::DATE_SHOW))//date show , signal client lab hide
		showFlag&=~QNStatusBar::SIGNAL_CLIENT_SHOW;
	if(flag&(QNStatusBar::ETH_SHOW))//ETH show , WIFI lab hide
		showFlag&=~QNStatusBar::WIFI_SHOW;

	if (flag & (QNStatusBar::BLUETOOTH_SHOW))
		bluetooth_lab->setPixmap(QPixmap(""));
	if(flag&(QNStatusBar::BATTERY_BACKGROUND_SHOW))
        showFlag|=QNStatusBar::BATTERY_LEVEL_SHOW;
	for(int i=0;i<labs.count();i++)
	{
		if(showFlag&(1<<i))//show
			labs[i]->show();
		else
			labs[i]->hide();
	}
	this->show();
	QCoreApplication::processEvents(QEventLoop::AllEvents, 100);//通知系统去处理事件
	if(flag&QNStatusBar::TIME_SHOW)//LED 显示过程中，无线信号为0 无线类型图标隐藏会调用次接口，导致去掉LED显示时，时间被去掉
		showFlag|=QNStatusBar::TIME_SHOW;
	if(flag&QNStatusBar::AMPM_SHOW)//LED 显示过程中，无线信号为0 无线类型图标隐藏会调用次接口，导致去掉LED显示时，时间被去掉
		showFlag|=QNStatusBar::AMPM_SHOW;
	 setStatusbarVisible();
}


int QNStatusBar::getShowFlag(void)
{
	return showFlag;
}
 void QNStatusBar::resetGeometry(QRect rec)
 {
     this->setGeometry(rec);
     for(int i=0;i<labs.count();i++)
         labs[i]->resize(labs[i]->width(),rec.height());

 }

void QNStatusBar::updateTime_slot(void)
{

    QTime tmp=QTime::currentTime();

    if(showFlag&AMPM_SHOW)
    {
        if(tmp.hour()>12)
        {
            ampm_lab->setText("PM");
			QString str = QString("%1:%2").arg(tmp.hour()-12,2,10,QLatin1Char('0')).arg(tmp.minute(),2,10,QLatin1Char('0'));
			time_lab->setText(str);
        }
        else
        {
            ampm_lab->setText("AM");
			QString str = QString("%1:%2").arg(tmp.hour(),2,10,QLatin1Char('0')).arg(tmp.minute(),2,10,QLatin1Char('0'));
			time_lab->setText(str);
        }

    }
    else
    {
		time_lab->setText(tmp.toString("hh:mm"));
    }
    if(showFlag&DATE_SHOW)
    {
        if(current_date!=QDate::currentDate())
           updateDate_slot(dateformat);
    }

}
void QNStatusBar::updateDate_slot(int format)
{
    if(format>=0)
        dateformat=format;
     current_date=QDate::currentDate();

     int year,mon,day;
     year=current_date.year();
     mon=current_date.month();
     day=current_date.day();
     if(CalenderType)//CalenderType==1 Iran calender
        gregorian_to_jalali(year,mon,day,&year,&mon,&day);
     QString date_txt;
     switch (dateformat)
    {
         case 0:date_txt=QString("%1\n%2-%3").arg(year).arg(mon).arg(day);break;
         case 1:date_txt=QString("%1-%2\n%3").arg(day).arg(mon).arg(year);break;
         case 2:date_txt=QString("%1-%2\n%3").arg(mon).arg(day).arg(year);break;
         case 3:date_txt=QString("%1\n%2/%3").arg(year).arg(mon).arg(day);break;
         case 4:date_txt=QString("%1/%2\n%3").arg(day).arg(mon).arg(year);break;
         case 5:date_txt=QString("%1/%2\n%3").arg(mon).arg(day).arg(year);break;
         default:date_txt=QString("%1\n%2-%3").arg(year).arg(mon).arg(day);break;

    }
    qDebug()<<" DATE format"<<format<<"date_txt"<<date_txt;
    date_lab->setText(date_txt);

}
void QNStatusBar::gregorian_to_jalali(long gy,long gm,long gd,int *year,int *mon,int *day)
{
     long gy2,days,jy,jm,jd, g_d_m[12]={0,31,59,90,120,151,181,212,243,273,304,334};
     if(gy>1600){
      jy=979;
      gy-=1600;
     }else{
      jy=0;
      gy-=621;
     }
     gy2=(gm>2)?(gy+1):gy;
     days=(365*gy) +((int)((gy2+3)/4)) -((int)((gy2+99)/100)) +((int)((gy2+399)/400)) -80 +gd +g_d_m[gm-1];
     jy+=33*((int)(days/12053));
     days%=12053;
     jy+=4*((int)(days/1461));
     days%=1461;
     if(days > 365){
      jy+=(int)((days-1)/365);
      days=(days-1)%365;
     }
     jm=(days < 186)?1+(int)(days/31):7+(int)((days-186)/30);
     jd=1+((days < 186)?(days%31):((days-186)%30));
     *year=jy;
     *mon=jm;
     *day=jd;
}
void QNStatusBar::updateSignalClient(const QString txt)
{
    signalClient_lab->setText(txt);
}


void QNStatusBar::updateSignalLevel(int level)
{
    static int prelev=-1;
    if(prelev==level)
        return;
    prelev=level;
    QString str=QString(STATUSBAR_ICON_PATH"signal%1.png").arg(level);
    QPixmap map(str);
    signalLevel_lab->setPixmap(map);
}
 void QNStatusBar::updateSignalType(QString type)
 {
     signalType_lab->setText(type);
 }

void QNStatusBar::updateWiFiLevel(int level)
{
    static int prelev=-1;
    if(prelev==level)
        return;
    prelev=level;

    QString str=QString(STATUSBAR_ICON_PATH"wifi_%1.png").arg(level==0?level:level - 1);
    QPixmap map(str);

    wifi_lab->setPixmap(map);
}

void QNStatusBar::updateBatteryLevel(int lev)
{
    switch (lev)
    {
		case 0:
			if ((showFlag & QNStatusBar::BATTERY_LEVEL_SHOW) != 0)
			{
				showFlag &= (~QNStatusBar::BATTERY_LEVEL_SHOW);	
				setShowFlag(showFlag);
			}
			return;
	    case 1:
        	battery_lev_lab->setPixmap(QPixmap(STATUSBAR_ICON_PATH"battery1.png"));
			break;
		case 2:
        	battery_lev_lab->setPixmap(QPixmap(STATUSBAR_ICON_PATH"battery2.png"));
			break;
		case 3:
        	battery_lev_lab->setPixmap(QPixmap(STATUSBAR_ICON_PATH"battery3.png"));
			break;
		case 4:
        	battery_lev_lab->setPixmap(QPixmap(STATUSBAR_ICON_PATH"adapter.png"));
			break;
		default:
			break;
    }

	if ((showFlag & QNStatusBar::BATTERY_LEVEL_SHOW) == 0)
	{
		showFlag |= QNStatusBar::BATTERY_LEVEL_SHOW;	
		setShowFlag(showFlag);
	}
}


void QNStatusBar::showLed(int ledflag)
{
    showFlag|=QNStatusBar::LED_SHOW;
    //led lab cover time and ampm lab
    led_lab->show();
    time_lab->hide();
    ampm_lab->hide();
    ledFlag=ledflag;

    repaint();
}
 void QNStatusBar::setLedColor(QList<QColor> Col)
 {
     led_colors.clear();
     led_colors=Col;
 }
void QNStatusBar::Led_Flick(int lednum,bool status)
{
   if(status)
       ledFlag|=(1<<lednum-1);
   else
       ledFlag&=~(1<<lednum-1);
    repaint();
}

void QNStatusBar::paint_led()
{
    QPainter paint(led_lab);
    paint.setRenderHint(QPainter::Antialiasing);
    int led_d=20;
    int y=(this->height()-led_d)/2;
    for(int i=0;i<4;i++)
    {
        if(ledFlag&(1<<i))
        {
            paint.setPen(led_colors[i]);
            paint.setBrush(led_colors[i]);
            paint.drawEllipse(5*(i+1)+i*led_d,y,led_d,led_d);
        }
        else
        {
            paint.setPen(Qt::gray);
            paint.setBrush(Qt::gray);
            paint.drawEllipse(5*(i+1)+i*led_d,5,led_d,led_d);
        }
    }

}


bool QNStatusBar::eventFilter(QObject *watched, QEvent *event)
{
	if(watched ==led_lab && event->type() == QEvent::Paint)
        paint_led();
    return QWidget::eventFilter(watched,event);
}


void QNStatusBar::setbackground(QColor c)
{
    this->setAttribute(Qt::WA_StyledBackground,true);
    QString str=QString("background-color:rgb(%1,%2,%3)").arg(c.red()).arg(c.green()).arg(c.blue());
   // qDebug()<<"#####setStyleSheet"<<str;
    this->setStyleSheet("background-color:rgb(40,40,40)");
}
void QNStatusBar::updateEthStatus(int status)
{
    static int prestatus=-1;
    if(prestatus==status)
        return;
    prestatus=status;
    QString icon_path=QString(STATUSBAR_ICON_PATH"eth%1.png").arg(status);
   QPixmap map(icon_path);
    eth_lab->setPixmap(QPixmap(map));
}

void QNStatusBar::updateModemStatus(int status)
{
    static int prestatus=-1;
    if(prestatus==status)
        return;
    prestatus=status;
    QString icon_path=QString(STATUSBAR_ICON_PATH"dial%1.png").arg(status);
    QPixmap map(icon_path);
    modem_lab->setPixmap(QPixmap(map));
}
 void QNStatusBar::updateBluetoothStatus(int status)
 {
     static int prestatus=-1;
     if(prestatus==status)
         return;
     prestatus=status;
     if(!status)
     {
        bluetooth_lab->hide();
        return ;
     }
     bluetooth_lab->show();
     QString icon_path=QString(STATUSBAR_ICON_PATH"bluetooth.png");
     QPixmap map(icon_path);
     bluetooth_lab->setPixmap(QPixmap(map));
 }
