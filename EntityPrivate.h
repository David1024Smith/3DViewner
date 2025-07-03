#ifndef ENTITYPRIVATE_H
#define ENTITYPRIVATE_H

namespace Qt3DCore {
class QEntity;
}
#include <QObject>
class EntityPrivate
{
    friend class Entity;
public:
    EntityPrivate(Qt3DCore::QEntity* entity);
    virtual ~EntityPrivate() = default;

protected:
    virtual void init();
protected:
    /*实体*/
    Qt3DCore::QEntity* m_entity = nullptr;
};

#endif // ENTITYPRIVATE_H
