#include "qndesktop.h"
#include <QDebug>


QNDesktop::QNDesktop(int sysAppCount, QWidget *parent, QRect rec, bool dev_type) :
    QWidget(parent)
{
    this->setGeometry(rec);
    this->setAttribute(Qt::WA_StyledBackground,true);
    this->setStyleSheet("background-color:white");
    this->setMouseTracking(true);
    rect=rec;
    sysAppNum=sysAppCount;

    lcd_w = rec.width();
    lcd_h = rec.height();
	qDebug("lcd_w = %d, lcd_h = %d\n", lcd_w, lcd_h);
    stausbar_pos_top = true;
    fw_type=dev_type;
    page_num=1;//firt page for system app
    DeskListWidget *first_page = new DeskListWidget(this,lcd_w,lcd_h,stausbar_pos_top);
    first_page->setItemCount(sysAppCount);//6  system app
    connect(first_page,SIGNAL(pageNeedChange(int)),this,SLOT(page_change_slot(int)));
    connect(first_page,SIGNAL(deskItemClick(int)),this,SLOT(send_itemClickedSignal_slot(int)));
    connect(first_page,SIGNAL(goNextItem(int)),this,SLOT(go_nextItem_slot(int)));
    connect(first_page,SIGNAL(enterCurrentItem(int)),this,SLOT(enter_currentItem_slot(int)));
    first_page->setPageIndex(0);
    pages.append(first_page);

    page_lab=new QLabel(this);
    if(fw_type!=true)//dev
    {
        watermark_lab=new QLabel(this);
        watermark_lab->setGeometry(rec);
        watermark_lab->setStyleSheet("background:transparent");
        watermark_lab->setPixmap(QPixmap(WATERMARK_PATH));
        watermark_lab->lower();
    }
    else
        watermark_lab=NULL;
    noapp_lab=new QLabel(this);
    lcd_h==450?noapp_lab->setGeometry(0,rec.height()/2-100,rec.width(),100):noapp_lab->setGeometry(0,rec.height()/2-40,rec.width(),80);
    lcd_h==450?applimit=9:applimit=8;
    noapp_lab->setStyleSheet("background-color:rgb(0,0,255);color:white;font-size:20px;");
    noapp_lab->setAlignment(Qt::AlignCenter);

    noapp_lab->hide();
    if(stausbar_pos_top)
        page_lab->setGeometry(this->width()/2-PAGE_LAB_W/2,lcd_h-20,PAGE_LAB_W,10);//lab hight=10
    else
        page_lab->setGeometry(this->width()/2-PAGE_LAB_W/2,10,PAGE_LAB_W,10);
    current_page_idx=1;//default in the first page
    ignoreSignalFlag=false;
    page_lab->installEventFilter(this);//安装事件过滤器,捕捉绘图事件
}
 void QNDesktop::setNoAppMes(QString txt)
 {
    noapp_mes=txt;
    noapp_lab->setText(noapp_mes);
 }
void QNDesktop::setFwType(bool pro)
{
    fw_type=pro;
}
void QNDesktop::setFocus(bool focus)
{
    if(focus)
    {
        pages[current_page_idx]->setFocus();
        pages[current_page_idx]->setMouseAvaliable(true);
    }
    else
       pages[current_page_idx]->setMouseAvaliable(false);//lose focus need widget lose mouse event

}
 void QNDesktop::ignoreSignal(bool flag)
 {
    if(ignoreSignalFlag==flag)
         return;

    ignoreSignalFlag=flag;
    pages[current_page_idx]->ignoreKeyPress(flag);
    if(flag)
    {
        disconnect(pages[current_page_idx],0,0,0);
    }
    else
    {
        pages[current_page_idx]->showListWidget();
        connect(pages[current_page_idx],SIGNAL(pageNeedChange(int)),this,SLOT(page_change_slot(int)));
        connect(pages[current_page_idx],SIGNAL(deskItemClick(int)),this,SLOT(send_itemClickedSignal_slot(int)));
        connect(pages[current_page_idx],SIGNAL(goNextItem(int)),this,SLOT(go_nextItem_slot(int)));
        connect(pages[current_page_idx],SIGNAL(enterCurrentItem(int)),this,SLOT(enter_currentItem_slot(int)));
    }

 }

