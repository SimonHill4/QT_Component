#include "qntitle.h"

QNTitle::QNTitle(QWidget *parent,const QPixmap *icon,const QString &QNTitle_str) :
    QWidget(parent)
{
    this->setGeometry(0,0,320,40);
    this->setAttribute(Qt::WA_StyledBackground,true);
    this->setStyleSheet("background-color:rgb(40,40,40)");
    title_height=40;
    QFont font;
    font.setPixelSize(20);
    font.setBold(true);
    QPalette pe;
    pe.setColor(QPalette::WindowText, Qt::white);

//    QPixmap *back_icon=new QPixmap(ICON_PATH"back.png");
//    back_lab=new QLabel(this);
//    back_lab->setAlignment(Qt::AlignCenter);
//    back_lab->setGeometry(280,0,20,40);
//    back_lab->setPixmap(*back_icon);
//    back_lab->setStyleSheet("background:transparent");
    rightAlign=false;
    mes_lab=new QLabel(this);
    mes_lab->setGeometry(30,0,270,40);
    mes_lab->setFont(font);
    mes_lab->setPalette(pe);
    mes_lab->setText(QNTitle_str);
    mes_lab->setStyleSheet("background:transparent");

    icon_lab=new QLabel(this);
    icon_lab->setAlignment(Qt::AlignCenter);
    icon_lab->setGeometry(5,0,20,40);
    icon_lab->setPixmap(*icon);
    icon_lab->setStyleSheet("background:transparent");


}
  QNTitle::~QNTitle()
{
    delete mes_lab;
    delete icon_lab;
}

void QNTitle::mousePressEvent(QMouseEvent *e)
{
//        if(e->x()<=20&&e->y()<=40)
//            emit goback();

}
 void QNTitle::setRight2Left(bool flag)
 {
     rightAlign=flag;
     if(flag)
     {
         mes_lab->setGeometry(0,0,290,40);
         icon_lab->setGeometry(295,0,20,40);
         //mes_lab->setAlignment(Qt::AlignRight);
         mes_lab->clear();
     }
     else
     {
         mes_lab->setGeometry(30,0,270,40);
         icon_lab->setGeometry(5,0,20,40);
         mes_lab->setAlignment(Qt::AlignLeft);
     }
 }

void QNTitle::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    //under line
    painter.setPen(QPen(QColor(255,255,255),2));
    painter.drawLine(QLine(0,35,320,35));

}
void QNTitle::upDateQNTitleIcon(const QPixmap *icon)
{
    icon_lab->setPixmap(*icon);
    this->show();
}
void QNTitle::upDateQNTitleMes(const QString &QNTitle_str)
{
  // mes_lab->setAlignment(rightAlign?Qt::AlignRight:Qt::AlignLeft);
   mes_lab->setText(QNTitle_str);
   this->show();
}
int QNTitle::get_title_height()
{
    return title_height;
}
