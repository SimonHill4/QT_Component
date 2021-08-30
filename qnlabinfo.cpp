#include "qnlabinfo.h"
#include <QCoreApplication>
QNLabInfo::QNLabInfo(QWidget *parent,QRect rect) :
    QWidget(parent)
{
    title_lab=new QLabel(this);
    title_lab->setGeometry(rect.x(),rect.y(),rect.width()/4,rect.height());
    mes_lab=new QLabel(this);
    mes_lab->setGeometry(rect.x()+rect.width()/4,rect.y(),rect.width()*3/4,rect.height());
    title_lab->setStyleSheet("background-color:rgb(40,40,40);color:white;font-size:16px;font-weight:bold");
    mes_lab->setStyleSheet("background-color:rgb(120,120,120);color:white;font-size:15px;font-weight:bold");
    mes_lab->setAlignment(Qt::AlignVCenter);
}
QNLabInfo::QNLabInfo(QWidget *parent,QRect rect,bool reponseTouch):
    QWidget(parent)
{
    this->setGeometry(rect);
    title_lab=new QLabel(this);
    title_lab->setGeometry(0,0,this->width(),this->height()*2/3);
    mes_lab=new QLabel(this);
    mes_lab->setGeometry(0,this->height()*2/3,this->width(),this->height()/3);
    title_lab->setStyleSheet("background-color:rgb(120,120,120);color:white;font-size:80px;font-weight:bold");
    mes_lab->setStyleSheet("background-color:rgb(120,120,120);color:white;font-size:15px;font-weight:bold");
    mes_lab->setAlignment(Qt::AlignCenter);
    title_lab->setAlignment(Qt::AlignHCenter|Qt::AlignTop);
}

QNLabInfo:: ~QNLabInfo()
{
    delete title_lab;
    delete mes_lab;
}
void QNLabInfo::setLeftInfo(QString str)
{
    title_lab->setText(str);
}

void QNLabInfo::setRightInfo(QString str)
{
    mes_lab->setText(str);
}
void QNLabInfo::setTitleInfo(QString str)
{
    title_lab->setText(str);
}

void QNLabInfo::setMsgInfo(QString str)
{
    mes_lab->setText(str);
}
void QNLabInfo::mousePressEvent(QMouseEvent *e)
{
    title_lab->setStyleSheet("background-color:rgb(255,150,0);color:white;font-size:80px;font-weight:bold");
    mes_lab->setStyleSheet("background-color:rgb(255,150,0);color:white;font-size:15px;font-weight:bold");
}
void QNLabInfo::mouseReleaseEvent(QMouseEvent *ev)
{
    title_lab->setStyleSheet("background-color:rgb(120,120,120);color:white;font-size:80px;font-weight:bold");
    mes_lab->setStyleSheet("background-color:rgb(120,120,120);color:white;font-size:15px;font-weight:bold");
    emit labPressed();
}
