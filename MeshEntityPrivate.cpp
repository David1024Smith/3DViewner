#include "MeshEntityPrivate.h"
#include <Qt3DCore/QEntity>
#include <Qt3DRender/QMesh>
#include <Qt3DRender/QMaterial>
#include <Qt3DExtras/QPhongMaterial>
#include <QColor>

MeshEntityPrivate::MeshEntityPrivate(Qt3DCore::QEntity *entity)
    : TransformEntityPrivate(entity)
{
}

MeshEntityPrivate::~MeshEntityPrivate()
{
}

void MeshEntityPrivate::init()
{
    m_meshRender = new Qt3DRender::QMesh(m_entity);
    m_entity->addComponent(m_meshRender);

    // Material
    Qt3DExtras::QPhongMaterial* phongMaterial = new Qt3DExtras::QPhongMaterial(m_entity);
    phongMaterial->setDiffuse(QColor(Qt::green));
    m_material = phongMaterial;
    m_entity->addComponent(m_material);

    TransformEntityPrivate::init();
} 