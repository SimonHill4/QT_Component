#include <sys/time.h>
#include <unistd.h>
#include <QDebug>
#include "desklistwidget.h"
#include <QCoreApplication>

DeskListWidget::DeskListWidget(QWidget *parent,int w,int h,bool statusBarTop) :
    QListWidget(parent)
{
    this->setGeometry(0,0,w,h);
    if(h==450)
        this->setIconSize(QSize(80,80));//icon size 60*60
   else
       this->setIconSize(QSize(60,60));//icon size 60*60
    icon_w=(h==450?80:60);

	this->setLayoutMode(QListView::Batched);
	this->setBatchSize(4);
    this->setWordWrap(true);
    h==450?this->setSpacing(15):this->setSpacing(10);
    this->setViewMode(QListView::IconMode);
    this->setMovement(QListView::Static);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setFrameShape(QListWidget::NoFrame);
    this->setMouseTracking(true);
    if(h==450)
        this->setStyleSheet("font-size:15px;background:transparent");
    else
        this->setStyleSheet("font-size:13px;background:transparent");
    mouse_press_x=0;
    lcd_w=w;
    mouseTrackFlag=true;
    current_item=0;//default first item
    this->raise();
    last_key=0;
    ignoreKeyFlag=false;
}
void DeskListWidget::showListWidget()
{ 
    this->show();
    QCoreApplication::processEvents(QEventLoop::AllEvents, 3000);//通知系统去处理事件
    emit goNextItem(current_item);
    this->setFocus();
}
void DeskListWidget::hideListWidget()
{
    this->hide();
    this->setFocusPolicy(Qt::NoFocus);
}
int DeskListWidget::itemCount()
{
    return item_count;
}

void DeskListWidget::setItemCount(int num)
{
    item_count=num;
}

void DeskListWidget::setMouseAvaliable(bool enable)
{
    mouseTrackFlag=enable;
}

void DeskListWidget::mousePressEvent(QMouseEvent * ev)
{

    mouse_press_x=ev->x();
}

void DeskListWidget::mouseReleaseEvent(QMouseEvent *ev)
{
    int tmp_x,tmp_y;
    tmp_x=ev->x();
    tmp_y=ev->y();
//qDebug()<<"===>x="<<tmp_x<<"tmp_y"<<tmp_y;
    if(qAbs(tmp_x-mouse_press_x)<icon_w) //press action not pull action
    {
        for(int i=0;i<(icon_w==80?3:4);i++)
        {
            if(tmp_x>=((i+1)*15+i*icon_w)&&tmp_x<=(i+1)*(icon_w+15)) //column
            {
                if(tmp_y>=15&&tmp_y<=(icon_w+15))
               {
                    if(i<item_count)
                        current_item=i;
                    emit deskItemClick(i);  //first row
               }
                else if(tmp_y>=(icon_w==80?135:100)&&tmp_y<=(icon_w==80?210:160))
                {
                    if((icon_w==80?3:4)+i<item_count)
                        current_item=(icon_w==80?3:4)+i;
                    emit deskItemClick((icon_w==80?3:4)+i);//second row
                }
                else if(tmp_y>=250&&tmp_y<325)
                {
                    if((icon_w==80?6:8)+i<item_count)
                        current_item=(icon_w==80?6:8)+i;
                    emit deskItemClick((icon_w==80?6:8)+i);//third row
                }
            }
       }
     }
     mouse_press_x=0;
}

void DeskListWidget::mouseMoveEvent(QMouseEvent *ev)
{
    if(!mouseTrackFlag||ignoreKeyFlag) //lose mouse focus just need return
        return ;
    if(mouse_press_x)
    {
        devition=ev->x()-mouse_press_x;
        if(devition>=lcd_w/4||(lcd_w/4+devition<=0))
        {
            mouse_press_x=0;
            emit pageNeedChange(devition);
        }
    }

}
void DeskListWidget::ignoreKeyPress(bool flag)
{
    ignoreKeyFlag=flag;

}
 void DeskListWidget::setPageIndex(int num)
 {
     pageIndex=num;
 }

void DeskListWidget::keyPressEvent(QKeyEvent *ev)
{
    if(ignoreKeyFlag)
    {
        return;
    }
	static struct timeval prevTime, currTime;
	unsigned long interval = 0; 

	switch(ev->key())
    {
        case Qt::Key_F2:
        {
           current_item+1<item_count?current_item+=1:current_item=0;
           emit goNextItem(current_item);
           break;
        }
        case Qt::Key_F1:
        {

            current_item>0?current_item-=1:current_item=item_count-1;
            emit goNextItem(current_item);
            break;
        }

        case Qt::Key_F4:

			emit pageNeedChange(-lcd_w/4);break;
		case Qt::Key_F3:

			emit pageNeedChange(lcd_w/4);break;
		case Qt::Key_Enter:
            emit enterCurrentItem(current_item);break;
		case Qt::Key_Escape:

			emit pageNeedChange(-lcd_w/4); break;
		case Qt::Key_Asterisk:
			gettimeofday(&prevTime, NULL);
            current_item>0?current_item-=1:current_item=(item_count==0?item_count:item_count-1);
            emit goNextItem(current_item);
			break;
		case Qt::Key_Percent:
		{

            gettimeofday(&currTime, NULL);
            /* convert second unit to usec unit */
            interval = (currTime.tv_sec - prevTime.tv_sec) * 1000000;
            interval += (currTime.tv_usec - prevTime.tv_usec);
            if (pageIndex!=0&&interval < 1000000)
                emit pageNeedChange(lcd_w/4);
            else
            {
                current_item+1<item_count?current_item+=1:current_item=0;
                qDebug()<<"###########PAGE INDX"<<pageIndex<<"current_item"<<current_item;
                emit goNextItem(current_item);
            }
            break;
		}
        case Qt::Key_1:
        {
            if(item_count>=1)
            {
                current_item=0;
                emit goNextItem(current_item);
                emit enterCurrentItem(current_item);
            }
            break;
        }
        case Qt::Key_2:
        {
            if(item_count>=2)
            {
                current_item=1;
                emit goNextItem(current_item);
                emit enterCurrentItem(current_item);
            }
            break;
        }
        case Qt::Key_3:
        {
            if(item_count>=3)
            {
                current_item=2;
                emit goNextItem(current_item);
                emit enterCurrentItem(current_item);
            }
            break;
        }
        case Qt::Key_4:
        {
            if(item_count>=4)
            {
                current_item=3;
                emit goNextItem(current_item);
                emit enterCurrentItem(current_item);
            }
            break;
        }
        case Qt::Key_5:
        {
            if(item_count>=5)
            {
                current_item=4;
                emit goNextItem(current_item);
                emit enterCurrentItem(current_item);
            }
            break;
        }
        case Qt::Key_6:
        {
            if(item_count>=6)
            {
                current_item=5;
                emit goNextItem(current_item);
                emit enterCurrentItem(current_item);
            }
            break;
        }
        case Qt::Key_7:
        {
            if(item_count>=7)
            {
                current_item=6;
                emit goNextItem(current_item);
                emit enterCurrentItem(current_item);
            }
            break;
        }
        case Qt::Key_8:
        {
            if(item_count>=8)
            {
                current_item=7;
                emit goNextItem(current_item);
                emit enterCurrentItem(current_item);
            }
            break;
        }
        case Qt::Key_9:
        {
            if(item_count>=9)
            {
                current_item=8;
                emit goNextItem(current_item);
                emit enterCurrentItem(current_item);
            }
            break;
        }
	}
}
