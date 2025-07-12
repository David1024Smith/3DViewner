#include "Qt3DView.h"
#include <Qt3DExtras/Qt3DWindow>
#include <Qt3DExtras/QForwardRenderer>
#include <Qt3DExtras/QOrbitCameraController>
#include <QHBoxLayout>
#include <QScreen>
#include <Qt3DCore/QEntity>
#include <Qt3DRender/QCamera>
#include <QVector3D>
#include <QQuaternion>
#include <QMatrix4x4>
#include <Qt3DRender/QCameraLens>
#include <Qt3DCore/QTransform>
#include <Qt3DRender/QMesh>
#include <Qt3DRender/QGeometryRenderer>
#include <Qt3DCore/QComponent>
#include <QDebug>
#include "Logger.h"

Qt3DView::Qt3DView(Qt3DCore::QEntity *root, QWidget *parent)
    : QWidget(parent)
    , m_rootEntity(root)
{
    m_3dWindow = new Qt3DExtras::Qt3DWindow();
    m_3dWindow->setRootEntity(root);
    m_3dWindow->defaultFrameGraph()->setClearColor(Qt::white);

    QSize screenSize = m_3dWindow->screen()->size();
    QWidget *container = QWidget::createWindowContainer(m_3dWindow);
    container->setMaximumSize(screenSize);

    QHBoxLayout* layout = new QHBoxLayout(this);
    layout->addWidget(container);
    layout->setContentsMargins(0, 0, 0, 0);

    // 设置焦点策略，确保能接收键盘事件
    setFocusPolicy(Qt::StrongFocus);
    container->setFocusPolicy(Qt::StrongFocus);
    
    // 初始化成员变量
    m_currentViewType = PerspectiveView;
    
    // 设置相机初始位置
    Qt3DRender::QCamera* camera = m_3dWindow->camera();
    camera->lens()->setPerspectiveProjection(45.0f, 16.0f/9.0f, 0.1f, 1000.0f);
    camera->setPosition(QVector3D(0, 0, 10));
    camera->setUpVector(QVector3D(0, 1, 0));
    camera->setViewCenter(QVector3D(0, 0, 0));
    
    // 创建轨道相机控制器
    m_cameraController = new Qt3DExtras::QOrbitCameraController(root);
    m_cameraController->setCamera(camera);
    
    // 初始化视图状态
    m_perspectiveViewState.position = QVector3D(0, 0, 10);
    m_perspectiveViewState.viewCenter = QVector3D(0, 0, 0);
    m_perspectiveViewState.upVector = QVector3D(0, 1, 0);
    
    m_topViewState.position = QVector3D(0, 10, 0);
    m_topViewState.viewCenter = QVector3D(0, 0, 0);
    m_topViewState.upVector = QVector3D(0, 0, -1);
    
    m_frontViewState.position = QVector3D(0, 0, 10);
    m_frontViewState.viewCenter = QVector3D(0, 0, 0);
    m_frontViewState.upVector = QVector3D(0, 1, 0);
    
    m_leftViewState.position = QVector3D(-10, 0, 0);
    m_leftViewState.viewCenter = QVector3D(0, 0, 0);
    m_leftViewState.upVector = QVector3D(0, 1, 0);
    
    // 设置初始视图为透视图
    switchToView(PerspectiveView);
    
    qDebug() << "Qt3DView initialized with QOrbitCameraController";
    Logger::instance().info("Qt3DView initialized with orbit camera controller");
}

Qt3DView::~Qt3DView()
{
}

Qt3DRender::QCamera *Qt3DView::camera() const
{
    return m_3dWindow->camera();
}

Qt3DExtras::QOrbitCameraController *Qt3DView::cameraController() const
{
    return m_cameraController;
}

