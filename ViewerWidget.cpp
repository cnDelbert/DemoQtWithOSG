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
	camera->setGraphicsContext( gw );

	const osg::GraphicsContext::Traits* traits = gw->getTraits(); ///< Set Grapics Window size

	camera->setClearColor( osg::Vec4(0., 0.2, 0.6, 1.0) ); ///< Clear Color
	camera->setViewport( new osg::Viewport(0, 0, traits->width, traits->height) );
	camera->setProjectionMatrixAsPerspective( 30.f, 
		static_cast<double>(traits->width)/static_cast<double>(traits->height), 
		1.0f, 10000.f );

	view->setSceneData( scene );
	view->addEventHandler( new osgViewer::StatsHandler );
	view->setCameraManipulator( new osgGA::TrackballManipulator );

	return gw->getGLWidget();
}