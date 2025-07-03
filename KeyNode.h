#ifndef KEYNODE_H
#define KEYNODE_H

#include <Qt3DCore/QNode>

namespace Qt3DInput {
class QKeyboardHandler;
class QKeyboardDevice;
class QLogicalDevice;
class QAction;
class QActionInput;
}

class KeyNode : public Qt3DCore::QNode
{
    Q_OBJECT
public:
    KeyNode(int key, Qt3DInput::QKeyboardDevice* keyboardDevice, Qt3DInput::QLogicalDevice* logicalDevice, QNode* parent = nullptr);
    ~KeyNode();

    // 是否按下
    bool isPressed() const;

    // 设置按键
    void setKeyCode(Qt::Key key);

    // 获取按键节点
    Qt3DInput::QAction* keyNode() const;

private slots:
    void onKeyActiveChanged(bool isActive);

private:
    int m_key = 0;
    bool m_isPressed = false;
    Qt3DInput::QKeyboardDevice* m_keyboardDevice = nullptr;
    Qt3DInput::QLogicalDevice* m_logicalDevice = nullptr;
    Qt3DInput::QKeyboardHandler* m_keyboardHandler = nullptr;
    Qt3DInput::QAction* m_keyAction = nullptr;
    Qt3DInput::QActionInput* m_keyInput = nullptr;
};

#endif // KEYNODE_H
