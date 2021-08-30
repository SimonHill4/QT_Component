#include "qnbutton.h"
#include <QDebug>
QNButton::QNButton(QWidget *parent,bool turnon,int row,int row_height) :
    QWidget(parent)
{
    this->setGeometry(0,0,50,25);//swich QNButton size 50*25
    if(turnon)
        QNButton_type=1;//switch QNButton type on
    else
        QNButton_type=0;//switch QNButton off
     text=QString().number(row+1);
     this->show();
     row_h=row_height;
}
QNButton::QNButton(QWidget *parent,int row,int row_height) :
    QWidget(parent)
{
        this->setGeometry(0,0,25,row_height);   //numbericon QNButton size 20*25
        QNButton_type=3;//number icon QNButton type
        text=QString().number(row+1);
        this->show();
        row_h=row_height;
}
QNButton::QNButton(QWidget *parent,QColor color,int row,int row_height,bool direction):
    QWidget(parent)
{
     this->setGeometry(0,0,50,row_height);
     QNButton_type=4;
     left_direction=direction;// < left direction // > right direction
     bt_color=color;
     text=QString().number(row+1);
     this->show();
     row_h=row_height;
}

QNButton::QNButton(QWidget *parent,bool select,QColor color,int row,int row_height):QWidget(parent)
{
   row_h=row_height;
   row_h>40?this->setGeometry(0,0,50,40):this->setGeometry(0,0,50,25);
   if(select)
        QNButton_type=5;
   else
       QNButton_type=6;
    bt_color=color;
    text=QString().number(row+1);
    this->show();
}

void QNButton::mousePressEvent(QMouseEvent *e)
{
        switch(QNButton_type)
        {
            case 1: QNButton_type=0;repaint();emit IconClicked(text.toInt());break;//change swich QNButton to close
            case 0: QNButton_type=1;repaint();emit IconClicked(text.toInt());break;//change swich QNButton to on
            default:emit IconClicked(text.toInt());break;//icon signal
        }

}

void QNButton::paintEvent(QPaintEvent *)
{
        switch(QNButton_type)
        {
            case 1:bt_color=QColor(50,205,50);break;    //switch QNButton on
            case 0:bt_color=QColor(120,120,120);break;  //switch QNButton off
            case 6: return;//non selected no need paint
        }

        QPainter painter(this);
        QFont font;
        font.setPixelSize(20);
        painter.setPen(QColor(255,255,255));
        painter.setFont(font);
        painter.setRenderHint(QPainter::Antialiasing, true);
        if(QNButton_type<3)//capsule type
        {
             QRectF rect;
            qreal radius;
            if(row_h==50)//320*480 lcd
            {
                radius = 13;
                rect = QRect(0, 10, 50, 28);
            }
            else //320*240 lcd
            {
                radius = this->height()/2;
                rect = QRect(0, 2, 50, 28);
            }

            QPainterPath path;

            path.moveTo(rect.bottomRight() - QPointF(0, radius));
            path.lineTo(rect.topRight() + QPointF(0, radius));
            path.arcTo(QRectF(QPointF(rect.topRight() - QPointF(radius * 2, 0)), QSize(radius * 2, radius *2)), 0, 90);
            path.lineTo(rect.topLeft() + QPointF(radius, 0));
            path.arcTo(QRectF(QPointF(rect.topLeft()), QSize(radius * 2, radius * 2)), 90, 90);
            path.lineTo(rect.bottomLeft() - QPointF(0, radius));
            path.arcTo(QRectF(QPointF(rect.bottomLeft() - QPointF(0, radius * 2)), QSize(radius * 2, radius * 2)), 180, 90);
            path.lineTo(rect.bottomLeft() + QPointF(radius, 0));
            path.arcTo(QRectF(QPointF(rect.bottomRight() - QPointF(radius * 2, radius * 2)), QSize(radius * 2, radius * 2)), 270, 90);
            painter.fillPath(path, bt_color);

        }
        if(QNButton_type==1)   //switch QNButton on
        {

            painter.setBrush(QBrush(Qt::white,Qt::SolidPattern));
            if(row_h==50)//320*480 lcd
                painter.drawEllipse(25,14,20,20);
            else//320*240 lcd
                painter.drawEllipse(25,6,20,20);
        }
        else if(QNButton_type==0)//switch QNButton off
        {
            painter.setBrush(QBrush(Qt::white,Qt::SolidPattern));
            if(row_h==50)//320*480 lcd
                painter.drawEllipse(4,14,20,20);
            else// 320*240 lcd
                painter.drawEllipse(4,6,20,20);
        }
        else if(QNButton_type==3)//number icon
        {
            painter.setPen(QColor(40,40,40));
            font.setPixelSize(18);
            painter.setFont(font);
            painter.setBrush(QBrush(QColor(40,40,40),Qt::SolidPattern));
           if(row_h==50)//320*480 lcd
                painter.drawEllipse(3,11,25,25);
           else//320*240 lcd
                painter.drawEllipse(3,4,25,25);
           painter.setPen(QColor(255,255,255));
           painter.drawText(QRectF(1,-1,this->width(),this->height()),Qt::AlignCenter,text);
        }
        else if(QNButton_type==4)//list have more QNButton
        {
            painter.setPen(QPen(bt_color,2));
            if(row_h==50)//320*480 lcd
            {
                if(left_direction)
                {
                    painter.drawLine(10,25,20,15);
                    painter.drawLine(10,25,20,35);
                }
                else
                {
                    painter.drawLine(30,15,40,25);
                    painter.drawLine(30,35,40,25);
                }
            }
            else//320*240 lcd
            {
                if(left_direction)
                {
                    painter.drawLine(10,13,20,8);
                    painter.drawLine(10,13,20,20);
                }
                else
                {
                    painter.drawLine(30,8,40,13);
                    painter.drawLine(30,20,40,13);
                }
            }
        }
        else if(QNButton_type==5)//list select QNButton was selected
        {
            painter.setPen(QPen(bt_color,2));
            painter.drawLine(20,row_h>40?25:18,30,row_h>40?32:25);
            painter.drawLine(45,row_h>40?15:8,30,row_h>40?32:25);
        }

}
