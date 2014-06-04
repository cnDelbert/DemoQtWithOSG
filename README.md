# Demo of Qt with OSG Viewer Embeded #

This demo is based on Qt5 and OpenSceneGraph 3.2.1, changed from the demo *osgViewerQt* which is provided by OSG.

The demo won't come out until compiled with Qt. I devided the single file project into a multifile project so that we can handle the project better.

Author: Delbert

### Class ViewerWidget ###

This class provide a widget which can embeded into a Qt window. This class is derived from QtWidget and OSG viewer. The widget will update for a fixed time which defined by *_timer*.

### Class DemoQtWithOSG ###

This class is the main class of the app. It defines how the main window should come out and how the framework should be.
