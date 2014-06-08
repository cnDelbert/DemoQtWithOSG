#include "kbController.h"
#include <QDebug>
/**
 * @brief kbController::kbController
 * @param rigidBody
 * @param statusFlag
 */
kbController::kbController( btRigidBody *rigidBody,
                            bool statusFlag )
    : m_rigidBody( rigidBody ),
      m_statusFLag( statusFlag )
{
    m_motionState = m_rigidBody->getMotionState();
    m_motionState->getWorldTransform( m_wTransform );

    m_origin      = m_wTransform->getOrigin();
    m_rotation    = m_wTransform->getRotation();
}

/**
 * @brief kbController::handle is a handler to keyboard events.
 * @param ea
 * @param aa
 * @return true if handled, false otherwise.
 */
bool kbController::handle(const osgGA::GUIEventAdapter &ea,
                          osgGA::GUIActionAdapter &aa)
{
    /** Check the work status of the handler to avoid mis-trigger */
    if( false == m_statusFLag )
        return false;

    switch( ea.getEventType() )
    {
    case osgGA::GUIEventAdapter::KEYDOWN:
    {
        switch ( ea.getKey() )
        {
        case osgGA::GUIEventAdapter::KEY_A:
        case osgGA::GUIEventAdapter::KEY_Left:
        case 'A':
            // TODO
            qDebug<<"Turn Left";
            return true;
            break;

        case osgGA::GUIEventAdapter::KEY_D:
        case osgGA::GUIEventAdapter::KEY_Right:
        case 'D':
            // TODO
            qDebug<<"Turn Right";
            return true;
            break;

        case osgGA::GUIEventAdapter::KEY_W:
        case osgGA::GUIEventAdapter::KEY_UP:
        case 'W':
            // TODO
            qDebug<<"Go Ahead";
            m_wTransform->setOrigin( btVector3( m_origin.getX(),
                                                m_origin.getY() + 1,
                                                m_origin.getZ() ) );
            return true;
            break;

        case osgGA::GUIEventAdapter::KEY_S:
        case osgGA::GUIEventAdapter::KEY_Down:
        case 'S':
            // TODO
            qDebug<<"Backward";
            return true;
            break;

        default:
            return false;
            break;
        }
    }
    }

}
