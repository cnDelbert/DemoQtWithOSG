#ifndef KBCONTROLLER_H
#define KBCONTROLLER_H

class kbController
        : public osgGA::GUIEventHandler
{
public:
    kbController();
    virtual bool handle( const osgGA::GUIEventAdapter& ea,
                         osgGA::GUIActionAdapter& aa);)
};

#endif // KBCONTROLLER_H
