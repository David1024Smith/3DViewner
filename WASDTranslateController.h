#ifndef WASDTRANSLATECONTROLLER_H
#define WASDTRANSLATECONTROLLER_H

#include "Entity.h"
#include <QtCore/Qt>

class TransformEntity;

class WASDTranslateController : public Entity
{
    Q_OBJECT
    friend class WASDControllerPrivate;

public:
    explicit WASDTranslateController(QNode *parent = nullptr);
    WASDTranslateController(EntityPrivate *privatePtr, QNode *parent = nullptr);
    ~WASDTranslateController();

    void bindEntity(TransformEntity* transformEntity);
    void removeBindEntity(TransformEntity* transformEntity);

    float horizontalSpeed() const;
    void setHorizontalSpeed(float newHorizontalSpeed);

    float vertialSpeed() const;
    void setVertialSpeed(float newVertialSpeed);

    void setLeftTranslationKeyCode(Qt::Key keyCode);
    void setRightTranslationKeyCode(Qt::Key keyCode);
    void setForwardTranslationKeyCode(Qt::Key keyCode);
    void setBackTranslationKeyCode(Qt::Key keyCode);

private slots:
    void onFrameFllushSlot(float deltaTime);
};

#endif // WASDTRANSLATECONTROLLER_H 