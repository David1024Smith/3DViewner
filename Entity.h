#ifndef ENTITY_H
#define ENTITY_H

#include <Qt3DCore/QEntity>

class EntityPrivate;
class Entity : public Qt3DCore::QEntity
{
    friend class EntityPrivate;
public:
    Entity(EntityPrivate* privatePtr, QNode *parent = nullptr);
    ~Entity();

protected:
    EntityPrivate* m_privatePtr;
};

#endif // ENTITY_H
