#include "qnlistinfo.h"
#include <QDebug>
#include <QPicture>
QNListInfo::QNListInfo(QWidget *parent,QList<QNListInfo_T> &list_mes,QRect &rect,int row) :
    QWidget(parent)
{    
        row_num=list_mes.count();
        table_widget=new QTableWidget(row_num,3,this);
        table_widget->verticalHeader()->setVisible(false);
        table_widget->horizontalHeader()->setVisible(false); //隐藏行表头
        table_widget->setColumnWidth(0,30); //number icon width
        table_widget->setColumnWidth(1,240);    //string message width
        table_widget->setColumnWidth(2,50);     //status icon width
        table_widget->setFrameShape(QFrame::NoFrame);
        //seting bottom line
        table_widget->setShowGrid(false);
        table_widget->setEditTriggers(QAbstractItemView::NoEditTriggers); //设置不可编辑

        table_widget->setStyleSheet(
        "QTableView::item:selected { background-color: rgb(80,80,80);color:rgb(255,255,255);}"
        "QTableView::Item{border:none;border-bottom:1px solid rgb(0,0,0);}"
        "QTableView{background-color:rgba(237,237,237,180);color:rgb(0,0,0)}"
         );
        table_widget->setSelectionBehavior(QAbstractItemView::SelectRows);
        table_widget->setSelectionMode(QAbstractItemView::SingleSelection);

        this->setGeometry(rect);
        table_widget->setGeometry(0,0,rect.width(),rect.height());
        table_widget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        table_widget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        QFont font;
        font.setPixelSize(18);
        table_widget->setFont(font);
		current_row=row;
        row_height=34;//default row height
        rightAlign=false;//defaut is left to right
        mask=new QLabel(this);
        mask->setGeometry(table_widget->geometry());
        mask->setStyleSheet("QLabel{background-color:transparent;}");

        mask->hide();
        //upDateQNListInfo(list_mes,current_row);
}
QNListInfo::~QNListInfo()
{
        delete table_widget;
}
void QNListInfo::upDateQNListInfo(QList<QNListInfo_T> &list_mes,int row)
{

            row_num=list_mes.count();
            table_widget->clearContents();
            table_widget->setRowCount(row_num);
            pre_row=current_row;
            current_row=row;
            table_widget->setFocusPolicy(Qt::NoFocus);
            list_infos=&list_mes;
            disconnect(table_widget,0,0,0);
            for(int i=0;i<row_num;i++)
            {
                    table_widget->setRowHeight(i,row_height);
                    //set number icon
                    table_widget->setCellWidget(i,rightAlign?2:0,new QNButton(this,i,row_height));
                    //set center message
                    table_widget->setItem(i,1,new QTableWidgetItem(list_mes[i].messge));
                    rightAlign?table_widget->item(i,1)->setTextAlignment(Qt::AlignRight):table_widget->item(i,1)->setTextAlignment(Qt::AlignLeft|Qt::AlignVCenter);
                  //set last status icon in the end of list item
                    if(list_mes[i].type==LIST_INFO_HAVE_SWITCH)
                    {
                            if(list_mes[i].status==0)   //switch QNButton off
                                table_widget->setCellWidget(i,rightAlign?0:2,new QNButton(this,false,i,row_height));
                            else    //switch QNButton on
                                table_widget->setCellWidget(i,rightAlign?0:2,new QNButton(this,true,i,row_height));
                    }
                    else if(list_mes[i].type==LIST_INFO_HAVE_MORE)
                        table_widget->setCellWidget(i,rightAlign?0:2,new QNButton(this,QColor(0,0,0),i,row_height,rightAlign));
                    else if(list_mes[i].type==LIST_INFO_HAVE_SELECT)
                    {
                        if(list_mes[i].status==0)
                            table_widget->setCellWidget(i,rightAlign?0:2,new QNButton(this,false,QColor(0,0,0),i,row_height));  //non selected
                        else
                            table_widget->setCellWidget(i,rightAlign?0:2,new QNButton(this,true,QColor(0,0,0),i,row_height)); //selected
                    } 
                    connect(table_widget->cellWidget(i,rightAlign?2:0),SIGNAL(IconClicked(int)),this,SLOT(changeSelectedRow(int)));
                    connect(table_widget->cellWidget(i,rightAlign?0:2),SIGNAL(IconClicked(int)),this,SLOT(changeSelectedRow(int)));
            }
            connect(table_widget,SIGNAL(currentCellChanged(int,int,int,int)),this,SLOT(current_cell_change_slot(int,int,int,int)));
            table_widget->selectRow(current_row); //defalut select first row
            this->show();


}
 void QNListInfo::setRowHeight(int value)
 {
     row_height=value;
 }
