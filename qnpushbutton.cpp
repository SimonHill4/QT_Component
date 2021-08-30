#include "qnpushbutton.h"

QNPushButton::QNPushButton(QWidget *parent,QRect bt,QString txt,QColor color) :
    QWidget(parent)
{
    this->setGeometry(bt);
    col=color;
    rec=bt;
    push_bt=new QPushButton(this);
    push_bt->resize(bt.width(),bt.height());
    QString tmp=QString("QPushButton{border-width:0px;border-radius:%1px;font-size:%2px;font-weight: bold;"
                        "color:white;background-color:rgb(%3,%4,%5)}").arg(bt.height()/2).arg(bt.height()*0.6).arg(color.red()).arg(color.green()).arg(color.blue());
    push_bt->setStyleSheet(tmp);
   push_bt->setText(txt);
   connect(push_bt,SIGNAL(pressed()),this,SLOT(send_button_pressed_slot()));
   connect(push_bt,SIGNAL(released()),this,SLOT(send_button_release_slot()));
}
 QNPushButton::~QNPushButton()
 {
     delete push_bt;
 }
 void QNPushButton::send_button_pressed_slot(void)
 {
     QString tmp=QString("QPushButton{border-width:0px;border-radius:%1px;font-size:%2px;font-weight: bold;"
                         "color:white;background-color:gray}").arg(rec.height()/2).arg(rec.height()*0.6);
     push_bt->setStyleSheet(tmp);
     emit ButtonPressed();
 }

 void QNPushButton::send_button_release_slot(void)
 {
     QString tmp=QString("QPushButton{border-width:0px;border-radius:%1px;font-size:%2px;font-weight: bold;"
                         "color:white;background-color:rgb(%3,%4,%5)}").arg(rec.height()/2).arg(rec.height()*0.6).arg(col.red()).arg(col.green()).arg(col.blue());
     push_bt->setStyleSheet(tmp);
     emit ButtonRelease();
 }
 void QNPushButton::hideButton(void)
 {
     push_bt->hide();
     this->hide();
 }
 void QNPushButton::showButton(void)
 {
     push_bt->show();
     this->show();
 }
