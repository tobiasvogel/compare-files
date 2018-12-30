#ifndef COMPARELINEEDIT_H
#define COMPARELINEEDIT_H

#include <QtGui>


class compareLineEdit : public QLineEdit
{
	Q_OBJECT
public:
	compareLineEdit(QWidget *parent = 0);

	void dragEnterEvent(QDragEnterEvent *event);
	void dropEvent(QDropEvent *event);
	void mouseDoubleClickEvent(QMouseEvent *event);
};

#endif
