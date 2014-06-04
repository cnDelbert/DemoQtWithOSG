/**
 * @file
 * @author  Delbert
 * @date    2014/06/03
 * @brief   Main window of the application.
 * @version 0.1.1
 *
 */

#include "demoqtwithosg.h"
#include <QMessageBox>

DemoQtWithOSG::DemoQtWithOSG(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

    createActions();
    createMenus();
    createToolbars();
    createStatusBar();

	osg::ref_ptr< osg::Node > cow = osgDB::readNodeFile("cow.osgt");
	osg::ref_ptr< osg::Group > root = new osg::Group;
	root->addChild( cow );
	
	osgViewer::ViewerBase::ThreadingModel threadingModel = 
		osgViewer::ViewerBase::SingleThreaded; /// Explict declaration for Qt 5
    viewerWidget = new ViewerWidget( root, threadingModel );
	setCentralWidget( viewerWidget );
	// 	viewerWidget->setGeometry(100, 100, 800, 600 );
 	viewerWidget->show();
	
}

DemoQtWithOSG::~DemoQtWithOSG()
{

}

void DemoQtWithOSG::aboutMsgBox()
{
    QMessageBox::about( this, tr("About this App"),
                        tr("The DemoQtWithOSG is a demo of\n"
                           "combination of OpenSceneGraph and\n"
                           "Qt5. The scene is embeded in a Qt5 Window."));

}

void DemoQtWithOSG::createActions()
{
    // TODO 20140604: connect should be added.
    /** Create newAction */
    m_newAction = new QAction( QIcon(":/img/new"), tr("&New"), this);
    m_newAction->setShortcut( QKeySequence::New );
    m_newAction->setStatusTip( tr("Create a new scene.") );

    /** Create openAction */
    m_openAction = new QAction( QIcon(":/img/open"), tr("&Open"), this);
    m_openAction->setShortcut( QKeySequence::Open );
    m_openAction->setStatusTip( tr("Open a file.") );

    /** Create saveAction */
    m_saveAction = new QAction( QIcon(":/img/save"), tr("&Save"), this);
    m_saveAction->setShortcut( QKeySequence::Save );
    m_saveAction->setStatusTip( tr("Save current status"));

    /** Create copyAction */
    m_copyAction = new QAction( QIcon(":/img/copy"), tr("&Copy"), this);
    m_copyAction->setShortcut( QKeySequence::Copy );
    m_copyAction->setStatusTip( tr("Copy") );

    /** Create pasteAction */
    m_pasteAction = new QAction( QIcon(":/img/paste"), tr("&Paste"), this);
    m_pasteAction->setShortcut( QKeySequence::Paste );
    m_pasteAction->setStatusTip( tr("Paste") );

    /** Create cutAction */
    m_cutAction = new QAction( QIcon(":/img/cut"), tr("C&ut"), this);
    m_cutAction->setShortcut( QKeySequence::Cut );
    m_cutAction->setStatusTip( tr("Cut") );

    /** Create aboutAction */
    m_aboutAction = new QAction( tr("&About..."), this);
    m_aboutAction->setStatusTip( tr("About the app..."));
    connect(m_aboutAction, SIGNAL(triggered()), this, SLOT(aboutMsgBox()) );
}

void DemoQtWithOSG::createMenus()
{
    /** File Menu */
    m_fileMenu = menuBar()->addMenu( tr("&File") );
    m_fileMenu->addAction( m_newAction );
    m_fileMenu->addAction( m_openAction );
    m_fileMenu->addAction( m_saveAction );

    /** Edit Menu */
    m_editMenu = menuBar()->addMenu( tr("&Edit") );
    m_editMenu->addAction( m_copyAction );
    m_editMenu->addAction( m_pasteAction );
    m_editMenu->addAction( m_cutAction );

    /** View Menu */
    m_viewMenu = menuBar()->addMenu( tr("&View") );
    // TODO 20140604

    /** Help Menu */
    m_helpMenu = menuBar()->addMenu( tr("&Help") );
    m_helpMenu->addAction( m_aboutAction );
    // TODO 20140604
}

void DemoQtWithOSG::createToolbars()
{
    /** File Toolbar */
    m_fileToolbar = addToolBar( tr("File") );
    m_fileToolbar->addAction( m_newAction );
    m_fileToolbar->addAction( m_openAction );
    m_fileToolbar->addAction( m_saveAction );

    /** Edit Toolbar */
    m_editToolbar = addToolBar( tr("Edit") );
    m_editToolbar->addAction( m_copyAction );
    m_editToolbar->addAction( m_pasteAction );
    m_editToolbar->addAction( m_cutAction );
}

void DemoQtWithOSG::createStatusBar()
{
    statusBar()->showMessage( tr("Ready."));
}
