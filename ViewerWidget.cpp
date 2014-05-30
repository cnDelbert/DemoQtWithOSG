/**
 * @file ViewerWidget.cpp
 * @brief Generate an OSGViewer window within Qt frame.
 *
 * @author Delbert
 * @date 2014/05/30
 * 
 * 
 */
#include "ViewerWidget.h"


ViewerWidget::ViewerWidget( osgViewer::ViewerBase::ThreadingModel 
	threadingModel = osgViewer::CompositeViewer::SingleThreaded )
	: QWidget()
{
	setThreadingModel( threadingModel );

	setKeyEventSetsDone( 0 );    ///< Disable viewer.done() by ESC

	//m_mainWidget = addViewWidget( createGraphicsWindow)
}


ViewerWidget::~ViewerWidget(void)
{
}

/**
 * @brief 添加显示组件
 * @return QWidget* 的指针。
 */
QWidget* addViewWidget( osgQt::GraphicsWindowQt* gw, 
	osg::Node* scene )
{
	osg::ref_ptr< osgViewer::View > view = new osgViewer::View;
	addView( view );

	osg::ref_ptr< osg::Camera > camera = view->getCamera();
}