#include "KeyNode.h"
#include <Qt3DInput/QKeyboardHandler>
#include <Qt3DInput/QAxis>
#include <Qt3DInput/QAction>
#include <Qt3DInput/QActionInput>
#include <Qt3DInput/QLogicalDevice>
#include <Qt3DInput/QKeyboardDevice>
#include <QDebug>

KeyNode::KeyNode(int key, Qt3DInput::QKeyboardDevice *keyboardDevice, Qt3DInput::QLogicalDevice *logicalDevice, QNode *parent)
    : Qt3DCore::QNode(parent)
    , m_key(key)
    , m_keyboardDevice(keyboardDevice)
    , m_logicalDevice(logicalDevice)
{
    // 键盘事件处理器
    m_keyboardHandler = new Qt3DInput::QKeyboardHandler(parent);
    m_keyboardHandler->setSourceDevice(keyboardDevice);

    // 按键检测
    m_keyAction = new Qt3DInput::QAction(parent);
    m_keyInput = new Qt3DInput::QActionInput(parent);
    m_keyInput->setButtons(QVector<int>() << key);
    m_keyInput->setSourceDevice(keyboardDevice);
    m_keyAction->addInput(m_keyInput);
    m_logicalDevice->addAction(m_keyAction);

    connect(m_keyAction, &Qt3DInput::QAction::activeChanged, this, &KeyNode::onKeyActiveChanged);
}

KeyNode::~KeyNode()
{
}

bool KeyNode::isPressed() const
{
    return m_isPressed;
}

void KeyNode::setKeyCode(Qt::Key key)
{
    m_key = key;
    m_keyInput->setButtons(QVector<int>() << key);
}

void KeyNode::onKeyActiveChanged(bool isActive)
{
    m_isPressed = isActive;
}

Qt3DInput::QAction *KeyNode::keyNode() const
{
    return m_keyAction;
}
