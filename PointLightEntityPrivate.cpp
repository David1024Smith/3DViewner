#include "PointLightEntityPrivate.h"
#include <QEntity>
#include <Qt3DRender/QPointLight>

PointLightEntityPrivate::PointLightEntityPrivate(Qt3DCore::QEntity *entity)
    : TransformEntityPrivate(entity)
{

}

void PointLightEntityPrivate::init()
{
    m_pointLight = new Qt3DRender::QPointLight(m_entity);
    m_pointLight->setColor(Qt::white);
    m_pointLight->setIntensity(1);
    m_entity->addComponent(m_pointLight);

    TransformEntityPrivate::init();
}
