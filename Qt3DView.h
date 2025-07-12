#ifndef QT3DVIEW_H
#define QT3DVIEW_H
#include <QWidget>
#include <QKeyEvent>
#include <QVector3D> // 添加QVector3D头文件

namespace  Qt3DCore{
class QEntity;
}
namespace Qt3DExtras {
class Qt3DWindow;
class QOrbitCameraController;
}
namespace Qt3DRender {
class QCamera;
}

class Qt3DView : public QWidget
{
    Q_OBJECT
public:
    // 视图类型枚举
    enum ViewType {
        PerspectiveView,  // 透视图
        TopView,          // 顶视图
        FrontView,        // 前视图
        LeftView          // 左视图
    };

    explicit Qt3DView(Qt3DCore::QEntity* root, QWidget* parent = nullptr);
    ~Qt3DView();

    Qt3DRender::QCamera* camera() const;
    Qt3DExtras::QOrbitCameraController* cameraController() const;
    
    // 切换到指定视图类型
    void switchToView(ViewType viewType);
    
    // 自动适应视图，使模型完全可见
    void fitToView();

protected:
    // 事件处理函数
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

private:
    // 视图状态结构
    struct ViewState {
        QVector3D position;
        QVector3D viewCenter;
        QVector3D upVector;
    };
    
    // 视图状态管理
    void saveCurrentView();
    void restoreView(ViewType viewType);
    
    // 边界计算方法
    bool calculateSceneBounds(QVector3D& minBounds, QVector3D& maxBounds);
    bool calculateEntityBounds(Qt3DCore::QEntity* entity, QVector3D& minBounds, QVector3D& maxBounds);

    // 成员变量
    Qt3DExtras::Qt3DWindow* m_3dWindow;
    Qt3DCore::QEntity* m_rootEntity;
    Qt3DExtras::QOrbitCameraController* m_cameraController;
    
    // 视图状态
    ViewType m_currentViewType;
    ViewState m_perspectiveViewState;
    ViewState m_topViewState;
    ViewState m_frontViewState;
    ViewState m_leftViewState;
};

#endif // QT3DVIEW_H
