/**
 * @file ViewerWidget.h
 * @brief Generate an OSGViewer window within Qt frame.
 *
 * @author Delbert
 * @date 2014/05/30
 * 
 * ViewerWidget is derived from QWidget and CompositeViewer, which can
 * be embeded in a Qt Window. CompositeViewer is used for multi-thread.
 */
#pragma once

#include <QtCore/QTimer>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

#include <osgViewer/CompositeViewer>
#include <osgViewer/ViewerEventHandlers>
#include <osgGA/TrackballManipulator>
#include <osgDB/ReadFile>
#include <osgQt/GraphicsWindowQt>


class ViewerWidget :
	public QWidget,
	public osgViewer::CompositeViewer
{
public:
	//ViewerWidget(void);
	ViewerWidget( osgViewer::ViewerBase::ThreadingModel 
		threadingModel = osgViewer::CompositeViewer::SingleThreaded );
	~ViewerWidget(void);

private:
	QWidget* m_mainWidget;

	QWidget* addViewWidget( osgQt::GraphicsWindowQt* gw, osg::Node* scene );
};

