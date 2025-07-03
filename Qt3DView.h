#ifndef QT3DVIEW_H
#define QT3DVIEW_H
#include <QWidget>
namespace  Qt3DCore{
class QEntity;
}
namespace Qt3DExtras {
class Qt3DWindow;
}
namespace Qt3DRender {
class QCamera;
}

class Qt3DView : public QWidget
{
public:
    explicit Qt3DView(Qt3DCore::QEntity* root,QWidget* parent = nullptr);
    ~Qt3DView();

    Qt3DRender::QCamera* camera() const;

private:
    Qt3DCore::QEntity *m_rootEntity;
    Qt3DExtras::Qt3DWindow* m_3dWindow;
};

#endif // QT3DVIEW_H
