#ifndef QNListInfo_H
#define QNListInfo_H

#include <QWidget>
#include <QCoreApplication>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QPainter>
#include <QHeaderView>
#include <QTime>
#include <QGraphicsDropShadowEffect>
#include "qnbutton.h"

typedef enum{
    LIST_INFO_HAVE_MORE,
    LIST_INFO_HAVE_SWITCH,
    LIST_INFO_HAVE_SELECT,
}QNListInfoType_T;

typedef struct{
    QNListInfoType_T type;
    QString messge;
    int status; //0-->close 1---->on 2----->wait.
}QNListInfo_T;

class QNListInfo : public QWidget
{
    Q_OBJECT
public:
    explicit QNListInfo(QWidget *parent,QList<QNListInfo_T > &list_mes,QRect &rect, int row = 0);
    ~QNListInfo();
    void keyPressEvent(QKeyEvent *ev);

    void upDateQNListInfo(QList<QNListInfo_T> &list_mes,int row);
    void setBurryEffect(bool flag);
	void getCurrentItemName(QList<QNListInfo_T> &list_mes, char *itemname);
    void setRowHeight(int value);
    void setRight2Left(bool flag);
signals:
        void listItemStatusChanged(int row,int status);
        void gonext(int row);
        void goback(void);
        void configure(int row);
public slots:
     void changeSelectedRow(int row);
     void changeSelectedRow(int row,int column);
     void current_cell_change_slot(int currentRow, int currentColumn, int previousRow, int previousColumn);
private:
     void enter_operation(void);
    QTableWidget *table_widget;
    int row_num,current_row,pre_row;
    QList<QNListInfo_T> *list_infos;
	unsigned int qtcode;
	bool isKeyPressed;
    int row_height;
    QLabel *mask;
    bool rightAlign;
    QGraphicsBlurEffect *blurEffec;
};

#endif // QNListInfo_H
