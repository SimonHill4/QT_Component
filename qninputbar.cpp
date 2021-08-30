#include "qninputbar.h"
#include <QDebug>

QNInputBar::QNInputBar(QWidget *parent,QRect rec,int fontsize) :
    QWidget(parent)
{
    keymap.append(" <>()&{}[]");//0
    keymap.append("qzQZ");//1
    keymap.append("abcABC");//2
    keymap.append("defDEF");//3
    keymap.append("ghiGHI");//4
    keymap.append("jklJKL");//5
    keymap.append("mnoMNO");//6
    keymap.append("prsPRS");//7
    keymap.append("tuvTUV");//8
    keymap.append("wxyWXY");//9
    keymap.append(".,@\\/+-_|%^!$:?~");//*
    alphaFlag=false;
    focusFlag=false;
    rec_size=rec;
    font_size=fontsize;
    this->setGeometry(rec_size.x(),rec_size.y()-20,rec_size.width(),rec_size.height()+20);//20 for alpha lab
    alpha_lab=new QLabel(this);
    alpha_lab->setGeometry(0,0,this->width(),20);
    alpha_lab->setStyleSheet("QLabel{font-size:15px;color:white;background-color:rgb(70,137,213)}");
    alpha_lab->hide();
    edit_outstyle=QString("QLineEdit{background-color:white;border-left-width:2px;border-top-left-radius:%1px;border-bottom-left-radius:%1px;font-size:%2px;color:black;border:2px solid gray}").arg(rec.height()/2).arg(fontsize);
    edit_instyle=QString("QLineEdit{background-color:white;border-left-width:2px;border-top-left-radius:%1px;border-bottom-left-radius:%1px;font-size:%2px;color:black;border:2px solid rgb(255,116,0)}").arg(rec.height()/2).arg(fontsize);
    qnlineedit=new QLineEdit(this);

    qnlineedit->setGeometry(0,alpha_lab->height(),rec.width()*3/4,rec.height());
    qnlineedit->setTextMargins(rec.height()/2,0,rec.height()/2,0);
    qnlineedit->setStyleSheet(edit_outstyle);
    qnlineedit->setAlignment(Qt::AlignCenter);
    connect(qnlineedit,SIGNAL(textEdited(QString)),this,SLOT(text_edited_slot(QString)));

    bt=new QPushButton(this);
    int btw=rec.width()-rec.width()*3/4;
    bt->setGeometry(rec.width()*3/4,alpha_lab->height(),btw,rec.height());
    bt->setText("Done");
    bt_outstyle=QString("QPushButton{border-width:0px;border-top-right-radius:%1px;border-bottom-right-radius:%1px;font-size:%2px;color:white;background-color:gray}").arg(rec_size.height()/2).arg(font_size);
    bt_instyle=QString("QPushButton{border-width:0px;border-top-right-radius:%1px;border-bottom-right-radius:%1px;font-size:%2px;color:white;background-color:rgb(255,116,0)}").arg(rec_size.height()/2).arg(font_size);
    bt->setStyleSheet(bt_outstyle);

    connect(bt,SIGNAL(released()),this,SLOT(send_complete_signal_slot()));
    maxlen=-1;
    echomode=true;

    qnlineedit->installEventFilter(this);//get foucsin event

}
void QNInputBar::text_edited_slot(QString newtext)
{
    QString tmptxt,endtxt,alpha_txt;
    static QString pre_txt;
    tmptxt=newtext;
    endtxt=tmptxt.right(1);
    if(endtxt=="#")//630pro 会执行此条件
    {
        alphaFlag=!alphaFlag;
        if(!alphaFlag)
            alpha_lab->hide();
        tmptxt.chop(1);
        qnlineedit->setText(tmptxt);
        return;
    }
    if(!alphaFlag)//num input
    {
        emit txtchange(newtext);
        return;
    }
    //process alpha
    static int press_times=0,keymap_index1;
    alpha_lab->isVisible()?pre_txt.chop(2):pre_txt.chop(1);
    if(pre_txt==newtext)//backkey
    {
        alpha_lab->hide();
        pre_txt=newtext;
        return;
    }
    pre_txt=newtext;
    tmptxt.chop(1);
    qnlineedit->setText(tmptxt);
    alpha_txt.clear();
    int idx;
    idx=endtxt=="*"?10:endtxt.toInt();

    //select alpha
    if(alpha_lab->isVisible())
    {
        if(idx==0||idx==10)
        {
            if(press_times==1)
                goto SHOWFIRST;
            keymap_index1=idx;
            for(int i=0;i<(keymap[idx].length()-8);i++)
                alpha_txt.append(QString("%1. %2   ").arg(i+1).arg(keymap[idx][i+8]));
            alpha_lab->setText(alpha_txt);
            alpha_lab->show();
            press_times=1;
            return;
        }
        int keymap_index2=endtxt.toInt();
        if(keymap_index2<=keymap[keymap_index1].length())
        {
            tmptxt.append(QString("%1").arg(keymap[keymap_index1][keymap_index2+8*press_times-1]));
            qnlineedit->setText(tmptxt);
            emit txtchange(tmptxt);
        }
        alpha_lab->hide();
        return;
    }
SHOWFIRST:
    //show alpha
    int len=(idx==0||idx==10)?8:keymap[idx].length();
    press_times=0;
    keymap_index1=idx;
    for(int i=0;i<len;i++)
        alpha_txt.append(QString("%1. %2   ").arg(i+1).arg(keymap[keymap_index1][i]));
    alpha_lab->setText(alpha_txt);
    alpha_lab->show();

}

