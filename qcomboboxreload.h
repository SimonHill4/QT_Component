#ifndef __QCOMBOBOXRELOAD_H__
#define __QCOMBOBOXRELOAD_H__


#include <QComboBox>


class QComboBoxReload : public QComboBox
{
    Q_OBJECT
public:
    explicit QComboBoxReload(QWidget *parent, int lcd_h);
    ~QComboBoxReload();
protected:
	void showPopup();
private:
	int lcd_height;
};



#endif  // __QCOMBOBOXRELOAD_H__
