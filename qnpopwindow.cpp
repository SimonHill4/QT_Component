#include "qnpopwindow.h"
#include <QDebug>
QNPopWindow::QNPopWindow(QWidget *parent,POPWINTYPE type,int lcd_w,int lcd_h) :
    QWidget(parent)
{
    lcd_width=lcd_w;
    lcd_height=lcd_h;
    FullScreenFlag=false;
    notifyFlag=false;
    waitFlag=false;
	warningFlag=false;
    confirmFlag=false;
    closeFlag=false;
    remindFlag=false;
    undeal_mesNum=0;
    icon_lab=NULL;
#if 0
    shadow=new QGraphicsDropShadowEffect;
    shadow->setBlurRadius(9.0);
    shadow->setColor(QColor(0, 0, 0, 160));
    shadow->setOffset(4.0);
#endif
    this->setAttribute(Qt::WA_StyledBackground,true);
    ok_btn=NULL;
    cancel_btn=NULL;
    switch (type)
    {
        case NOTIFY_WIN:
        {
            this->setGeometry(0,0,320,60);
            lab=new QLabel(this);
            lab->setGeometry(this->geometry());

            //this->setStyleSheet("background-color:rgb(91,109,117)");
            QString instyle=QString("QLabel{font-size:15px;color:white;background:transparent;}");
            lab->setStyleSheet(instyle);
            lab->setAlignment(Qt::AlignCenter);
            notifyFlag=true;//control move animation
            ani_slide=new QPropertyAnimation;
            break;
        }
        case WARNING_WIN:
        {
            this->setGeometry(0,lcd_h==480?lcd_h/2-100:60,lcd_w,lcd_h==480?120:100);
            this->setStyleSheet("background-color:rgb(91,109,117)");
            lab=new QLabel(this);
            lab->setGeometry(0,0,this->width(),this->height());
            lab->setStyleSheet("background:transparent;color:white;font-size:15px;font-weight:bold");
            lab->setAlignment(Qt::AlignCenter);
            warningFlag=true;
            break;
        }
        case CONFIRM_WIN:
        {
            confirmFlag=true;
            this->setGeometry(lcd_w/2-125,lcd_h/2-75,250,150);
            this->setStyleSheet("background-color:rgb(100,100,100)");
            lab=new QLabel(this);
            lab->setGeometry(0,0,this->width(),this->height()-40);//40 for button
            lab->setAlignment(Qt::AlignCenter);
            ok_btn=new QPushButton(this);
            cancel_btn=new QPushButton(this);
            ok_btn->setGeometry(lab->width()/2,lab->height(),lab->width()/2,40);
            cancel_btn->setGeometry(0,lab->height(),lab->width()/2,40);
            lab->setStyleSheet("background:transparent;color:white;font-size:15px;font-weight:bold");
            ok_btn->setStyleSheet("QPushButton{border-width:0px;border-style:dashed;border-top-width:1;font-size:20px;font-weight:bold;color:white;background:transparent}");

            cancel_btn->setStyleSheet("QPushButton{border-width:0px;border-style:dashed;border-top-width:1;border-right-width:1;font-size:20px;font-weight:bold;color:white;background:transparent}");
            ok_btn->setDefault(false);
            cancel_btn->setDefault(false);
            ok_btn->setText("OK");
            cancel_btn->setText("Cancel");
            connect(ok_btn,SIGNAL(pressed()),this,SLOT(send_buttonPress_signal_slot()));
            connect(cancel_btn,SIGNAL(pressed()),this,SLOT(send_buttonPress_signal_slot()));
            connect(ok_btn,SIGNAL(released()),this,SLOT(button_release_slot()));
            connect(cancel_btn,SIGNAL(released()),this,SLOT(button_release_slot()));
            break;
        }
        case CLOSE_WIN:
        {
            closeFlag=true;
            this->setGeometry(lcd_w/2-120,lcd_h/2-60,240,120);
            this->setStyleSheet("background-color:rgb(69,75,78)");
            lab=new QLabel(this);
            lab->setGeometry(80,0,this->width()-80,this->height()-40);
            lab->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
            icon_lab=new QLabel(this);
            icon_lab->setGeometry(0,0,80,80);
            icon_lab->setStyleSheet("background-color:transparent");
            close_btn=new QPushButton(this);
            close_btn->setGeometry(0,this->height()-40,this->width(),40);
            lab->setStyleSheet("background:transparent;color:white;font-size:15px;");
            close_btn->setStyleSheet("QPushButton{border-width:0px;border-style:solid;border-top-width:1;font-size:20px;color:white;background:transparent}");
            close_btn->setDefault(false);
            close_btn->setText("Close");
            connect(close_btn,SIGNAL(pressed()),this,SLOT(send_buttonPress_signal_slot()));
            connect(close_btn,SIGNAL(released()),this,SLOT(button_release_slot()));
            break;
        }
        case REMIND_WIN:
        {
            remindFlag=true;
            this->setGeometry(40,0,240,50);
            this->setStyleSheet("background-color:rgb(69,75,78)");
            lab=new QLabel(this);
            lab->setGeometry(50,0,165,50);
            lab->setStyleSheet("QLabel{background-color:transparent;font-size:20px;color:white;}");
            icon_lab=new QLabel(this);
            icon_lab->setGeometry(15,0,50,50);
            icon_lab->setStyleSheet("QLabel{background-color:transparent;}");
            lab->setAlignment(Qt::AlignCenter);
            break;
        }
    }


    hideWindow();//default hide, if need show,it will need call popWondow
}
void QNPopWindow::send_buttonPress_signal_slot(void)
{
  QPushButton *tmp=qobject_cast<QPushButton *> (sender());
  if(tmp==ok_btn)
  {
        tmp->setStyleSheet("QPushButton{border-width:0px;border-style:dashed;border-top-width:1;font-size:20px;font-weight:bold;color:white;background-color:rgb(255,116,0)}");
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);//通知系统去处理事件
        emit buttonPressed(true);
  }
  else if(tmp==cancel_btn)
  {
      tmp->setStyleSheet("QPushButton{border-width:0px;border-style:dashed;border-top-width:1;border-right-width:1;font-size:20px;font-weight:bold;color:white;background-color:rgb(255,116,0)}");
      QCoreApplication::processEvents(QEventLoop::AllEvents, 100);//通知系统去处理事件
      emit buttonPressed(false);
  }
  else if(tmp==close_btn)
  {
      tmp->setStyleSheet("QPushButton{border-width:0px;border-style:solid;border-top-width:1;font-size:15px;color:white;background-color:rgb(255,116,0)}");
      QCoreApplication::processEvents(QEventLoop::AllEvents, 100);//通知系统去处理事件
      emit buttonPressed(true);
  }

}
void QNPopWindow::button_release_slot(void)
{
    QPushButton *tmp=qobject_cast<QPushButton *> (sender());
    if(tmp==ok_btn)
        tmp->setStyleSheet("QPushButton{border-width:0px;border-style:dashed;border-top-width:1;font-size:20px;font-weight:bold;color:white;background:transparent}");
    else if(tmp==cancel_btn)
        tmp->setStyleSheet("QPushButton{border-width:0px;border-style:dashed;border-top-width:1;border-right-width:1;font-size:20px;font-weight:bold;color:white;background:transparent}");
    else if(tmp==close_btn)
        close_btn->setStyleSheet("QPushButton{border-width:0px;border-style:solid;border-top-width:1;font-size:15px;color:white;background:transparent}");

}

