#ifndef MESHENTITYPRIVATE_H
#define MESHENTITYPRIVATE_H

#include "TransformEntityPrivate.h"
namespace Qt3DRender {
class QMesh;
class QMaterial;
}

class MeshEntityPrivate : public TransformEntityPrivate
{
public:
    friend class MeshEntity;
public:
    explicit MeshEntityPrivate(Qt3DCore::QEntity* entity);
    ~MeshEntityPrivate();

protected:
    void init() override;

protected:
    /**/
    Qt3DRender::QMesh* m_meshRender = nullptr;
    Qt3DRender::QMaterial* m_material = nullptr;
};

#endif // MESHENTITYPRIVATE_H
