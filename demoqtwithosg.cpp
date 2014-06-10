/**
 * @file
 * @author  Delbert
 * @date    2014/06/06
 * @brief   Main window of the application.
 * @version 0.1.3
 * 
 * 
 * 0.1.3 add bullet support.
 * 0.1.1 basic functions
 */

#include "demoqtwithosg.h"
#include "kbController.h"
#include <QMessageBox>
#include <QLabel>

/** Bullet Headers */
#include <btBulletDynamicsCommon.h>

/** osgBullet Headers */
#include <osgbCollision/CollisionShapes.h>
#include <osgbDynamics/MotionState.h>

/** OSG Headers */
#include <osg/Shape>
#include <osg/ShapeDrawable>

/** For bullet Demo */
osg::MatrixTransform* createOSGBox( osg::Vec3 size )
{
    osg::Box* box = new osg::Box();
    box->setHalfLengths( size );
    osg::ShapeDrawable * shape = new osg::ShapeDrawable( box );
    osg::Geode * geode = new osg::Geode();
    geode->addDrawable( shape );
    osg::MatrixTransform * transform = new osg::MatrixTransform();
    transform->addChild( geode );
    return( transform );
}
osg::MatrixTransform* createOSGSphere( btScalar radius ) ///< Create an OSG sphere
{
    osg::Sphere* sphere = new osg::Sphere();
    sphere->setRadius( radius );
    osg::ShapeDrawable* shape = new osg::ShapeDrawable( sphere );
    osg::Geode* geode = new osg::Geode;
    geode->addDrawable( shape );
    osg::MatrixTransform* tr = new osg::MatrixTransform;
    tr->addChild( geode );
    return tr;
}
btRigidBody* createBTSphere( osg::MatrixTransform* sphere,
                             osg::Vec3 center )
{
    btCollisionShape* collision = osgbCollision::btSphereCollisionShapeFromOSG( sphere );
    osgbDynamics::MotionState* motion = new osgbDynamics::MotionState;
    motion->setTransform( sphere );
    motion->setParentTransform( osg::Matrix::translate( center ));

    btScalar mass(1.0f);
    btVector3 inertia;
    collision->calculateLocalInertia( mass, inertia );
    btRigidBody::btRigidBodyConstructionInfo rb( mass, motion, collision, inertia );
    btRigidBody* body = new btRigidBody( rb );
    return body;
}

btRigidBody * createSBTBox( osg::MatrixTransform * box,
    osg::Vec3 center )//return the Bullet with the center as the center of mass
{
    btCollisionShape * collision = osgbCollision::btBoxCollisionShapeFromOSG( box );//create a collision shape from box
    osgbDynamics::MotionState * motion = new osgbDynamics::MotionState();
    motion->setTransform( box );
    motion->setParentTransform( osg::Matrix::translate( center ) );
    btScalar mass( 0.0 );
    btVector3 inertia( 0, 0, 0 );//
    btRigidBody::btRigidBodyConstructionInfo rb( mass, motion, collision, inertia );//init the rigidBody
    btRigidBody * body = new btRigidBody( rb );
    return( body );
}
btRigidBody * createBTBox( osg::MatrixTransform * box,
    osg::Vec3 center )//return the Bullet with the center as the center of mass
{
    btCollisionShape * collision = osgbCollision::btBoxCollisionShapeFromOSG( box );//create a collision shape from box
    osgbDynamics::MotionState * motion = new osgbDynamics::MotionState();
    motion->setTransform( box );
    motion->setParentTransform( osg::Matrix::translate( center ) );
    btScalar mass( 1.0 );
    btVector3 inertia( 0, 0, 0 );  // can also be calculated
    btRigidBody::btRigidBodyConstructionInfo rb( mass, motion, collision, inertia );//init the rigidBody
    btRigidBody * body = new btRigidBody( rb );
    return( body );
}

