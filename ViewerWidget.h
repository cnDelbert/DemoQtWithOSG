/**
 * @file
 * @class   ViewerWidget
 * @brief   Generate an OSGViewer window within Qt frame.
 *
 * @author  Delbert
 * @date    2014/06/06
 * @version 0.1.3
 * 
 * 0.1.3 Add getView method, so that event handler can be added.
 * 0.1.2 Add bullet support.
 * 0.1.1 Basic functions.
 *
 * ViewerWidget is derived from QWidget and CompositeViewer, which can
 * be embeded in a Qt Window. CompositeViewer is used for multi-thread.
 */
#pragma once

#include <QtCore/QTimer>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QtWidgets/QGridLayout>

#include <osgViewer/CompositeViewer>
#include <osgViewer/ViewerEventHandlers>
#include <osgGA/TrackballManipulator>
#include <osgDB/ReadFile>
#include <osgQt/GraphicsWindowQt>


#include <btBulletDynamicsCommon.h>


class ViewerWidget :
	public QWidget,
	public osgViewer::CompositeViewer
{
public:
	/** Create an instance of ViewerWidget. */
    ViewerWidget( osg::Node* scene = osgDB::readNodeFile("cow.osgt"),
                  btDynamicsWorld* dynamicsWorld = NULL,
                  osgViewer::ViewerBase::ThreadingModel
                  threadingModel = osgViewer::CompositeViewer::SingleThreaded );

	/** create a GraphicsWindow to show the scene. */
	osgQt::GraphicsWindowQt* createGraphicsWindow(int x, int y, int w, int h,
		const std::string& name = "", bool windowDecoration = false );

	/** Override the paintEvent to update the scene. */
	virtual void paintEvent( QPaintEvent* event ); 
	~ViewerWidget( void );

    /** Get Methods to get obj or status */
    osgViewer::View* getView();

protected:
	/** Tick time for update function. */
	QTimer m_timer; 

private:
    /** Qt */
	QWidget* m_mainWidget;    
	QGridLayout* m_gridLayout;

    QWidget* addViewWidget( osgQt::GraphicsWindowQt* gw, osg::Node* scene );

    /** OSG */
    osgViewer::View* m_view;

    /** bullet */
    btDynamicsWorld* m_dynamicsWorld;

};