void QNDesktop::page_change_slot(int devition)
{
    if(devition>0&&current_page_idx>0)//go left page and have left page
    {
         pages[current_page_idx]->hideListWidget();
         pages[--current_page_idx]->showListWidget();
    }
    else if(devition<0&&current_page_idx<page_num-1)//go right page and have right page
    {
        if(current_page_idx==0)//leave sys app page,need clear passwd verify
            emit clearPasswdVerify();
        pages[current_page_idx]->hideListWidget();
        pages[++current_page_idx]->showListWidget();

    }
    (pageitems.count()==sysAppNum&&current_page_idx==1)?noapp_lab->show():noapp_lab->hide();
    if(!fw_type)
        (watermark_lab!=NULL&&current_page_idx!=0)?watermark_lab->show():watermark_lab->hide();
}

QNDesktop::~QNDesktop()
{
    delete page_lab;
    for(int i=0;i<pages.count();i++)
        delete pages[i];

}

 void QNDesktop::setBackGround(QColor c)
{
     this->setAttribute(Qt::WA_StyledBackground,true);
     QString str=QString("background-color:rgb(%1,%2,%3)").arg(c.red()).arg(c.green()).arg(c.blue());
     this->setStyleSheet(str);
}


/*if have new app installed it, just need re-invoked this function*/
void QNDesktop::loadItems(QList<QListWidgetItem *> &items, int sysAppCount)
{
    pageitems.clear();
    pageitems = items;
    sysAppNum=sysAppCount;

    int appnum = items.count();
	qDebug("item count = %d", appnum);
    if(appnum==sysAppCount&&current_page_idx==1)
        noapp_lab->show();
    else
        noapp_lab->hide();
  
    //first page widget
    for(int i = 0; i < sysAppCount; i++)
    {
        pages[0]->addItem(items[i]);
    }
    //second page widget

    if(page_num<2)//for new install app, no need create page again
    {
        DeskListWidget *second_page=new DeskListWidget(this,lcd_w,lcd_h,stausbar_pos_top);
        //second_page->setItemCount(appnum - sysAppCount);
        connect(second_page,SIGNAL(pageNeedChange(int)),this,SLOT(page_change_slot(int)));
        connect(second_page,SIGNAL(deskItemClick(int)),this,SLOT(send_itemClickedSignal_slot(int)));
        connect(second_page,SIGNAL(goNextItem(int)),this,SLOT(go_nextItem_slot(int)));
        connect(second_page,SIGNAL(enterCurrentItem(int)),this,SLOT(enter_currentItem_slot(int)));
        second_page->setPageIndex(1);
        page_num=2;
        pages.append(second_page);
    }
    int secondPageAppNum;
    appnum>(sysAppCount+applimit)?secondPageAppNum=applimit:secondPageAppNum=appnum-sysAppCount;
    pages[1]->clear();//for new install app
    for(int j = sysAppCount; j < (sysAppCount+secondPageAppNum); j++)
    {
        lcd_h==450?items[j]->setSizeHint(QSize(86,100)):items[j]->setSizeHint(QSize(67,80));
        pages[1]->addItem(items[j]);
    }
    qDebug()<<"======================second page app num"<<secondPageAppNum;
    // current_page_idx=1;
    pages[0]->hideListWidget();
    page_lab->raise();
    pages[1]->setItemCount(secondPageAppNum);

    //third page

    if(appnum >sysAppCount+applimit)//for new install app, no need create page again
    {
        if(page_num<3)
        {
            DeskListWidget *third_page=new DeskListWidget(this,lcd_w,lcd_h,stausbar_pos_top);
            //third_page->setItemCount(appnum - sysAppCount - 8);
            connect(third_page,SIGNAL(pageNeedChange(int)),this,SLOT(page_change_slot(int)));
            connect(third_page,SIGNAL(deskItemClick(int)),this,SLOT(send_itemClickedSignal_slot(int)));
            connect(third_page,SIGNAL(goNextItem(int)),this,SLOT(go_nextItem_slot(int)));
            connect(third_page,SIGNAL(enterCurrentItem(int)),this,SLOT(enter_currentItem_slot(int)));
            page_num=3;
            third_page->setPageIndex(2);
            repaint();
            pages.append(third_page);
        }
        int thirdPageAppNum;
        appnum>(sysAppCount+2*applimit)?thirdPageAppNum=applimit:thirdPageAppNum=appnum-sysAppCount-applimit;
        pages[2]->clear();//for new install app
        for(int j = sysAppCount + applimit; j < (sysAppCount+applimit+thirdPageAppNum); j++)
        {
            lcd_h==450?items[j]->setSizeHint(QSize(86,100)):items[j]->setSizeHint(QSize(67,80));
            pages[2]->addItem(items[j]);
        }
        pages[2]->setItemCount(thirdPageAppNum);
        pages[2]->hideListWidget();
        pages[1]->hideListWidget();
        page_lab->raise();
    }
    else
    {
        if(page_num==3)
        {
            page_num=2;
            pages.removeAt(2);
        }

    }

    if(watermark_lab&&current_page_idx!=0)
        watermark_lab->show();
     pages[current_page_idx]->showListWidget();
}


