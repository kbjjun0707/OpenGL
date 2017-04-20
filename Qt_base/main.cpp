#include "qt_base.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Qt_base w;
	w.show();
	return a.exec();
}