//FULL SCREEN INFO WITH BURRY BAKCGROUND
QNPopWindow::QNPopWindow(QWidget *parent,QRect rec,QNListInfo *list_widget) :
    QWidget(parent)
{

    burry_bg=list_widget;
    FullScreenFlag=true;
    notifyFlag=false;
    waitFlag=false;
    warningFlag=false;
    confirmFlag=false;
    closeFlag=false;
    remindFlag=false;
    ok_btn=NULL;
    cancel_btn=NULL;
    this->setGeometry(rec);
    this->setStyleSheet("background:transparent");
    plaintext=new QPlainTextEdit(this);
    plaintext->setHidden(true);
    plaintext->setReadOnly(true);
    plaintext->setGeometry(0,0,this->width(),this->height());
    plaintext->setStyleSheet("background-color:white;color:black;font-size:20px");
    //plaintext->setAlignment(Qt::AlignLeft);
    hideWindow();//default hide, if need show,it will need call popWondow
}
void QNPopWindow::popWindow(void)
{   
    this->raise();
    this->show();
    this->setFocus();
    keyrecorder=0;// clean key buf
    if(!FullScreenFlag)
    {
         lab->show();
    }
    if(confirmFlag)
    {
        ok_btn->show();
        ok_btn->setStyleSheet("QPushButton{border-width:0px;border-style:dashed;border-top-width:1;font-size:20px;font-weight:bold;color:white;background:transparent}");
        cancel_btn->show();
        cancel_btn->setStyleSheet("QPushButton{border-width:0px;border-style:dashed;border-top-width:1;border-right-width:1;font-size:20px;font-weight:bold;color:white;background:transparent}");
    }
    if(closeFlag)
    {
        close_btn->setStyleSheet("QPushButton{border-width:0px;border-style:solid;border-top-width:1;font-size:15px;color:white;background:transparent}");
        close_btn->show();
        icon_lab->show();
    }
    if(remindFlag)
    {
      icon_lab->show();
      lab->show();
    }
   if(notifyFlag)//from top to postion
    {
        ani_slide->setTargetObject(this);
        ani_slide->setPropertyName("pos");
        ani_slide->setDuration(500);
        ani_slide->setStartValue(QPoint(this->x(),-this->height()));
        ani_slide->setEndValue(QPoint(this->x(),this->y()));
        ani_slide->start();
    }
    if(FullScreenFlag)
    {
        plaintext->show();
        QCoreApplication::processEvents(QEventLoop::AllEvents, 300);//通知系统去处理事件
        return ;
    }

}
void QNPopWindow::hideWindow(void)
{
    this->setWindowModality(Qt::NonModal);
    this->hide();
    this->releaseMouse();
    if(FullScreenFlag)
        plaintext->hide();
    else
        lab->hide();
    if(ok_btn)
        ok_btn->hide();
    if(cancel_btn)
        cancel_btn->hide();
    if(closeFlag)
    {
        close_btn->hide();
        icon_lab->hide();
    }

    this->setFocusPolicy(Qt::NoFocus);
}

