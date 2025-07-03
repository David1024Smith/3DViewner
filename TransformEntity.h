#ifndef TRANSFORMENTITY_H
#define TRANSFORMENTITY_H

#include "Entity.h"
#include <QVector3D>
#include <QQuaternion>
#include <Qt3DCore/QTransform>

namespace Qt3DCore {
class QTransform;
}

class TransformEntity : public Entity
{
    Q_OBJECT
    friend class TransformEntityPrivate;
signals:
    // transform object changed signal
    void transformComponentChanged();

public:
    explicit TransformEntity(QNode *parent = nullptr);
    TransformEntity(EntityPrivate *privatePtr, QNode *parent = nullptr);
    ~TransformEntity();

    // Set Position
    void setTranslation(const QVector3D& position);
    QVector3D translation() const;

    // Set rotation
    void setRotation(const QQuaternion& rotation);
    QQuaternion rotation() const;

    // Scale
    void setScale(const QVector3D &scale);
    QVector3D scale() const;

    // Get transform
    Qt3DCore::QTransform* transform() const;
    void setTransform(Qt3DCore::QTransform* transform);
};

#endif // TRANSFORMENTITY_H 