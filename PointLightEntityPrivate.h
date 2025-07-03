#ifndef POINTLIGHTENTITYPRIVATE_H
#define POINTLIGHTENTITYPRIVATE_H

#include "TransformEntityPrivate.h"
namespace Qt3DRender {
class QPointLight;
}

class PointLightEntityPrivate : public TransformEntityPrivate
{
    friend class PointLightEntity;
public:
    PointLightEntityPrivate(Qt3DCore::QEntity *entity);

protected:
    void init() override;
protected:
    // 点光源
    Qt3DRender::QPointLight* m_pointLight = nullptr;
};

#endif // POINTLIGHTENTITYPRIVATE_H