QString QNInputBar::getText(void)
{
    return qnlineedit->text();
}

 void QNInputBar::setText(QString tx)
{
     qnlineedit->setText(tx);
}

void QNInputBar::send_complete_signal_slot(void)
{
    qDebug()<<"#####emit signal";
    emit enterPressed();
}

void QNInputBar::clear()
{
     qnlineedit->clear();
}

QNInputBar::~QNInputBar()
{
    delete qnlineedit;
    delete bt;
}
void QNInputBar::setMaxLength(int len)
{
     maxlen=len;
     qnlineedit->setMaxLength(maxlen);
}

void QNInputBar::setEchoMode(QLineEdit::EchoMode mode)
{
   qnlineedit->setEchoMode(mode);
}

void QNInputBar::setRemindText(QString txt)
{
    qnlineedit->setPlaceholderText(txt);
}
void QNInputBar::setDefaultText(QString txt)
{
    text=txt;
    qnlineedit->setText(text);
}

void QNInputBar::setButtonText(QString tx)
{
    bt->setText(tx);
}

void QNInputBar::setAlignment(Qt::AlignmentFlag flag)
{
   qnlineedit->setAlignment(flag);
}
void QNInputBar::hide()
{
    qnlineedit->hide();
    bt->hide();
    this->lower();
}
void QNInputBar::show()
{
     qnlineedit->show();
     bt->show();
     this->raise();
     QCoreApplication::processEvents(QEventLoop::AllEvents, 300);
}
void QNInputBar::setActive(bool flag)
{
    if(flag)
    {
        qnlineedit->setStyleSheet(edit_instyle);
        bt->setStyleSheet(bt_instyle);
         this->setFocus();
        qnlineedit->setEnabled(true);
        qnlineedit->setFocus();
        //qnlineedit->setCursorPosition(qnlineedit->text().length());

    }
    else
    {
        qnlineedit->setStyleSheet(edit_outstyle);
        bt->setStyleSheet(bt_outstyle);
        this->setFocusPolicy(Qt::NoFocus);
    }
}
bool QNInputBar::eventFilter(QObject *watched, QEvent *event)
{

    if((watched ==qnlineedit)&& event->type() == QEvent::FocusIn)
        emit gotfocus();
    return QWidget::eventFilter(watched,event);

}

void QNInputBar::keyPressEvent(QKeyEvent *ev)
{
    int key=ev->key();

    switch(key)
    {
        case Qt::Key_Escape: emit cancelPressed(); alpha_lab->hide();break;
        case Qt::Key_Percent:alphaFlag=!alphaFlag;break;
        case Qt::Key_Enter: if(alpha_lab->isVisible())
                                alpha_lab->hide();
                            else
                                emit enterPressed();
                            break;
        case Qt::Key_F1:emit golast();break;
        case Qt::Key_F2:emit gonext();break;
    }

    if(!alphaFlag)
        alpha_lab->hide();

}