void QNPopWindow::setFont(const QFont &font)
{
    lab->setFont(font);
}
void QNPopWindow::setBackGround(QColor c)
{

    lab->setAttribute(Qt::WA_StyledBackground,true);
    QString str=QString("background-color:rgb(%1,%2,%3)").arg(c.red()).arg(c.green()).arg(c.blue());
    lab->setStyleSheet(str);
}
int QNPopWindow::get_key(void)
{
    return keyrecorder;
}
 void QNPopWindow::clear_keybuf(void)
 {
     keyrecorder=0;
 }

void QNPopWindow::mousePressEvent(QMouseEvent * ev)
{
    if(!notifyFlag)
        return;
    emit anyKeyPressed(true);
}

void QNPopWindow::keyPressEvent(QKeyEvent *ev)
{

    keyrecorder=ev->key();
    //loop.quit();
    if(waitFlag)//if need wait logic function completed, any key presss should ignore
        return;
    switch(keyrecorder)
    {
        case Qt::Key_Enter:emit buttonPressed(true);anyKeyPressed(true);break;
        case Qt::Key_Escape:emit buttonPressed(false);emit cancelPressed();emit anyKeyPressed(false);break;
        default: emit anyKeyPressed(true);break;
    }
    if(FullScreenFlag)
        movePlainTextSliderPosition();
}
 void QNPopWindow::setMessage(QString str,int type)
{
    if(FullScreenFlag)
    {
        plaintext->clear();
        plaintext->appendPlainText(str);
        QCoreApplication::processEvents(QEventLoop::AllEvents, 200);//reflesh
        return;
    }
    if(remindFlag==false)
    {
        switch(type)
        {
            case 0:   lab->setStyleSheet("background-color:rgb(2,171,72);color:white;font-size:15px;font-weight:bold");break;//succeed
            case 1:   closeFlag?lab->setStyleSheet("background:transparent;color:white;font-size:15px"):lab->setStyleSheet("background-color:rgb(120,120,120);color:white;font-size:15px");break;//process
            case -1:  lab->setStyleSheet("background-color:rgb(255,0,0);color:white;font-size:15px;font-weight:bold");break;//error
        }
    }
    lab->clear();
    lab->setText(str);
    QCoreApplication::processEvents(QEventLoop::AllEvents, 200);//reflesh
}
void QNPopWindow::appendMessage(QString str,int type)
{
    if(FullScreenFlag)
    {
        plaintext->appendPlainText(str);
        QCoreApplication::processEvents(QEventLoop::AllEvents, 200);//reflesh
        return;
    }
    QString tmp;
    switch(type)
    {
        case 0:   lab->setStyleSheet("background-color:rgb(2,171,72);color:white;font-size:15px;font-weight:bold");break;//succeed
        case 1:   lab->setStyleSheet("background-color:rgb(91,109,117);color:white;font-size:15px;font-weight:bold");break;//process
        case -1:  lab->setStyleSheet("background-color:rgb(255,0,0);color:white;font-size:15px;font-weight:bold");break;//error
    }
    tmp=lab->text();
    tmp.append(str);
    lab->clear();
    lab->setText(tmp);
    QCoreApplication::processEvents(QEventLoop::AllEvents, 200);//reflesh
}
 void QNPopWindow::clearMessage(void)
 {
     if(FullScreenFlag)
     {
         plaintext->clear();
         return;
     }
     lab->clear();
 }

 void QNPopWindow::setWaitFlag(void)
 {

     waitFlag=true;
     qDebug()<<"==========>flag"<<waitFlag;
 }

 void QNPopWindow::clearWaitFlag(void)
 {
     waitFlag=false;
     keyrecorder=0;
 }

