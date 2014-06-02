
#include "demoqtwithosg.h"


DemoQtWithOSG::DemoQtWithOSG(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	viewWidget = new ViewerWidget;
	setCentralWidget(ViewerWidget);
}

DemoQtWithOSG::~DemoQtWithOSG()
{

}
