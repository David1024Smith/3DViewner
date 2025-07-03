#include "TransformEntity.h"
#include "TransformEntityPrivate.h"
#include <Qt3DCore/QTransform>
#include <QVector3D>
#include <QQuaternion>

TransformEntity::TransformEntity(QNode *parent)
    : Entity(new TransformEntityPrivate(this), parent)
{
}

TransformEntity::TransformEntity(EntityPrivate* privatePtr, QNode *parent)
    : Entity(privatePtr, parent)
{
}

TransformEntity::~TransformEntity()
{
}

void TransformEntity::setTranslation(const QVector3D &position)
{
    Qt3DCore::QTransform* transform = this->transform();
    transform->setTranslation(position);
}

QVector3D TransformEntity::translation() const
{
    Qt3DCore::QTransform* transform = this->transform();
    return transform->translation();
}

void TransformEntity::setRotation(const QQuaternion &rotation)
{
    Qt3DCore::QTransform* transform = this->transform();
    transform->setRotation(rotation);
}

QQuaternion TransformEntity::rotation() const
{
    Qt3DCore::QTransform* transform = this->transform();
    return transform->rotation();
}

void TransformEntity::setScale(const QVector3D &scale)
{
    Qt3DCore::QTransform* transform = this->transform();
    transform->setScale3D(scale);
}

QVector3D TransformEntity::scale() const
{
    Qt3DCore::QTransform* transform = this->transform();
    return transform->scale3D();
}

Qt3DCore::QTransform *TransformEntity::transform() const
{
    return static_cast<TransformEntityPrivate*>(m_privatePtr)->m_transform;
}

void TransformEntity::setTransform(Qt3DCore::QTransform *transform)
{
    // 移除之前的transform组件
    TransformEntityPrivate* privatePtr = static_cast<TransformEntityPrivate*>(m_privatePtr);

    this->removeComponent(privatePtr->m_transform);
    this->addComponent(transform);
    privatePtr->m_transform = transform;

    emit transformComponentChanged();
}
