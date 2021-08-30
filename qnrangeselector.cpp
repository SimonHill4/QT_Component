#include "qnrangeselector.h"

QNRangeSelector::QNRangeSelector(QWidget *parent,const int &x,const int &y,const int &default_idx, QList<QString> &value) :
    QWidget(parent)
{
    homingAni  = new QPropertyAnimation(this,"deviation");
    homingAni->setDuration(300);
    homingAni->setEasingCurve(QEasingCurve::OutQuad);
    //this->setGeometry(80,115,160,250);
   this->setGeometry(x,y,80,120);
    setRange(0,value.count(),default_idx);
    range_value=value;
    pos_x=x;
    pos_y=y;
    this->setAttribute(Qt::WA_StyledBackground,true);
    this->setStyleSheet("background-color: rgb(120,120,120)");
    //this->show();
  //  fontSize=height()-1;
}
void QNRangeSelector::resetGeometry(const QRect &r)
{
    this->setGeometry(r);
}
 void QNRangeSelector::upDateRangeList(QList<QString> &value,const int &default_idx)
 {
     range_value.clear();
     range_value=value;
     setRange(0,value.count(),default_idx);
      this->show();
 }

QNRangeSelector::~QNRangeSelector()
{
    delete homingAni;
}
void QNRangeSelector::keyPressEvent(QKeyEvent *ev)
{
    switch(ev->key())
    {
         case Qt::Key_Asterisk:
         case Qt::Key_F1:
         {
               if(m_currentValue == m_minRange)//limit move over to the top edge
                         return;
                m_deviation=this->height()/4;
                repaint();
                emit deviationChange((float)m_deviation/((height()-1)/4));
                emit currentValueChanged(m_currentValue);
                break;
         }
         case Qt::Key_Percent:
         case Qt::Key_F2:
         {
               if(m_currentValue == m_maxRange)//limit move over to the down edge
                        return;
               m_deviation=0-this->height()/4;
               repaint();
               emit deviationChange((float)m_deviation/((height()-1)/4));
               emit currentValueChanged(m_currentValue);
               break;
         }
        case Qt::Key_F3:    //change focus
        {
             emit tabPressed(m_currentValue);
             break;
        }
        case Qt::Key_Enter:
        {
                emit enterPressed(m_currentValue);
                break;
        }
        case Qt::Key_Escape:
       {
                emit cancelPressed();
                break;
       }
    }
}

void QNRangeSelector::setRange(int min,int max,int current)
{
    m_minRange = min;
    m_maxRange = max-1;
    m_currentValue=current;
    m_deviation=0;
    if(m_currentValue < min)
        m_currentValue = min;
    if(m_currentValue > max-1)
        m_currentValue = max-1;

    //计算字符尺寸
    m_numSize = 2;//size of word
    int temp = m_maxRange;
    while(temp > 0)
    {
        temp /= 10;
        m_numSize++;
    }

    repaint();
}

int QNRangeSelector::currentValue()
{
    return m_currentValue;
}

void QNRangeSelector::mousePressEvent(QMouseEvent *e)
{

    homingAni->stop();
    isDragging = 1;
    m_mouseSrcPos = e->pos().y();
}

void QNRangeSelector::mouseMoveEvent(QMouseEvent *e)
{
    if(isDragging)
    {
        //数值到边界时，阻止继续往对应方向移动
        if((m_currentValue == m_minRange && e->pos().y() >= m_mouseSrcPos)||
          (m_currentValue == m_maxRange && e->pos().y() <= m_mouseSrcPos))
            return;

        m_deviation = e->pos().y() - m_mouseSrcPos;

        //若移动速度过快时进行限制
        if(m_deviation > (height()-1)/4)
            m_deviation = (height()-1)/4;
        else if(m_deviation < -(height()-1)/4)
            m_deviation = -(height()-1)/4;

        emit deviationChange((float)m_deviation/((height()-1)/4));

        repaint();
    }
}

void QNRangeSelector::mouseReleaseEvent(QMouseEvent *)
{
    if(isDragging)
    {
        isDragging = 0;
        homing();
    }
}

void QNRangeSelector::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    int Width = width()-1;
    int Height = height()-1;

    if(m_deviation >= Height/4 && m_currentValue > m_minRange)
    {
        m_mouseSrcPos += Height/4;
        m_deviation -= Height/4;
        m_currentValue -= 1;
    }
    if(m_deviation <= -Width/4 && m_currentValue < m_maxRange)
    {
        m_mouseSrcPos -= Height/4;
        m_deviation += Height/4;
        m_currentValue += 1;
    }

    //cureent string
    paintString(painter,range_value[m_currentValue],m_deviation,true);

    //previous string and next string
    if(m_currentValue != m_minRange)
        paintString(painter,range_value[m_currentValue-1],m_deviation-Height/4,false);
    if(m_currentValue != m_maxRange)
        paintString(painter,range_value[m_currentValue+1],m_deviation+Height/4,false);
#if 0
    //两侧数字2,超出则不显示
    if(m_deviation >= 0 && m_currentValue-2 >= m_minRange)
        paintNum(painter,m_currentValue-2,m_deviation-Height/2);
    if(m_deviation <= 0 && m_currentValue+2 <= m_maxRange)
        paintNum(painter,m_currentValue+2,m_deviation+Height/2);
#endif
    //边框
    painter.setPen(QPen(QColor(255,255,255),3));
    painter.drawLine(10,this->height()/3,this->width()-10,this->height()/3);
    painter.drawLine(10,this->height()*2/3,this->width()-10,this->height()*2/3);

}

void QNRangeSelector::paintString(QPainter &painter,QString str,int deviation,bool center)
{
    int scare;
    str.count()>6?scare=2.0:scare=1;
    int Height = height()-1;//40;
    int size = (Height - qAbs(scare*deviation))/m_numSize;
    int transparency = 255-510*qAbs(deviation)/Height;

    int y = 40+1.2*deviation;//Height/2+deviation-high/2;

    QFont font;
    if(center)
     {
            font.setPixelSize(size/scare);
            painter.setPen(QColor(255,255,255,transparency));
      }
    else
    {
            font.setPixelSize(size*0.8);
            painter.setPen(QColor(255,255,255,transparency));
     }
    painter.setFont(font);
    painter.drawText(QRectF((float)(this->width()/80)*(-20),y-40,Height,Height),Qt::AlignCenter,str);
    //painter.drawText(QRectF(()-20,y-40,Height,Height),Qt::AlignCenter,str);
}

void QNRangeSelector::homing()
{
    //将数字矫正到中心
    if(m_deviation > width()/8)
    {
        homingAni->setStartValue((width()-1)/8-m_deviation);
        homingAni->setEndValue(0);
        m_currentValue--;
    }
    else if(m_deviation > -width()/8)
    {
        homingAni->setStartValue(m_deviation);
        homingAni->setEndValue(0);
    }
    else if(m_deviation < -width()/8)
    {
        homingAni->setStartValue(-(width()-1)/8-m_deviation);
        homingAni->setEndValue(0);
        m_currentValue++;
    }
    emit currentValueChanged(m_currentValue);
    homingAni->start();
}

int QNRangeSelector::readDeviation()
{
    return m_deviation;
}

void QNRangeSelector::setDeviation(int n)
{
    m_deviation = n;
    repaint();
}
void QNRangeSelector::setBackgroundColor(QColor c)
{
    this->setAttribute(Qt::WA_StyledBackground,true);
    QString str=QString("background-color:rgb(%1,%2,%3)").arg(c.red()).arg(c.green()).arg(c.blue());
    this->setStyleSheet(str);
}
