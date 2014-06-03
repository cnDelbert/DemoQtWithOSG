/**
 * @file
 * @author  Delbert
 * @date    2014/06/03
 * @brief   Main window of the application.
 * @version 0.1.1
 *
 */

#include "demoqtwithosg.h"


DemoQtWithOSG::DemoQtWithOSG(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	
	/*ViewerWidget**/ 
	osg::ref_ptr< osg::Node > cow = osgDB::readNodeFile("cow.osgt");
	osg::ref_ptr< osg::Group > root = new osg::Group;
	root->addChild( cow );
	
	osgViewer::ViewerBase::ThreadingModel threadingModel = 
		osgViewer::ViewerBase::SingleThreaded; /// Explict declaration for Qt 5
	viewerWidget = new ViewerWidget(/*threadingModel,*/ root );
	setCentralWidget( viewerWidget );
	// 	viewerWidget->setGeometry(100, 100, 800, 600 );
 	viewerWidget->show();
	
}

DemoQtWithOSG::~DemoQtWithOSG()
{
	//delete ui;
}
