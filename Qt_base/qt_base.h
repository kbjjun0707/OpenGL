#ifndef QT_BASE_H
#define QT_BASE_H

#include <QtWidgets/QMainWindow>
#include "ui_qt_base.h"

class Qt_base : public QMainWindow
{
	Q_OBJECT

public:
	Qt_base(QWidget *parent = 0);
	~Qt_base();

private:
	Ui::Qt_baseClass ui;
};

#endif // QT_BASE_H
