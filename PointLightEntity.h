#ifndef POINTLIGHTENTITY_H
#define POINTLIGHTENTITY_H

#include "TransformEntity.h"
#include <QColor>

namespace Qt3DRender {
class QPointLight;
}

class PointLightEntity : public TransformEntity
{
    Q_OBJECT
    friend class PointLightEntityPrivate;
signals:
    void pointLightChanged();

public:
    explicit PointLightEntity(QNode *parent = nullptr);
    PointLightEntity(EntityPrivate *privatePtr, QNode *parent = nullptr);
    ~PointLightEntity();

    void setLightColor(const QColor& color);
    QColor lightColor() const;

    void setIntensity(float intensity);
    float intensity() const;

    Qt3DRender::QPointLight* pointLight() const;
    void setPointLight(Qt3DRender::QPointLight* pointLight);
};

#endif // POINTLIGHTENTITY_H 