QNPopWindow::~QNPopWindow()
{
    delete lab;
}
void QNPopWindow::movePlainTextSliderPosition(void)
{
    int sliderPosition = 0;

    int minPosition = (plaintext->verticalScrollBar())->minimum();
    int maxPosition = (plaintext->verticalScrollBar())->maximum();


    qDebug("minimum = %d", (plaintext->verticalScrollBar())->minimum());
    qDebug("maximum = %d", (plaintext->verticalScrollBar())->maximum());

        sliderPosition = (plaintext->verticalScrollBar())->sliderPosition();
        switch (keyrecorder)
        {
            case Qt::Key_Percent:
            case Qt::Key_F2:
                if (sliderPosition < maxPosition)
                {
                    sliderPosition += 1;
                    (plaintext->verticalScrollBar())->setSliderPosition(sliderPosition);
                }

                break;

            case Qt::Key_Asterisk:
            case Qt::Key_F1:
                if (sliderPosition > minPosition)
                {
                    sliderPosition -= 1;
                    (plaintext->verticalScrollBar())->setSliderPosition(sliderPosition);
                }

                break;
            default:
                break;
        }


}
 void QNPopWindow::set_undeal_message_num(int num)
 {
    undeal_mesNum=num;
    update();
 }
 void QNPopWindow::paintEvent(QPaintEvent *e)
{
    if(!closeFlag)
        return;
     QPainterPath path;
     path.moveTo(this->width(),0);
     path.arcTo(this->width()-30,-30,60,60,180,90);
     QPainter painter(this);
     QFont font;
     font.setPixelSize(20);
     painter.setPen(undeal_mesNum==0?QColor(69,75,78):QColor(255,0,0));
     painter.setFont(font);
     painter.setRenderHint(QPainter::Antialiasing, true);

     painter.setBrush(QBrush(undeal_mesNum==0?QColor(69,75,78):QColor(255,0,0),Qt::SolidPattern));
     painter.drawPath(path);
     if(undeal_mesNum>0)
     {
         painter.setPen(QColor(255,255,255));
         painter.drawText(QRectF(this->width()-20,0,20,20),Qt::AlignCenter,QString::number(undeal_mesNum));
     }


}
void QNPopWindow::setConfirmWin_button_txt(QString oktxt,QString canceltxt)
{
    oktext=oktxt;
      ok_btn->setText(oktext);
    canceltext=canceltxt;
    cancel_btn->setText(canceltext);
}

void QNPopWindow::setColseWin_button_txt(QString txt)
{
    closetext=txt;
    close_btn->setText(closetext);
}
void QNPopWindow::setCloseWin_icon(QPixmap &icon)
{
    if(icon_lab==NULL)
        return;
    icon_lab->setPixmap(icon);
}
void QNPopWindow::setRemindWin_icon(QPixmap &icon)
{
    if(icon_lab==NULL)
        return;
    icon_lab->setPixmap(icon);
}
