#ifndef QNINPUTBAR_H
#define QNINPUTBAR_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QEvent>
#include <QKeyEvent>
#include <string.h>
#include <QLabel>
#include <QCoreApplication>
#include <QGraphicsDropShadowEffect>
class QNInputBar : public QWidget
{
    Q_OBJECT
public:
    explicit QNInputBar(QWidget *parent,QRect rec,int fontsize);
    ~QNInputBar();

    void setMaxLength(int len);
    void setEchoMode(QLineEdit::EchoMode mode);
    void setRemindText(QString txt);
    void setDefaultText(QString txt);
    void setButtonText(QString tx);
    void setActive(bool flag);
    void setAlignment(Qt::AlignmentFlag flag);
    void hide();
    void show();
    void clear();
    void setText(QString tx);
    QString getText(void);

signals:
    void enterPressed(void);
    void cancelPressed(void);
    void gonext(void);
    void golast(void);
    void gotfocus(void);
    void txtchange(QString txt);
public slots:
    void send_complete_signal_slot(void);
    void text_edited_slot(QString newtext);
protected:
      bool eventFilter(QObject *watched, QEvent *event);
      void keyPressEvent(QKeyEvent *ev);
private:
    QLabel *alpha_lab;
    QPushButton *bt;
    QString edit_instyle,edit_outstyle,bt_instyle,bt_outstyle;
    QVector <QString> keymap;
    bool alphaFlag,focusFlag;
    QRect rec_size;
    int font_size,map_index1,map_index2;
    QString text,remindtxt;

    QLineEdit *qnlineedit;
    int maxlen;
    bool echomode;//true show number,false show *

};

#endif // QNINPUTBAR_H
