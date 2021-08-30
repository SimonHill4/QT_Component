#ifndef QNPROGRESSBAR_H
#define QNPROGRESSBAR_H

#include <QWidget>
#include <QPainter>
#include <QLabel>
class QNProgressBar : public QWidget
{
    Q_OBJECT
public:
    explicit QNProgressBar(QWidget *parent,QRect rec);
    ~QNProgressBar();
    void updatePercent(int value);
    void runCircle(int value);
    void paintEvent(QPaintEvent *);
signals:

public slots:

private:
    int percent;
    QLabel *txt_lab;
    bool circleFlag;//转圈等待动画,没有中间百分比
};

#endif // QNPROGRESSBAR_H
