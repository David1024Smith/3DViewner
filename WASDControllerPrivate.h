#ifndef WASDCONTROLLERPRIVATE_H
#define WASDCONTROLLERPRIVATE_H

#include <QList>
#include "EntityPrivate.h"
namespace Qt3DInput {
class QKeyboardDevice;
class QLogicalDevice;
}
namespace Qt3DLogic {
class QFrameAction;
}
class TransformEntity;
class KeyNode;

class WASDControllerPrivate : public EntityPrivate
{
    friend class WASDRotateController;
    friend class WASDTranslateController;
public:
    WASDControllerPrivate(Qt3DCore::QEntity* entity);

    void bindEntity(TransformEntity* transformEntity);
    void removeBindEntity(TransformEntity* transformEntity);

    float horizontalSpeed() const;
    void setHorizontalSpeed(float newHorizontalSpeed);

    float vertialSpeed() const;
    void setVertialSpeed(float newVertialSpeed);

protected:
    void init() override;

protected:
    Qt3DInput::QKeyboardDevice* m_keyboardDevice = nullptr;
    Qt3DInput::QLogicalDevice* m_logicDevice = nullptr;
    Qt3DLogic::QFrameAction* m_frameFllusher = nullptr;

    QList<TransformEntity*> m_transformEntityList;

    KeyNode* m_wKeyNode = nullptr;
    KeyNode* m_aKeyNode = nullptr;
    KeyNode* m_sKeyNode = nullptr;
    KeyNode* m_dKeyNode = nullptr;

    float m_horizontalSpeed = 50;
    float m_vertialSpeed = 50 ;
};

#endif // WASDCONTROLLERPRIVATE_H
