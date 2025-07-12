#ifndef APPWINDOW_H
#define APPWINDOW_H

#include <QMainWindow>
#include <QUrl>
#include <QString>
#include <QKeyEvent>

namespace Qt3DCore {
    class QEntity;
}

class QWidget;
class QHBoxLayout;
class QVBoxLayout;
class MeshEntity;
class PointLightEntity;
class Qt3DView;

class AppWindow : public QMainWindow
{
    Q_OBJECT

public:
    AppWindow(QWidget *parent = nullptr);
    ~AppWindow();

protected:
    // Drag and drop event handling
    void dragEnterEvent(QDragEnterEvent* event) override;
    void dropEvent(QDropEvent* event) override;
    
    // 键盘事件处理
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

private slots:
    void openFile();

private:
    void createMenus();
    bool isSupportedModelFile(const QString& filePath);
    bool loadModelFromFile(const QString& filePath);

    QWidget *centralwidget;
    QHBoxLayout *layout;
    Qt3DCore::QEntity* m_rootEntity = nullptr;
    MeshEntity* m_currentMeshEntity = nullptr;
    PointLightEntity* pointLightEntity = nullptr;

    Qt3DView* m_view = nullptr;
};
#endif // APPWINDOW_H 