void Qt3DView::fitToView()
{
    // 计算场景边界框
    QVector3D minBounds, maxBounds;
    if (calculateSceneBounds(minBounds, maxBounds)) {
        // 计算模型中心和大小
        QVector3D center = (minBounds + maxBounds) * 0.5f;
        QVector3D size = maxBounds - minBounds;
        float maxDimension = qMax(qMax(size.x(), size.y()), size.z());
        
        // 计算合适的相机距离
        float distance = maxDimension * 2.0f; // 给模型留一些边距
        distance = qMax(distance, 1.0f); // 确保最小距离
        
        Qt3DRender::QCamera* camera = m_3dWindow->camera();
        
        // 根据当前视图类型设置相机位置
        switch (m_currentViewType) {
        case PerspectiveView:
            camera->setPosition(center + QVector3D(0, 0, distance));
            camera->setViewCenter(center);
            camera->setUpVector(QVector3D(0, 1, 0));
            break;
        case TopView:
            camera->setPosition(center + QVector3D(0, distance, 0));
            camera->setViewCenter(center);
            camera->setUpVector(QVector3D(0, 0, -1));
            break;
        case FrontView:
            camera->setPosition(center + QVector3D(0, 0, distance));
            camera->setViewCenter(center);
            camera->setUpVector(QVector3D(0, 1, 0));
            break;
        case LeftView:
            camera->setPosition(center + QVector3D(-distance, 0, 0));
            camera->setViewCenter(center);
            camera->setUpVector(QVector3D(0, 1, 0));
            break;
        }
        
        // 更新当前视图状态
        saveCurrentView();
        
        qDebug() << "Fit to view - Center:" << center << "Size:" << size << "Distance:" << distance;
        Logger::instance().info(QString("自动适应视图 - 中心: (%1, %2, %3), 大小: %4")
                               .arg(center.x()).arg(center.y()).arg(center.z()).arg(maxDimension));
    } else {
        qDebug() << "Could not calculate scene bounds for fit to view";
        Logger::instance().warning("无法计算场景边界，使用默认视图");
    }
}

bool Qt3DView::calculateSceneBounds(QVector3D &minBounds, QVector3D &maxBounds)
{
    // 初始化边界
    minBounds = QVector3D(1000000, 1000000, 1000000);
    maxBounds = QVector3D(-1000000, -1000000, -1000000);
    bool foundBounds = false;
    
    // 递归遍历场景中的所有实体
    if (m_rootEntity) {
        foundBounds = calculateEntityBounds(m_rootEntity, minBounds, maxBounds);
    }
    
    // 如果没有找到边界，使用默认值
    if (!foundBounds) {
        minBounds = QVector3D(-1, -1, -1);
        maxBounds = QVector3D(1, 1, 1);
        foundBounds = true;
    }
    
    return foundBounds;
}

bool Qt3DView::calculateEntityBounds(Qt3DCore::QEntity *entity, QVector3D &minBounds, QVector3D &maxBounds)
{
    if (!entity) return false;
    
    bool foundBounds = false;
    
    // 查找几何渲染器组件
    auto geometryRenderers = entity->componentsOfType<Qt3DRender::QGeometryRenderer>();
    if (!geometryRenderers.isEmpty()) {
        // 获取变换组件
        Qt3DCore::QTransform* transform = nullptr;
        auto transforms = entity->componentsOfType<Qt3DCore::QTransform>();
        if (!transforms.isEmpty()) {
            transform = transforms.first();
        }
        
        // 对于每个几何渲染器，计算其边界
        for (auto renderer : geometryRenderers) {
            // 这里简化处理，使用一个估算的边界框
            // 在实际应用中，可能需要更复杂的几何分析
            QVector3D localMin(-1, -1, -1);
            QVector3D localMax(1, 1, 1);
            
            // 如果有变换，应用变换
            if (transform) {
                QMatrix4x4 matrix = transform->matrix();
                
                // 变换边界框的8个顶点
                QVector3D vertices[8] = {
                    QVector3D(localMin.x(), localMin.y(), localMin.z()),
                    QVector3D(localMax.x(), localMin.y(), localMin.z()),
                    QVector3D(localMin.x(), localMax.y(), localMin.z()),
                    QVector3D(localMax.x(), localMax.y(), localMin.z()),
                    QVector3D(localMin.x(), localMin.y(), localMax.z()),
                    QVector3D(localMax.x(), localMin.y(), localMax.z()),
                    QVector3D(localMin.x(), localMax.y(), localMax.z()),
                    QVector3D(localMax.x(), localMax.y(), localMax.z())
                };
                
                for (int i = 0; i < 8; ++i) {
                    QVector3D transformedVertex = matrix.map(vertices[i]);
                    minBounds.setX(qMin(minBounds.x(), transformedVertex.x()));
                    minBounds.setY(qMin(minBounds.y(), transformedVertex.y()));
                    minBounds.setZ(qMin(minBounds.z(), transformedVertex.z()));
                    maxBounds.setX(qMax(maxBounds.x(), transformedVertex.x()));
                    maxBounds.setY(qMax(maxBounds.y(), transformedVertex.y()));
                    maxBounds.setZ(qMax(maxBounds.z(), transformedVertex.z()));
                }
            } else {
                // 没有变换，直接使用本地边界
                minBounds.setX(qMin(minBounds.x(), localMin.x()));
                minBounds.setY(qMin(minBounds.y(), localMin.y()));
                minBounds.setZ(qMin(minBounds.z(), localMin.z()));
                maxBounds.setX(qMax(maxBounds.x(), localMax.x()));
                maxBounds.setY(qMax(maxBounds.y(), localMax.y()));
                maxBounds.setZ(qMax(maxBounds.z(), localMax.z()));
            }
            
            foundBounds = true;
        }
    }
    
    // 递归处理子实体
    for (auto child : entity->childNodes()) {
        Qt3DCore::QEntity* childEntity = qobject_cast<Qt3DCore::QEntity*>(child);
        if (childEntity) {
            if (calculateEntityBounds(childEntity, minBounds, maxBounds)) {
                foundBounds = true;
            }
        }
    }
    
    return foundBounds;
}

