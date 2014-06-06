/**
 * @file     
 * @brief    Generate an OSGViewer window within Qt frame.
 *
 * @author   Delbert
 * @date     2014/06/6
 * @version  0.1.3
 * @param    threadingModel Default setting is SingleThreaded for Qt5 compactable.
 * @param    scene The scene will show in the ViewerWidget.
 * @return   An instance of ViewerWidget.
 */
#include "ViewerWidget.h"
#include <osgViewer/CompositeViewer>
#include <QMessageBox>

ViewerWidget::ViewerWidget(osg::Node* scene/* = osgDB::readNodeFile("glider.osgt")*/,
                           btDynamicsWorld* dynamicsWorld/* = NULL */,
                           osgViewer::ViewerBase::ThreadingModel threadingModel
                           /* = osgViewer::CompositeViewer::SingleThreaded */ )
    : QWidget(),
      m_dynamicsWorld( dynamicsWorld )
{
	setThreadingModel( threadingModel );	 
    setKeyEventSetsDone( 0 );    ///< Disable viewer.done() by ESC

    m_view = new osgViewer::View;

	m_mainWidget = addViewWidget( createGraphicsWindow( 0, 0, 100, 100), scene );

	m_gridLayout = new QGridLayout;
	m_gridLayout->addWidget( m_mainWidget, 0, 0 );
	setLayout( m_gridLayout );

	connect(&m_timer, SIGNAL(timeout()), this, SLOT( update() ));
    m_timer.start( 17 );
}

ViewerWidget::~ViewerWidget(void)
{
}

osgViewer::View* ViewerWidget::getView()
{
    return m_view;
}

/**
 * @brief  Add the viewWidget.
 * @return A pointer to QWidget.
 */
QWidget* ViewerWidget::addViewWidget( osgQt::GraphicsWindowQt* gw, 
	osg::Node* scene )
{
    addView( m_view );

    osg::ref_ptr< osg::Camera > camera = m_view->getCamera();
	camera->setGraphicsContext( gw );

	const osg::GraphicsContext::Traits* traits = gw->getTraits(); /// Set Grapics Window size

	camera->setClearColor( osg::Vec4(0., 0.2, 0.6, 1.0) ); /// Clear Color
	camera->setViewport( new osg::Viewport(0, 0, traits->width, traits->height) );
	camera->setProjectionMatrixAsPerspective( 30.0f, 
		static_cast<double>(traits->width)/static_cast<double>(traits->height), 
		1.0f, 10000.0f );

    m_view->setSceneData( scene );
    m_view->addEventHandler( new osgViewer::StatsHandler );
    m_view->setCameraManipulator( new osgGA::TrackballManipulator );

	return gw->getGLWidget();
}

osgQt::GraphicsWindowQt* ViewerWidget::createGraphicsWindow( int x, int y, int w, int h,
	const std::string& name/* = ""*/, bool windowDecoration/* = false*/ )
{
	osg::DisplaySettings* ds = osg::DisplaySettings::instance().get();
	osg::ref_ptr<osg::GraphicsContext::Traits> traits = new osg::GraphicsContext::Traits;
	traits->windowName = name;
	traits->windowDecoration = windowDecoration;
	traits->x = x;
	traits->y = y;
	traits->width = w;
	traits->height = h;
	traits->doubleBuffer = true;
	traits->alpha = ds->getMinimumNumAlphaBits();
	traits->stencil = ds->getMinimumNumStencilBits();
	traits->sampleBuffers = ds->getMultiSamples();
	traits->samples = ds->getNumMultiSamples();

	return new osgQt::GraphicsWindowQt(traits.get());
}

void ViewerWidget::paintEvent( QPaintEvent* event )
{
    if( m_dynamicsWorld != NULL )///< if the \param dynamicsWorld is omitted
    {
        m_dynamicsWorld->stepSimulation( (btScalar)m_timer.interval()/1000 );
    }
	frame();
}
