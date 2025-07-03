#ifndef TRANSFORMENTITYPRIVATE_H
#define TRANSFORMENTITYPRIVATE_H

#include "EntityPrivate.h"
namespace Qt3DCore {
class QTransform;
class QEntity;
}
class TransformEntity;

class TransformEntityPrivate : public EntityPrivate
{
public:
    friend class TransformEntity;
public:
    TransformEntityPrivate(Qt3DCore::QEntity* entity);
    ~TransformEntityPrivate();

protected:
    void init() override;
protected:
    /*transfrom组件*/
    Qt3DCore::QTransform* m_transform = nullptr;
};

#endif // TRANSFORMENTITYPRIVATE_H