void QNDesktop::clearItems(void)
{
	QListWidgetItem *item;


#if 1
    for (int i = 0; i < pages.count(); i++)
	{
		if (pages[i]->count() > 0)
		{
			for (int j = 0; j < pages[i]->count(); j++)
			{
				item = pages[i]->item(j);	
				delete item;
			}
			pages[i]->clear();
		}
	}
#endif
}


void QNDesktop::paint_page_mark(void)
{
    page_lab->raise();
    QPainter paint(page_lab);
    paint.setRenderHint(QPainter::Antialiasing);
    for(int i=0;i<page_num;i++)
    {
        if(current_page_idx==i)
        {
            paint.setPen(Qt::green);
            paint.setBrush(Qt::green);
            paint.drawEllipse(5*(i+1)+i*10,0,10,10);

        }
        else
        {
            paint.setPen(Qt::gray);
            paint.setBrush(Qt::gray);
            paint.drawEllipse(5*(i+1)+i*10,0,10,10);
        }
    }

}

void QNDesktop::enter_currentItem_slot(int idx)
{
    if(ignoreSignalFlag)
        return;
	int list_idx=0;//get list item index in the page items
	for(int i=0;i<current_page_idx;i++)
		list_idx+=pages[i]->itemCount();
	list_idx+=idx;
	emit needExecute(list_idx);
}

void QNDesktop::go_nextItem_slot(int idx)
{

    int list_idx=0;//get list item index in the page items
    for(int i=0;i<current_page_idx;i++)
        list_idx+=pages[i]->itemCount();
    list_idx+=idx;
    if(current_page_idx==1&&pageitems.count()==sysAppNum)
         return;
    else
        pages[current_page_idx]->setCurrentItem(pageitems[list_idx]);
}

void QNDesktop::send_itemClickedSignal_slot(int idx)
{
    int list_idx=0;//get list item index in the page items
    if(idx<pages[current_page_idx]->itemCount())
    {
        for(int i=0;i<current_page_idx;i++)
            list_idx+=pages[i]->itemCount();
        list_idx+=idx;
        pages[current_page_idx]->setCurrentItem(pageitems[list_idx]);
        emit needExecute(list_idx);
    }
}

bool QNDesktop::eventFilter(QObject *watched, QEvent *event)
{
    if((watched ==page_lab)&& event->type() == QEvent::Paint)
          paint_page_mark(); 
    return QWidget::eventFilter(watched,event);
}
