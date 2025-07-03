#include "MeshEntity.h"
#include "MeshEntityPrivate.h"
#include <Qt3DRender/QMesh>
#include <Qt3DRender/QMaterial>
#include <QUrl>

MeshEntity::MeshEntity(QNode *parent)
    : TransformEntity(new MeshEntityPrivate(this), parent)
{
}

MeshEntity::MeshEntity(EntityPrivate *privatePtr, QNode *parent)
    : TransformEntity(privatePtr, parent)
{
}

MeshEntity::~MeshEntity()
{
}

void MeshEntity::setSourceUrl(const QUrl &sourceUrl)
{
    Qt3DRender::QMesh* meshRender = this->meshRender();
    meshRender->setSource(sourceUrl);
}

QUrl MeshEntity::sourceUrl() const
{
    Qt3DRender::QMesh* meshRender = this->meshRender();
    return meshRender->source();
}

Qt3DRender::QMesh *MeshEntity::meshRender() const
{
    return static_cast<MeshEntityPrivate*>(m_privatePtr)->m_meshRender;
}

void MeshEntity::setMeshRender(Qt3DRender::QMesh *meshRender)
{
    // Remove previous component
    MeshEntityPrivate* meshPrivatePtr = static_cast<MeshEntityPrivate*>(m_privatePtr);

    this->removeComponent(meshPrivatePtr->m_meshRender);
    this->addComponent(meshRender);
    meshPrivatePtr->m_meshRender = meshRender;

    emit meshRenderChanged();
}

Qt3DRender::QMaterial *MeshEntity::material() const
{
    return static_cast<MeshEntityPrivate*>(m_privatePtr)->m_material;
}

void MeshEntity::setMaterial(Qt3DRender::QMaterial *material)
{
    // Remove previous component
    MeshEntityPrivate* meshPrivatePtr = static_cast<MeshEntityPrivate*>(m_privatePtr);

    this->removeComponent(meshPrivatePtr->m_material);
    this->addComponent(material);
    meshPrivatePtr->m_material = material;

    emit materialChanged();
} 