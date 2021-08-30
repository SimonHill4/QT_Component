/********************************
 * this class just for QNDesktop
 *******************************/
#ifndef DESKLISTWIDGET_H
#define DESKLISTWIDGET_H

#include <QListWidget>
#include <QMouseEvent>
class DeskListWidget : public QListWidget
{
    Q_OBJECT
public:
    explicit DeskListWidget(QWidget *parent = 0,int w=320,int h=240,bool statusBarTop=true);
    void mousePressEvent(QMouseEvent * ev);
    void mouseReleaseEvent(QMouseEvent * ev);
    void mouseMoveEvent(QMouseEvent * ev);
    void keyPressEvent(QKeyEvent *ev);
    void setMouseAvaliable(bool enable);
    void setItemCount(int num);
    void showListWidget();
     void hideListWidget();
     void setPageIndex(int num);
    int itemCount();
    void ignoreKeyPress(bool flag);
signals:
    void pageNeedChange(int devition);
    void deskItemClick(int index);
    void goNextItem(int idx);
    void enterCurrentItem(int idx);
    void numberPressed(int num);
private:
    int mouse_press_x,devition,lcd_w;
    bool mouseTrackFlag;
    int item_count,current_item;
    int last_key; //record last key pressed
    int icon_w,pageIndex;
    bool ignoreKeyFlag;

};

#endif // DESKLISTWIDGET_H
