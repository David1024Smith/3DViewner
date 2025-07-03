#include "PointLightEntity.h"
#include "PointLightEntityPrivate.h"
#include <Qt3DRender/QPointLight>
#include <QColor>

PointLightEntity::PointLightEntity(QNode *parent)
    : TransformEntity(new PointLightEntityPrivate(this),parent)
{

}

PointLightEntity::PointLightEntity(EntityPrivate *privatePtr, QNode *parent)
    : TransformEntity(privatePtr,parent)
{

}

PointLightEntity::~PointLightEntity()
{

}

void PointLightEntity::setLightColor(const QColor &color)
{
    Qt3DRender::QPointLight* pointLight = this->pointLight();
    pointLight->setColor( color );
}

QColor PointLightEntity::lightColor() const
{
    Qt3DRender::QPointLight* pointLight = this->pointLight();
    return pointLight->color();
}

void PointLightEntity::setIntensity(float intensity)
{
    Qt3DRender::QPointLight* pointLight = this->pointLight();
    pointLight->setIntensity( intensity );
}

float PointLightEntity::intensity() const
{
    Qt3DRender::QPointLight* pointLight = this->pointLight();
    return pointLight->intensity();
}

Qt3DRender::QPointLight *PointLightEntity::pointLight() const
{
    return static_cast<PointLightEntityPrivate*>(m_privatePtr)->m_pointLight;
}

void PointLightEntity::setPointLight(Qt3DRender::QPointLight *pointLight)
{
    /*移除之前的点光源*/
    PointLightEntityPrivate* privatePtr = static_cast<PointLightEntityPrivate*>(m_privatePtr);

    this->removeComponent( privatePtr->m_pointLight );
    this->addComponent( pointLight );
    privatePtr->m_pointLight = pointLight;

    emit pointLightChanged();
}
