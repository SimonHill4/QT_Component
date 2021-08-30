#ifndef QNRangeSelector_H
#define QNRangeSelector_H
#include <QDebug>
#include <QWidget>
#include <QMouseEvent>
#include <QPainter>
#include <QPropertyAnimation>
#include <QLabel>
class QNRangeSelector : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(int deviation READ readDeviation WRITE setDeviation)
public:

    explicit QNRangeSelector(QWidget *parent,const int &x,const int &y,const int &default_idx,QList<QString> &value);
    ~QNRangeSelector();
    void setRange(int min,int max,int current);
    void upDateRangeList(QList<QString> &value,const int &default_idx);
    int currentValue();
    int m_minRange;
    int m_maxRange;
    int m_currentValue;
    bool isDragging;
    int m_deviation;
    int m_mouseSrcPos;
    int m_numSize;//计算所得的数字字符尺寸，以最长的情况为准
    QPropertyAnimation *homingAni;

    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void paintEvent(QPaintEvent *);

    void paintString(QPainter &painter,QString str,int deviation,bool center);
    void homing();
    int readDeviation();
    void setDeviation(int n);
    void setBackgroundColor(QColor c);
    void resetGeometry(const QRect &r);
signals:
    void currentValueChanged(int value);
    void deviationChange(float deviation);
    void enterPressed(int index);
    void tabPressed(int index);
    void cancelPressed(void);

public slots:
protected:
    void keyPressEvent(QKeyEvent *ev);
private:
    QList<QString> range_value;
    int pos_x,pos_y;

};

#endif // QNRangeSelector_H
