#ifndef QNDESKTOP_H
#define QNDESKTOP_H

#include <QWidget>
#include <desklistwidget.h>
#include <QAbstractItemView>
#include <QPainter>
#include <QLabel>
#include <QEvent>
#include <QMouseEvent>
#include <QThread>
#include <math.h>

#define PAGE_LAB_W  50  //page lab hight is 10
#define WATERMARK_PATH "/system/Qt/png/watermark.png"

class QNDesktop : public QWidget
{
    Q_OBJECT
public:
    explicit QNDesktop(int sysAppCount=6, QWidget *parent = 0, QRect rec=QRect(0,30,320,210),bool statusbarOnTop = true);
    ~QNDesktop();
    void loadItems(QList<QListWidgetItem *> &items, int sysAppCount);
	void clearItems(void);
    void setBackGround(QColor c);
    bool eventFilter(QObject *watched, QEvent *event);
    void setFocus(bool focus);
    void ignoreSignal(bool flag);
    void setFwType(bool pro);
    void setNoAppMes(QString txt);
signals:
    void needExecute(int index);
    void clearPasswdVerify(void);
public slots:
    void page_change_slot(int devition);
    void send_itemClickedSignal_slot(int idx);
    void go_nextItem_slot(int idx);
    void enter_currentItem_slot(int idx);
private:
    void paint_page_mark(void);


    QList<DeskListWidget *> pages;
    QList<QListWidgetItem *> pageitems;
    QLabel *page_lab,*watermark_lab,*noapp_lab;
    int page_num,current_page_idx,lcd_w,lcd_h,applimit;//one page maximum Apps
    bool stausbar_pos_top,fw_type;
    int mos_pressed_x,sysAppNum;
    QRect rect;
    QString noapp_mes;
    bool ignoreSignalFlag;

};

#endif // QNDESKTOP_H
