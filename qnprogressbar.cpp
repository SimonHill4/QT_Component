#include "qnprogressbar.h"

QNProgressBar::QNProgressBar(QWidget *parent,QRect rec) :
    QWidget(parent)
{
    this->setGeometry(rec);
    percent=0;
    txt_lab=new QLabel(this);
    txt_lab->setGeometry(rec.width()*0.26+10,rec.height()*0.25,rec.width()/2,rec.width()/2);
    txt_lab->setStyleSheet("QLabel{font-size:20px;color:rgb(40,40,40);font-weight:bold}");

    circleFlag=false;
}
QNProgressBar::~QNProgressBar()
{
    delete txt_lab;
}
void QNProgressBar::updatePercent(int value)
{
    value>0?percent=value%102:percent=value;//101-->用于画勾勾 -1-->画叉叉
    repaint();
}
 void QNProgressBar::runCircle(int value)
 {
        circleFlag=true;
        percent=value%101;
        repaint();
 }

void QNProgressBar::paintEvent(QPaintEvent *)
{
    int recw,offset;
    QPainter paint(this);
    this->width()>100?recw=100:recw=60;
     this->width()>100?offset=30:offset=20;
    paint.setRenderHint(QPainter::Antialiasing, true);
    QRectF rectangle(10,10,recw,recw);
    int startAngle = 0;
    int spanAngle = percent*3.5* 16;
    if(circleFlag)
    {
        txt_lab->hide();
        startAngle=(percent-5)*3.6* 16;
        paint.setPen(QPen(Qt::white,10,Qt::SolidLine));//进度圆弧
        paint.drawArc(rectangle, startAngle, -spanAngle);
        return;
    }
    if(percent==101)
    {
        txt_lab->hide();
        paint.setPen(QPen(QColor(2,171,72),8,Qt::SolidLine));//设置画笔形式
        paint.setBrush(QBrush(QColor(2,171,72),Qt::SolidPattern));
        paint.drawEllipse(10,10,recw,recw);
         paint.setPen(QPen(Qt::white,8,Qt::SolidLine));//设置画笔形式
        paint.drawLine(offset,this->height()*0.6,this->width()/2,this->height()*0.75);
        paint.drawLine(this->width()/2,this->height()*0.75,this->width()*0.75,offset);
        return ;
    }
    else if(percent==-1)
    {
        txt_lab->hide();
        paint.setPen(QPen(Qt::red,8,Qt::SolidLine));//设置画笔形式
        paint.setBrush(QBrush(Qt::red,Qt::SolidPattern));
        paint.drawEllipse(10,10,recw,recw);
        paint.setPen(QPen(Qt::white,8,Qt::SolidLine));//设置画笔形式
        paint.drawLine(offset,offset,this->height()*0.75,this->height()*0.75);
        paint.drawLine(offset,this->height()*0.75,this->width()*0.75,offset);
        return ;
    }
    txt_lab->show();
    paint.setPen(QPen(Qt::gray,10,Qt::SolidLine));//灰色圆轮廓
    paint.drawEllipse(rectangle);
    paint.setPen(QPen(Qt::green,10,Qt::SolidLine));//进度圆弧
    paint.drawArc(rectangle, startAngle+25*3.6*16, -spanAngle);
    txt_lab->setText(QString::number(percent)+"%"); 
}