void Qt3DView::switchToView(ViewType viewType)
{
    // 保存当前视图状态
    saveCurrentView();
    
    // 切换到新视图
    m_currentViewType = viewType;
    restoreView(viewType);
    
    // 记录日志
    QString viewName;
    switch (viewType) {
    case PerspectiveView:
        viewName = "透视图";
        break;
    case TopView:
        viewName = "顶视图";
        break;
    case FrontView:
        viewName = "前视图";
        break;
    case LeftView:
        viewName = "左视图";
        break;
    }
    
    qDebug() << "Switching to view:" << viewName;
    Logger::instance().info(QString("切换到%1").arg(viewName));
}

// 鼠标事件现在由QOrbitCameraController处理

void Qt3DView::keyPressEvent(QKeyEvent *event)
{
    qDebug() << "Key press event, key:" << event->key() << "text:" << event->text();
    // 处理视图切换快捷键
    switch (event->key()) {
    case Qt::Key_T:
        qDebug() << "T key pressed - switching to top view";
        switchToView(TopView);
        break;
    case Qt::Key_F:
        qDebug() << "F key pressed - switching to front view";
        switchToView(FrontView);
        break;
    case Qt::Key_L:
        qDebug() << "L key pressed - switching to left view";
        switchToView(LeftView);
        break;
    case Qt::Key_P:
        qDebug() << "P key pressed - switching to perspective view";
        switchToView(PerspectiveView);
        break;
    case Qt::Key_Home:
        qDebug() << "Home key pressed - fitting to view";
        fitToView();
        break;
    default:
        QWidget::keyPressEvent(event);
        break;
    }
}

void Qt3DView::keyReleaseEvent(QKeyEvent *event)
{
    qDebug() << "Key release event, key:" << event->key();
    QWidget::keyReleaseEvent(event);
}


void Qt3DView::saveCurrentView()
{
    Qt3DRender::QCamera* camera = m_3dWindow->camera();
    
    // 保存当前视图状态
    ViewState* currentState = nullptr;
    
    switch (m_currentViewType) {
    case PerspectiveView:
        currentState = &m_perspectiveViewState;
        break;
    case TopView:
        currentState = &m_topViewState;
        break;
    case FrontView:
        currentState = &m_frontViewState;
        break;
    case LeftView:
        currentState = &m_leftViewState;
        break;
    }
    
    if (currentState) {
        currentState->position = camera->position();
        currentState->viewCenter = camera->viewCenter();
        currentState->upVector = camera->upVector();
    }
}

void Qt3DView::restoreView(ViewType viewType)
{
    Qt3DRender::QCamera* camera = m_3dWindow->camera();
    
    ViewState* newState = nullptr;
    
    switch (viewType) {
    case PerspectiveView:
        newState = &m_perspectiveViewState;
        camera->lens()->setPerspectiveProjection(45.0f, width() / static_cast<float>(height()), 0.1f, 1000.0f);
        break;
    case TopView:
        newState = &m_topViewState;
        camera->lens()->setOrthographicProjection(-5.0f, 5.0f, -5.0f, 5.0f, 0.1f, 1000.0f);
        break;
    case FrontView:
        newState = &m_frontViewState;
        camera->lens()->setOrthographicProjection(-5.0f, 5.0f, -5.0f, 5.0f, 0.1f, 1000.0f);
        break;
    case LeftView:
        newState = &m_leftViewState;
        camera->lens()->setOrthographicProjection(-5.0f, 5.0f, -5.0f, 5.0f, 0.1f, 1000.0f);
        break;
    }
    
    if (newState) {
        camera->setPosition(newState->position);
        camera->setViewCenter(newState->viewCenter);
        camera->setUpVector(newState->upVector);
    }
}