void QNListInfo::setRight2Left(bool flag)
{
    rightAlign=flag;
    if(flag)
    {
        table_widget->setColumnWidth(0,50); //status icon width
        table_widget->setColumnWidth(1,240);    //string message width
        table_widget->setColumnWidth(2,30);     //number icon
    }
    else
    {
        table_widget->setColumnWidth(0,30); //number icon width
        table_widget->setColumnWidth(1,240);    //string message width
        table_widget->setColumnWidth(2,50);     //status icon width
    }
}
void QNListInfo::current_cell_change_slot(int currentRow, int currentColumn, int previousRow, int previousColumn)
{
     current_row=currentRow;
     pre_row=previousRow;

}



 void QNListInfo::changeSelectedRow(int row)
 {
        pre_row=current_row;
        current_row=row-1;
        table_widget->selectRow(current_row);
       if((*list_infos)[current_row].type==LIST_INFO_HAVE_SELECT)
       {
               for(int i=0;i<row_num;i++)
               {
                    QNButton *tmp = (QNButton *)table_widget->cellWidget(i,2);
                    if(i==current_row)
                    {
                         tmp->QNButton_type=5;//list select QNButton was selected
                         (*list_infos)[current_row].status=1;
                          emit listItemStatusChanged(current_row, 1);
                    }
                    else if((*list_infos)[i].type==LIST_INFO_HAVE_SELECT)
                    {
                        tmp->QNButton_type=6;//set the other to non selected
                         (*list_infos)[i].status=0;
                    }
                    tmp->repaint();
               }
       }
       else if((*list_infos)[current_row].type==LIST_INFO_HAVE_SWITCH)
       {
           (*list_infos)[current_row].status=!((*list_infos)[current_row].status);
           emit listItemStatusChanged(current_row, (*list_infos)[current_row].status);
       }
       else
           emit gonext(current_row);
 }
 void QNListInfo::changeSelectedRow(int row,int column)
 {
        pre_row=current_row;
        current_row=row;
        table_widget->selectRow(current_row);
        if((*list_infos)[current_row].type==LIST_INFO_HAVE_SELECT)
        {
                for(int i=0;i<row_num;i++)
                {
                     QNButton *tmp = (QNButton *)table_widget->cellWidget(i,2);
                     if(i==current_row)
                     {
                          tmp->QNButton_type=5;//list select QNButton was selected
                          (*list_infos)[current_row].status=1;
                          if(pre_row!=current_row)
                             emit listItemStatusChanged(current_row, 1);
                     }
                     else if((*list_infos)[i].type==LIST_INFO_HAVE_SELECT)
                     {
                        tmp->QNButton_type=6;//set the other to non selected
                         (*list_infos)[i].status=0;
                     }

                     tmp->repaint();
                }
        }
 }


void QNListInfo::keyPressEvent(QKeyEvent *ev)
{
	qtcode = ev->key();
	isKeyPressed = true;
    pre_row=current_row;
    switch(ev->key())
    {
        case Qt::Key_F1:
		case Qt::Key_Asterisk:
			current_row > 0 ? current_row -= 1 : current_row = row_num - 1;
			break;
        case Qt::Key_F2:
		case Qt::Key_Percent:
			current_row < row_num - 1 ? current_row += 1 : current_row = 0;
			break;
        case Qt::Key_0:emit configure(current_row);break;
        case Qt::Key_1: if(row_num>=1)
                        {
                            current_row=0;
                            enter_operation();
                        }
                        break;
        case Qt::Key_2:if(row_num>=2)
                        {
                            current_row=1;
                            enter_operation();
                        }
                        break;
        case Qt::Key_3:if(row_num>=3)
                        {
                            current_row=2;
                            enter_operation();
                        }
                        break;
        case Qt::Key_4:if(row_num>=4)
                        {
                            current_row=3;
                            enter_operation();
                        }
                        break;
        case Qt::Key_5:if(row_num>=5)
                        {
                            current_row=4;
                            enter_operation();
                        }
                        break;
        case Qt::Key_6:if(row_num>=6)
                        {
                            current_row=5;
                            enter_operation();
                        }
                        break;
        case Qt::Key_7:if(row_num>=7)
                        {
                            current_row=6;
                            enter_operation();
                        }
                        break;
        case Qt::Key_8:if(row_num>=8)
                        {
                            current_row=7;
                            enter_operation();
                        }
                        break;
        case Qt::Key_9:if(row_num>=9)
                        {
                            current_row=8;
                            enter_operation();
                        }
                        break;
        case Qt::Key_Escape:emit goback();break;
        case Qt::Key_Enter:enter_operation(); break;
    }

    table_widget->selectRow(current_row);
}

 void QNListInfo::enter_operation(void)
 {
     QNButton *btn = (QNButton *)table_widget->cellWidget(current_row,2);
    if((*list_infos)[current_row].type==LIST_INFO_HAVE_SWITCH)
    {
            btn->QNButton_type=!btn->QNButton_type;
            btn->repaint();
            (*list_infos)[current_row].status=!((*list_infos)[current_row].status);
            emit listItemStatusChanged(current_row, (*list_infos)[current_row].status);
    }
    else if((*list_infos)[current_row].type==LIST_INFO_HAVE_SELECT)
    {
            btn->QNButton_type=5;//list select QNButton was selected
            (*list_infos)[current_row].status=1;
             emit listItemStatusChanged(current_row, 1);
            for(int i=0;i<row_num;i++)
            {
                 QNButton *tmp = (QNButton *)table_widget->cellWidget(i,2);
                 if(i==current_row)
                     continue;
                 else if((*list_infos)[i].type==LIST_INFO_HAVE_SELECT)
                 {
                     tmp->QNButton_type=6;//set the other to non selected
                      (*list_infos)[i].status=0;
                  }
                 tmp->repaint();
            }
            btn->repaint();
    }
    else if((*list_infos)[current_row].type==LIST_INFO_HAVE_MORE)
        emit gonext(current_row);
 }

void QNListInfo::getCurrentItemName(QList<QNListInfo_T> &list_mes, char *itemname)
{
    QString name = list_mes[current_row].messge;
	std::string name2 = name.toStdString();


	strcpy(itemname, name2.c_str());
}
void QNListInfo::setBurryEffect(bool flag)
{
    if(flag)
    {
        blurEffec=new QGraphicsBlurEffect(this);
        blurEffec->setBlurHints(QGraphicsBlurEffect::PerformanceHint);
        blurEffec->setBlurRadius(10);
        table_widget->setGraphicsEffect(blurEffec);
        mask->show();
    }
    else
    {
        mask->hide();
        table_widget->setGraphicsEffect(NULL);
    }
}
