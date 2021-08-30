#ifndef QNLABINFO_H
#define QNLABINFO_H

#include <QWidget>
#include <QLabel>
#include <QMouseEvent>
class QNLabInfo : public QWidget
{
    Q_OBJECT
public:
    explicit QNLabInfo(QWidget *parent,QRect rect);
    explicit QNLabInfo(QWidget *parent,QRect rect,bool reponseTouch);
    ~QNLabInfo();
    void setLeftInfo(QString str);
    void setRightInfo(QString str);
    void setTitleInfo(QString str);
    void setMsgInfo(QString str);
signals:
    void labPressed(void);
protected:
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *ev);
public slots:

private:
    QLabel *title_lab,*mes_lab;

};

#endif // QNLABINFO_H
