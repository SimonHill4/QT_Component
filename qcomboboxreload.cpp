#include "qcomboboxreload.h"
#include <QDebug>

#define VISIBLE_ITEMS 3
#define ITEM_HEIGHT 20


QComboBoxReload::QComboBoxReload(QWidget *parent, int lcd_h) :
    QComboBox(parent)
{
	lcd_height = lcd_h;
}


QComboBoxReload::~QComboBoxReload()
{
}


void QComboBoxReload::showPopup()
{
    QWidget *popup;
	int real_count = 0;


	QComboBox::showPopup();
	real_count = count() > VISIBLE_ITEMS ? VISIBLE_ITEMS : count();
	popup = this->findChild<QFrame*>();
	qDebug() << "popy: " << popup->y() << "poph: " << popup->height() << "thisy: " << this->y();
	if (popup->y() + real_count * ITEM_HEIGHT > lcd_height)
	{
		popup->move(popup->x(), popup->y() - this->height() - popup->height()); //x轴不变，y轴向上移动 list的高+combox的高
		return;
	}
	//QComboBox::showPopup();
}
