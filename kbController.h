#ifndef KBCONTROLLER_H
#define KBCONTROLLER_H

#include <osgGA/GUIEventHandler>
#include <btBulletDynamicsCommon.h>
/**
 * @brief The kbController class
 */
class kbController
        : public osgGA::GUIEventHandler
{
public:
    kbController( btRigidBody* rigidBody,
                  bool statusFlag = false );
    virtual bool handle( const osgGA::GUIEventAdapter& ea,
                         osgGA::GUIActionAdapter& aa);

private:
    bool           m_statusFLag; ///< true for work while false for idle

    btVector3      m_origin;
    btQuaternion   m_rotation;
    btRigidBody*   m_rigidBody;
    btMotionState* m_motionState;
    btTransform*   m_wTransform;

};

#endif // KBCONTROLLER_H
