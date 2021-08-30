/*
 * this class just for QNListinfo class
 */
#ifndef QNButton_H
#define QNButton_H

#include <QWidget>
#include <QMouseEvent>
#include <QRect>
#include <QPainter>
#include <QLabel>
class QNButton : public QWidget
{
    Q_OBJECT
public:
    explicit QNButton(QWidget *parent,bool turnon,int row,int row_height=34);    //switch QNButton
    explicit QNButton(QWidget *parent,int row,int row_height=34);    //number icon QNButton
    explicit QNButton(QWidget *parent,QColor color,int row,int row_height=34,bool direction=false);    //list have more QNButton
    explicit QNButton(QWidget *parent,bool select,QColor color,int row,int row_height);//list have select QNButton
    void mousePressEvent(QMouseEvent *);
    void paintEvent(QPaintEvent *);

signals:
    void QNButtonPressed(void);
    void IconClicked(int i);
public slots:
private:
    QString text;
    QColor bt_color;
public:
    /**********************************
     * 0---->switch QNButton off
     * 1--->swich QNButton on
     * 3------>number icon QNButton
     * 4------>list have more QNButton
     *5------>list have selected,QNButton was selected
     *6------>list have selected,QNButton non selected
     * *********************************/
    int QNButton_type,row_h;
    bool left_direction;
};

#endif // QNButton_H
