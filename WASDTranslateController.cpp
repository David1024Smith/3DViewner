#include "WASDTranslateController.h"
#include "WASDControllerPrivate.h"
#include "KeyNode.h"
#include "TransformEntity.h"
#include <Qt3DCore/QTransform>
#include <QVector3D>
#include <Qt3DLogic/QFrameAction>
#include <QtCore/QObject>

WASDTranslateController::WASDTranslateController(QNode *parent)
    : Entity(new WASDControllerPrivate(this), parent)
{
    WASDControllerPrivate* dataPtr = static_cast<WASDControllerPrivate*>(m_privatePtr);
    QObject::connect(dataPtr->m_frameFllusher, &Qt3DLogic::QFrameAction::triggered, this, &WASDTranslateController::onFrameFllushSlot);
}

WASDTranslateController::WASDTranslateController(EntityPrivate *privatePtr, QNode *parent)
    : Entity(privatePtr, parent)
{
    WASDControllerPrivate* dataPtr = static_cast<WASDControllerPrivate*>(m_privatePtr);
    QObject::connect(dataPtr->m_frameFllusher, &Qt3DLogic::QFrameAction::triggered, this, &WASDTranslateController::onFrameFllushSlot);
}

WASDTranslateController::~WASDTranslateController()
{
}

void WASDTranslateController::bindEntity(TransformEntity *transformEntity)
{
    WASDControllerPrivate* dataPtr = static_cast<WASDControllerPrivate*>(m_privatePtr);
    dataPtr->bindEntity(transformEntity);
}

void WASDTranslateController::removeBindEntity(TransformEntity *transformEntity)
{
    WASDControllerPrivate* dataPtr = static_cast<WASDControllerPrivate*>(m_privatePtr);
    dataPtr->removeBindEntity(transformEntity);
}

float WASDTranslateController::horizontalSpeed() const
{
    WASDControllerPrivate* dataPtr = static_cast<WASDControllerPrivate*>(m_privatePtr);
    return dataPtr->horizontalSpeed();
}

void WASDTranslateController::setHorizontalSpeed(float newHorizontalSpeed)
{
    WASDControllerPrivate* dataPtr = static_cast<WASDControllerPrivate*>(m_privatePtr);
    dataPtr->setHorizontalSpeed(newHorizontalSpeed);
}

float WASDTranslateController::vertialSpeed() const
{
    WASDControllerPrivate* dataPtr = static_cast<WASDControllerPrivate*>(m_privatePtr);
    return dataPtr->vertialSpeed();
}

void WASDTranslateController::setVertialSpeed(float newVertialSpeed)
{
    WASDControllerPrivate* dataPtr = static_cast<WASDControllerPrivate*>(m_privatePtr);
    dataPtr->setVertialSpeed(newVertialSpeed);
}

void WASDTranslateController::setLeftTranslationKeyCode(Qt::Key keyCode)
{
    WASDControllerPrivate* dataPtr = static_cast<WASDControllerPrivate*>(m_privatePtr);
    dataPtr->m_aKeyNode->setKeyCode(keyCode);
}

void WASDTranslateController::setRightTranslationKeyCode(Qt::Key keyCode)
{
    WASDControllerPrivate* dataPtr = static_cast<WASDControllerPrivate*>(m_privatePtr);
    dataPtr->m_dKeyNode->setKeyCode(keyCode);
}

void WASDTranslateController::setForwardTranslationKeyCode(Qt::Key keyCode)
{
    WASDControllerPrivate* dataPtr = static_cast<WASDControllerPrivate*>(m_privatePtr);
    dataPtr->m_wKeyNode->setKeyCode(keyCode);
}

void WASDTranslateController::setBackTranslationKeyCode(Qt::Key keyCode)
{
    WASDControllerPrivate* dataPtr = static_cast<WASDControllerPrivate*>(m_privatePtr);
    dataPtr->m_sKeyNode->setKeyCode(keyCode);
}

// void WASDTranslateController::setTranslationKeyCode(Qt::Key leftTranslationKeyCode, Qt::Key rightTranslationKeyCode, Qt::Key forwardTranslationKeyCode, Qt::Key backTranslationKeyCode)
// {
//     setLeftTranslationKeyCode(leftTranslationKeyCode);
//     setRightTranslationKeyCode(rightTranslationKeyCode);
//     setForwardTranslationKeyCode(forwardTranslationKeyCode);
//     setBackTranslationKeyCode(backTranslationKeyCode);
// }

void WASDTranslateController::onFrameFllushSlot(float deltaTime)
{
    WASDControllerPrivate* dataPtr = static_cast<WASDControllerPrivate*>(m_privatePtr);

    for(int i=0; i<dataPtr->m_transformEntityList.size(); ++i)
    {
        Qt3DCore::QTransform* transform = dataPtr->m_transformEntityList[i]->transform();
        if(dataPtr->m_wKeyNode->isPressed())
        {
            QVector3D position = transform->translation();
            float zPosition = position.z() - deltaTime*dataPtr->m_vertialSpeed;
            position.setZ(zPosition);
            transform->setTranslation(position);
        }
        if(dataPtr->m_sKeyNode->isPressed())
        {
            QVector3D position = transform->translation();
            float zPosition = position.z() + deltaTime*dataPtr->m_vertialSpeed;
            position.setZ(zPosition);
            transform->setTranslation(position);
        }
        if(dataPtr->m_aKeyNode->isPressed())
        {
            QVector3D position = transform->translation();
            float xPosition = position.x() - deltaTime*dataPtr->m_vertialSpeed;
            position.setX(xPosition);
            transform->setTranslation(position);
        }
        if(dataPtr->m_dKeyNode->isPressed())
        {
            QVector3D position = transform->translation();
            float xPosition = position.x() + deltaTime*dataPtr->m_vertialSpeed;
            position.setX(xPosition);
            transform->setTranslation(position);
        }
    }
}
