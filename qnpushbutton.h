#ifndef QNPUSHBUTTON_H
#define QNPUSHBUTTON_H

#include <QWidget>
#include <QPushButton>
class QNPushButton : public QWidget
{
    Q_OBJECT
public:
    explicit QNPushButton(QWidget *parent = 0,QRect bt=QRect(0,0,20,30),QString txt=QString("QNButton"),QColor color=QColor(Qt::green));
    ~QNPushButton();
    void hideButton(void);
    void showButton(void);
signals:
    void ButtonPressed(void);
    void ButtonRelease(void);
public slots:
    void send_button_pressed_slot(void);
    void send_button_release_slot(void);
private:
    QPushButton *push_bt;
    QColor col;
    QRect rec;
};

#endif // QNPUSHBUTTON_H
