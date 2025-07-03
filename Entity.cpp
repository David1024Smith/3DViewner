#include "Entity.h"
#include "EntityPrivate.h"

Entity::Entity(EntityPrivate *privatePtr, QNode *parent)
    : Qt3DCore::QEntity(parent)
    , m_privatePtr(privatePtr)
{
    m_privatePtr->init();
}

Entity::~Entity()
{
    delete m_privatePtr;
}
