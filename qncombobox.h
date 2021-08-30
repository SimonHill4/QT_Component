#ifndef QNCOMBOBOX_H
#define QNCOMBOBOX_H

#include <QWidget>
#include <QComboBox>
#include <QLabel>
#include "qcomboboxreload.h"


class QNComBobox : public QWidget
{
    Q_OBJECT
public:
    explicit QNComBobox(QWidget *parent ,QRect rec, int lcd_h);
    ~QNComBobox();
    void setLeftText(QString txt);
    void addItems(QStringList txtlist);
    void clearItem(void);
    void setEditable(bool flag);
    void setcurrentIndex(int idx);
    void setAcctive(bool flag);
    int getCurrentIndex(void);
signals:
    void current_Index_Change(int idx);
public slots:
    void send_current_index_change_slots(int id);
private:
    //QComboBox *box;
	QComboBoxReload *box;
    QLabel *lab;
};

#endif // QNCOMBOBOX_H
