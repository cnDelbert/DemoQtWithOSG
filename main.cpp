#include "demoqtwithosg.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	DemoQtWithOSG w;
	w.show();
	return a.exec();
}
