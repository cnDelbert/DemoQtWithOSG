/**
 * @file 
 * @brief   An entrance for the application.
 * @author  Delbert
 * @date    2014/06/03
 * @version 0.1.1
 */

#include "demoqtwithosg.h"
#include <QtWidgets/QApplication>

/**
 * @brief  Main entrance for the application.
 *
 */
 int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	DemoQtWithOSG w;
	w.show();
	return a.exec();
}