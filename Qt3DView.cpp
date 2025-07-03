#include "Qt3DView.h"
#include <Qt3DWindow>
#include <QForwardRenderer>
#include <QHBoxLayout>
#include <QScreen>
#include <QEntity>

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
     layout->setContentsMargins(0,0,0,0);
}

Qt3DView::~Qt3DView()
{
    delete m_rootEntity;
    delete m_3dWindow;
}

Qt3DRender::QCamera *Qt3DView::camera() const
{
    return m_3dWindow->camera();
}
