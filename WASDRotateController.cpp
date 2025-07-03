#include "WASDRotateController.h"
#include "WASDControllerPrivate.h"
#include <Qt3DLogic/QFrameAction>
#include <Qt3DCore/QTransform>
#include "KeyNode.h"
#include "TransformEntity.h"
#include <QVector3D>
#include <QQuaternion>
#include <QtCore/QObject>
//#include <QMath>


WASDRotateController::WASDRotateController(QNode *parent)
    : Entity(new WASDControllerPrivate(this), parent)
{
    WASDControllerPrivate* dataPtr = static_cast<WASDControllerPrivate*>(m_privatePtr);
    QObject::connect(dataPtr->m_frameFllusher, &Qt3DLogic::QFrameAction::triggered, this, &WASDRotateController::onFrameFllushSlot);
}

WASDRotateController::WASDRotateController(EntityPrivate *privatePtr, QNode *parent)
    : Entity(privatePtr, parent)
{
    WASDControllerPrivate* dataPtr = static_cast<WASDControllerPrivate*>(m_privatePtr);
    QObject::connect(dataPtr->m_frameFllusher, &Qt3DLogic::QFrameAction::triggered, this, &WASDRotateController::onFrameFllushSlot);
}

WASDRotateController::~WASDRotateController()
{
}

void WASDRotateController::bindEntity(TransformEntity *transformEntity)
{
    WASDControllerPrivate* dataPtr = static_cast<WASDControllerPrivate*>(m_privatePtr);
    dataPtr->bindEntity(transformEntity);
}

void WASDRotateController::removeBindEntity(TransformEntity *transformEntity)
{
    WASDControllerPrivate* dataPtr = static_cast<WASDControllerPrivate*>(m_privatePtr);
    dataPtr->removeBindEntity(transformEntity);
}

float WASDRotateController::horizontalSpeed() const
{
    WASDControllerPrivate* dataPtr = static_cast<WASDControllerPrivate*>(m_privatePtr);
    return dataPtr->horizontalSpeed();
}

void WASDRotateController::setHorizontalSpeed(float newHorizontalSpeed)
{
    WASDControllerPrivate* dataPtr = static_cast<WASDControllerPrivate*>(m_privatePtr);
    dataPtr->setHorizontalSpeed(newHorizontalSpeed);
}

float WASDRotateController::vertialSpeed() const
{
    WASDControllerPrivate* dataPtr = static_cast<WASDControllerPrivate*>(m_privatePtr);
    return dataPtr->vertialSpeed();
}

void WASDRotateController::setVertialSpeed(float newVertialSpeed)
{
    WASDControllerPrivate* dataPtr = static_cast<WASDControllerPrivate*>(m_privatePtr);
    dataPtr->setVertialSpeed(newVertialSpeed);
}

void WASDRotateController::onFrameFllushSlot(float deltaTime)
{
    WASDControllerPrivate* dataPtr = static_cast<WASDControllerPrivate*>(m_privatePtr);

    for(int i=0; i<dataPtr->m_transformEntityList.size(); ++i)
    {
        Qt3DCore::QTransform* transform = dataPtr->m_transformEntityList[i]->transform();
        if(dataPtr->m_wKeyNode->isPressed())
        {
            float origin = transform->rotationX();
            transform->setRotationX(origin + deltaTime*dataPtr->m_vertialSpeed);
        }
        if(dataPtr->m_sKeyNode->isPressed())
        {
            float origin = transform->rotationX();
            transform->setRotationX(origin - deltaTime*dataPtr->m_vertialSpeed);
        }
        if(dataPtr->m_aKeyNode->isPressed())
        {
            float origin = transform->rotationY();
            transform->setRotationY(origin + deltaTime*dataPtr->m_horizontalSpeed);
        }
        if(dataPtr->m_dKeyNode->isPressed())
        {
            float origin = transform->rotationY();
            transform->setRotationY(origin - deltaTime*dataPtr->m_horizontalSpeed);
        }
    }
}

void WASDRotateController::setLeftRotateKeyCode(Qt::Key keyCode)
{
    WASDControllerPrivate* dataPtr = static_cast<WASDControllerPrivate*>(m_privatePtr);
    dataPtr->m_aKeyNode->setKeyCode(keyCode);
}

void WASDRotateController::setRightRotateKeyCode(Qt::Key keyCode)
{
    WASDControllerPrivate* dataPtr = static_cast<WASDControllerPrivate*>(m_privatePtr);
    dataPtr->m_dKeyNode->setKeyCode(keyCode);
}

void WASDRotateController::setUpRotateKeyCode(Qt::Key keyCode)
{
    WASDControllerPrivate* dataPtr = static_cast<WASDControllerPrivate*>(m_privatePtr);
    dataPtr->m_wKeyNode->setKeyCode(keyCode);
}

void WASDRotateController::setDownRotateKeyCode(Qt::Key keyCode)
{
    WASDControllerPrivate* dataPtr = static_cast<WASDControllerPrivate*>(m_privatePtr);
    dataPtr->m_sKeyNode->setKeyCode(keyCode);
}

void WASDRotateController::setRotateKeyCode(Qt::Key leftRotateKeyCode, Qt::Key rightRotateKeyCode, Qt::Key upRotateKeyCode, Qt::Key downRotateKeyCode)
{
    setLeftRotateKeyCode(leftRotateKeyCode);
    setRightRotateKeyCode(rightRotateKeyCode);
    setUpRotateKeyCode(upRotateKeyCode);
    setDownRotateKeyCode(downRotateKeyCode);
}
