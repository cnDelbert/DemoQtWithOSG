/**
 * @file  
 * @class    DemoQtWithOSG
 * @author   Delbert
 * @date     2014/05/30
 * @version  0.1.1
 * @brief    The MainWindow class
 */

#ifndef DEMOQTWITHOSG_H
#define DEMOQTWITHOSG_H

//#include <QtWidgets>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QAction>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QMenu>

#include "ui_demoqtwithosg.h"
#include "ViewerWidget.h"

class DemoQtWithOSG : public QMainWindow
{
	Q_OBJECT

public:
	DemoQtWithOSG(QWidget *parent = 0);
	~DemoQtWithOSG();
	/** Widget to show the scene. */
	ViewerWidget* viewerWidget;

private slots:
    void aboutMsgBox();

private:
	Ui::DemoQtWithOSGClass ui;

	/* Actions */
	QAction* m_newAction;
	QAction* m_openAction;
	QAction* m_saveAction;
    QAction* m_saveAsAction;
    QAction* m_exitAction;

    QAction* m_copyAction;
    QAction* m_pasteAction;
    QAction* m_cutAction;

    QAction* m_aboutAction;

	/* Menus */
    QMenu* m_fileMenu; ///< File Menu
    QMenu* m_editMenu; ///< Edit Menu
    QMenu* m_viewMenu; ///< View Menu
    QMenu* m_helpMenu; ///< Help Menu

    /* Toolbars */
    QToolBar* m_fileToolbar;
    QToolBar* m_editToolbar;

    /* Widgets */

    /* Member vals */

    /* Methods */
    void createActions();
    void createMenus();
    void createToolbars();
    void createStatusBar();

};

#endif // DEMOQTWITHOSG_H
