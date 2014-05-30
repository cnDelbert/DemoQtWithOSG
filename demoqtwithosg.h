/**
 * @file demoqtwithosg.h
 * @author Delbert
 * @date 2014/05/30
 * 
 * 
 */

#ifndef DEMOQTWITHOSG_H
#define DEMOQTWITHOSG_H

#include <QtWidgets/QMainWindow>
#include "ui_demoqtwithosg.h"

class DemoQtWithOSG : public QMainWindow
{
	Q_OBJECT

public:
	DemoQtWithOSG(QWidget *parent = 0);
	~DemoQtWithOSG();

private:
	Ui::DemoQtWithOSGClass ui;
};

#endif // DEMOQTWITHOSG_H
