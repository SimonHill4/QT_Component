#ifndef QNPOPWINDOW_H
#define QNPOPWINDOW_H

#include <QWidget>
#include <QGraphicsDropShadowEffect>
#include <QLabel>
#include <QPushButton>
#include <QKeyEvent>
#include <QPropertyAnimation>
#include <qnlistinfo.h>
#include <QCoreApplication>
#include <unistd.h>
#include <QEventLoop>
#include <QPlainTextEdit>
#include <QScrollBar>
#include <QMouseEvent>
#include <QPainter>

#define BLURRY_VALUE    10




class QNPopWindow : public QWidget
{
    Q_OBJECT

public:
    typedef enum{
        NOTIFY_WIN=0X01,
        WARNING_WIN=0X02,
        CONFIRM_WIN=0X03,
        CLOSE_WIN=0x04,
        REMIND_WIN=0x05,
    }POPWINTYPE;
    explicit QNPopWindow(QWidget *parent = 0,POPWINTYPE type=NOTIFY_WIN,int lcd_w=320,int lcd_h=240);
    explicit QNPopWindow(QWidget *parent,QRect rec,QNListInfo *list_widget);//full win info with burry background
    ~QNPopWindow(void);
    void popWindow(void);
    void hideWindow(void);
    void clearMessage(void);
    void setMessage(QString str="mess",int type=1);//1proceing mes 0 succeed mes -1error mes
    void appendMessage(QString str="mess",int type=1);//1proceing mes 0 succeed mes -1error mes
    void setFont(const QFont &);
    void setBackGround(QColor c);
    void keyPressEvent(QKeyEvent *ev);
    void mousePressEvent(QMouseEvent * ev);
    void setWaitFlag(void);
    void clearWaitFlag(void);
    void clear_keybuf(void);
    int get_key(void);
    void movePlainTextSliderPosition(void);
    void set_undeal_message_num(int num);
    void paintEvent(QPaintEvent *e);

    void setConfirmWin_button_txt(QString oktxt="OK",QString canceltxt="Cancel");
    void setColseWin_button_txt(QString txt="Close");
    void setCloseWin_icon(QPixmap &icon);
     void setRemindWin_icon(QPixmap &icon);
signals:
    void buttonPressed(bool btn);//true=ok button. false=cancel button
    void anyKeyPressed(bool bt);
    void cancelPressed(void);
public slots:
    void send_buttonPress_signal_slot(void);
    void button_release_slot(void);
private:
    QLabel *lab,*icon_lab;
    QPlainTextEdit *plaintext;
    QPushButton *ok_btn,*cancel_btn,*close_btn;
    QPropertyAnimation *ani_slide;
    int lcd_width,lcd_height;
    bool FullScreenFlag,notifyFlag,waitFlag,warningFlag,confirmFlag,closeFlag,remindFlag;
    QGraphicsBlurEffect *blurEffec;
    QGraphicsDropShadowEffect *shadow;
    QNListInfo *burry_bg;
    QEventLoop loop;
    int keyrecorder,undeal_mesNum;
    QString oktext,canceltext,closetext;
};

#endif // QNPOPWINDOW_H
