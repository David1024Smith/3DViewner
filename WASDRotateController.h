#ifndef WASDROTATECONTROLLER_H
#define WASDROTATECONTROLLER_H

#include "Entity.h"
#include <QtCore/Qt>

class TransformEntity;

class WASDRotateController : public Entity
{
    Q_OBJECT
public:
    explicit WASDRotateController(QNode *parent = nullptr);
    WASDRotateController(EntityPrivate *privatePtr, QNode *parent = nullptr);
    ~WASDRotateController();

    // 绑定实体
    void bindEntity(TransformEntity* transformEntity);
    void removeBindEntity(TransformEntity* transformEntity);

    // 水平速度
    float horizontalSpeed() const;
    void setHorizontalSpeed(float newHorizontalSpeed);

    // 垂直速度
    float vertialSpeed() const;
    void setVertialSpeed(float newVertialSpeed);

    void setLeftRotateKeyCode(Qt::Key keyCode);
    void setRightRotateKeyCode(Qt::Key keyCode);

    void setUpRotateKeyCode(Qt::Key keyCode);
    void setDownRotateKeyCode(Qt::Key keyCode);

    void setRotateKeyCode(Qt::Key leftRotateKeyCode, Qt::Key rightRotateKeyCode,
                          Qt::Key upRotateKeyCode, Qt::Key downRotateKeyCode);

private slots:
    // 帧刷新槽函数
    void onFrameFllushSlot(float deltaTime);
};

#endif // WASDROTATECONTROLLER_H
