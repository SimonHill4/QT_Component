#ifndef QNTitle_H
#define QNTitle_H

#include <QWidget>
#include <QLabel>
#include <QPixmap>
#include <QPainter>
#include <QMouseEvent>
#include <QCoreApplication>
#define TITLE_ICON_PATH "/system/Qt/icons/small/"
class QNTitle : public QWidget
{
    Q_OBJECT
public:
    explicit QNTitle(QWidget *parent ,const QPixmap *icon,const QString &QNTitle_str);
    ~QNTitle();
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);
    void upDateQNTitleIcon(const QPixmap *icon);
    void upDateQNTitleMes(const QString &QNTitle_str);
    int get_title_height(void);
    void setRight2Left(bool flag);
signals:
    void goback(void);
public slots:
private:
    QLabel *mes_lab;
    QLabel *icon_lab;
    int title_height;
    bool rightAlign;
};

#endif // QNTitle_H
