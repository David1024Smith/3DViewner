#include "WASDControllerPrivate.h"
#include <QKeyboardDevice>
#include <QLogicalDevice>
#include <QFrameAction>
#include <QTransform>
#include "KeyNode.h"
#include "TransformEntity.h"

WASDControllerPrivate::WASDControllerPrivate(Qt3DCore::QEntity *entity)
    : EntityPrivate(entity)
{

}

void WASDControllerPrivate::init()
{
    m_keyboardDevice = new Qt3DInput::QKeyboardDevice(m_entity);
    m_logicDevice = new Qt3DInput::QLogicalDevice(m_entity);
    m_frameFllusher = new Qt3DLogic::QFrameAction(m_entity);

    m_wKeyNode = new KeyNode(Qt::Key_W,m_keyboardDevice,m_logicDevice,m_entity);
    m_sKeyNode = new KeyNode(Qt::Key_S,m_keyboardDevice,m_logicDevice,m_entity);
    m_aKeyNode = new KeyNode(Qt::Key_A,m_keyboardDevice,m_logicDevice,m_entity);
    m_dKeyNode = new KeyNode(Qt::Key_D,m_keyboardDevice,m_logicDevice,m_entity);

}

void WASDControllerPrivate::bindEntity(TransformEntity *transformEntity)
{
    m_transformEntityList.append( transformEntity );
    transformEntity->addComponent( m_logicDevice );
    transformEntity->addComponent( m_frameFllusher );
}

void WASDControllerPrivate::removeBindEntity(TransformEntity *transformEntity)
{
    m_transformEntityList.removeOne( transformEntity );
}

float WASDControllerPrivate::horizontalSpeed() const
{
    return m_horizontalSpeed;
}

void WASDControllerPrivate::setHorizontalSpeed(float newHorizontalSpeed)
{
    m_horizontalSpeed = newHorizontalSpeed;
}

float WASDControllerPrivate::vertialSpeed() const
{
    return m_vertialSpeed;
}

void WASDControllerPrivate::setVertialSpeed(float newVertialSpeed)
{
    m_vertialSpeed = newVertialSpeed;
}
