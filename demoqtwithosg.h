/**
 * @file  
 * @class    DemoQtWithOSG
 * @author   Delbert
 * @date     2014/05/30
 * @version  0.1.1
 * @brief    The MainWindow class
 */

#ifndef DEMOQTWITHOSG_H
#define DEMOQTWITHOSG_H

#include <QtWidgets/QMainWindow>
#include "ui_demoqtwithosg.h"
#include "ViewerWidget.h"

class DemoQtWithOSG : public QMainWindow
{
	Q_OBJECT

public:
	DemoQtWithOSG(QWidget *parent = 0);
	~DemoQtWithOSG();
	/** Widget to show the scene. */
	ViewerWidget* viewerWidget;

private:
	Ui::DemoQtWithOSGClass ui;

};

#endif // DEMOQTWITHOSG_H
