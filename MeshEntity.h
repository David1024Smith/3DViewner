#ifndef MESHENTITY_H
#define MESHENTITY_H

#include "TransformEntity.h"
namespace Qt3DRender {
class QMesh;
class QMaterial;
}

class MeshEntity : public TransformEntity
{
    Q_OBJECT
    friend class MeshEntityPrivate;
signals:
    void meshRenderChanged();
    void materialChanged();
public:
    explicit MeshEntity(QNode *parent = nullptr);
    MeshEntity(EntityPrivate *privatePtr, QNode *parent = nullptr);
    ~MeshEntity();

    void setSourceUrl(const QUrl& sourceUrl);
    QUrl sourceUrl() const;


    Qt3DRender::QMesh* meshRender() const;
    void setMeshRender(Qt3DRender::QMesh* meshRender);


    Qt3DRender::QMaterial* material() const;
    void setMaterial(Qt3DRender::QMaterial* material);
};

#endif // MESHENTITY_H
