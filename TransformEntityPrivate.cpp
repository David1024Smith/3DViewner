#include "TransformEntityPrivate.h"
#include <QEntity>
#include <QDebug>
#include <Qt3DCore/QTransform>
#include <QVector3D>

TransformEntityPrivate::TransformEntityPrivate(Qt3DCore::QEntity* entity)
    : EntityPrivate(entity)
{

}

TransformEntityPrivate::~TransformEntityPrivate()
{

}

void TransformEntityPrivate::init()
{
    /*创建transform组件*/
    m_transform = new Qt3DCore::QTransform(m_entity);
    m_entity->addComponent( m_transform );

    /*复位位置*/
    m_transform->setTranslation(QVector3D(0,0,0));
}