/** Physics Initialize */
btDynamicsWorld* initPhysics()//Physics Initialize
{
    btDefaultCollisionConfiguration * collisionConfiguration = new btDefaultCollisionConfiguration();
    btCollisionDispatcher * dispatcher = new btCollisionDispatcher( collisionConfiguration );
    btConstraintSolver * solver = new btSequentialImpulseConstraintSolver;

    btVector3 worldAabbMin( -10000, -10000, -10000 );
    btVector3 worldAabbMax( 10000, 10000, 10000 );
    btBroadphaseInterface * inter = new btAxisSweep3( worldAabbMin, worldAabbMax, 1000 );

    btDynamicsWorld * dynamicsWorld = new btDiscreteDynamicsWorld( dispatcher, inter, solver, collisionConfiguration );
    dynamicsWorld->setGravity( btVector3( 0, 0, -9.8 ) );

    return( dynamicsWorld );
}

DemoQtWithOSG::DemoQtWithOSG(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

    createActions();
    createMenus();
    createToolbars();
    createStatusBar();

	osg::ref_ptr< osg::Node > cow = osgDB::readNodeFile("cow.osgt");
    osg::ref_ptr< osg::Group > scene2 = new osg::Group;
    scene2->addChild( cow );

    /** \brief Create a box and a ground, to simulate the world */
    osg::ref_ptr< osg::Group > scene1 = new osg::Group;
    btDynamicsWorld* dynamicsWorld = initPhysics();
    osg::ref_ptr< osg::MatrixTransform > ground;
    btRigidBody* groundBody;

    float thin = .01;//
    ground = createOSGBox( osg::Vec3( 50, 50, thin ) );//ground area
    groundBody = createSBTBox( ground, osg::Vec3( 0, 0, 0 ) );

    scene1->addChild( ground );
    osg::ref_ptr< osg::MatrixTransform > box    = new osg::MatrixTransform;
    osg::ref_ptr< osg::MatrixTransform > sphere = new osg::MatrixTransform;
    btRigidBody* rbBox;
    btRigidBody* rbSphere;
    box      = createOSGBox( osg::Vec3(2, 2, 2) );
    rbBox    = createBTBox( box, osg::Vec3( 10, 0 ,50));
    sphere   = createOSGSphere( 1.0f );
    rbSphere = createBTSphere( sphere, osg::Vec3( 0, 0, 100 ) );

    scene1->addChild(box);
    scene1->addChild(sphere);
    dynamicsWorld->addRigidBody(rbBox);
    dynamicsWorld->addRigidBody(rbSphere);
    dynamicsWorld->addRigidBody( groundBody );

    /** \brief ViewerWidget with physics */
    ViewerWidget* vw = new ViewerWidget( scene1, dynamicsWorld );
    kbController* hand = new kbController( rbSphere, true );
    vw->getView()->addEventHandler( hand );  ///< Still there some problem with controller

	osgViewer::ViewerBase::ThreadingModel threadingModel = 
        osgViewer::ViewerBase::SingleThreaded; ///< Explict declaration for Qt 5
    viewerWidget = new ViewerWidget( scene2, NULL, threadingModel );

    //viewerWidget->setGeometry(100, 100, 800, 600 );
    //viewerWidget->show();

    QLabel* labelLeft  = new QLabel( tr("OSG with bullet"), this);
    QLabel* labelRight = new QLabel( tr("OSG without bullet"), this);

    m_mainGridLayout = new QGridLayout;
    m_mainGridLayout->addWidget( vw, 0, 0, 4, 1 );
    m_mainGridLayout->addWidget( viewerWidget, 0, 1, 4, 1 );
    m_mainGridLayout->addWidget( labelLeft, 4, 0, 1, 1 , Qt::AlignCenter | Qt::AlignHCenter );
    m_mainGridLayout->addWidget( labelRight, 4, 1, 1, 1 , Qt::AlignCenter | Qt::AlignHCenter );

    centralWidget()->setLayout( m_mainGridLayout );
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
