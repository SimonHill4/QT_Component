#include "qncombobox.h"
#include <QCoreApplication>
#include <QDebug>
QNComBobox::QNComBobox(QWidget *parent,QRect rec, int lcd_h) :
    QWidget(parent)
{

    this->setGeometry(rec);
    lab=new QLabel(this);
    lab->setGeometry(0,0,80,this->height());
    lab->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    lab->setStyleSheet("font-size:15px;color:black");
    box=new QComboBoxReload(this, lcd_h);
	box->setMaxVisibleItems(3);
    box->setGeometry(lab->width(),0,this->width()-lab->width(),this->height());
    box->setStyleSheet(
                    "QComboBox {border:1px solid gray;padding-right: 0px;font-size:20px;}"
                    "QComboBox::drop-down {width:50px;}"
					"QComboBox QAbstractItemView::item { max-height: 20px;min-height: 20px}"
                    "QScrollBar:vertical {border: 2px solid grey;width: 15px;}");

   connect(box,SIGNAL(currentIndexChanged(int)),this,SLOT(send_current_index_change_slots(int)));

}
void QNComBobox::send_current_index_change_slots(int id)
{
    qDebug()<<"#####idx="<<id;
    emit current_Index_Change(id);
}

QNComBobox::~QNComBobox()
{
    delete lab;
    delete box;
}
void QNComBobox::setAcctive(bool flag)
{
    qDebug()<<"-------------->"<<flag;
    if(flag)
        box->setStyleSheet(
                        "QComboBox {border:2px solid red;padding-right: 0px;font-size:20px}"
                        "QComboBox::drop-down {width:50px;}"
						"QComboBox QAbstractItemView::item { max-height: 10px;min-height: 10px}"
                        "QScrollBar:vertical {border: 2px solid grey;width: 15px;}");
    else
        box->setStyleSheet(
                        "QComboBox {border:1px solid gray;padding-right: 0px;font-size:20px}"
                        "QComboBox::drop-down {width:50px;}"
						"QComboBox QAbstractItemView::item { max-height: 20px;min-height: 20px}"
                        "QScrollBar:vertical {border: 2px solid grey;width: 15px;}");
    QCoreApplication::processEvents(QEventLoop::AllEvents, 100);//通知系统去处理事件
}

void QNComBobox::setcurrentIndex(int idx)
{
     box->setCurrentIndex(idx);

}
int QNComBobox::getCurrentIndex(void)
{
    return box->currentIndex();
}

void QNComBobox::setEditable(bool flag)
{
    box->setEditable(flag);
}

void QNComBobox::setLeftText(QString txt)
{
    lab->setText(txt);
}
void QNComBobox::addItems(QStringList txtlist)
{
    box->addItems(txtlist);
}
void QNComBobox::clearItem(void)
{
    box->clear();
}
