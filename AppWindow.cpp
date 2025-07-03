#include "AppWindow.h"
#include "Qt3DView.h"
#include "MeshEntity.h"
#include "PointLightEntity.h"
#include "WASDTranslateController.h"
#include "WASDRotateController.h"
#include "Logger.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMenuBar>
#include <QStatusBar>
#include <QFileDialog>
#include <QMessageBox>
#include <QDockWidget>
#include <QPlainTextEdit>
#include <QScrollBar>
#include <QDateTime>
#include <QFileInfo>
#include <QMimeData>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QDebug>
#include <QFile>
#include <QApplication>
#include <QScreen>

AppWindow::AppWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // Enable drag and drop
    setAcceptDrops(true);
    
    // Create central widget
    centralwidget = new QWidget(this);
    setCentralWidget(centralwidget);

    // Create layout
    layout = new QHBoxLayout(centralwidget);

    // Create root entity first
    Qt3DCore::QEntity* rootEntity = new Qt3DCore::QEntity();
    m_rootEntity = rootEntity;

    // Create 3D view with root entity
    m_view = new Qt3DView(rootEntity);
    layout->addWidget(m_view);

    // Create mesh entity
    MeshEntity* rightMeshEntity = new MeshEntity(rootEntity);
    rightMeshEntity->setSourceUrl(QUrl::fromLocalFile("Qt3DModel/FinalBaseMesh.obj"));
    m_currentMeshEntity = rightMeshEntity;

    // Create point light entity
    pointLightEntity = new PointLightEntity(rootEntity);

    // Create menus
    createMenus();
    
    // Create WASD rotate controller
    WASDRotateController* rotateController = new WASDRotateController(rootEntity);
    rotateController->bindEntity(rightMeshEntity);
    
    // Set window size to half of screen size and center it
    QScreen* screen = QApplication::primaryScreen();
    if (screen) {
        QRect screenGeometry = screen->geometry();
        int windowWidth = screenGeometry.width() / 2;
        int windowHeight = screenGeometry.height() / 2;
        
        // Resize window
        resize(windowWidth, windowHeight);
        
        // Center window on screen
        int x = (screenGeometry.width() - windowWidth) / 2;
        int y = (screenGeometry.height() - windowHeight) / 2;
        move(x, y);
        
        Logger::instance().info(QString("Window size set to %1x%2, centered on screen").arg(windowWidth).arg(windowHeight));
    }
    
    // Output initialization completion information
    Logger::instance().info("Application initialized successfully");
}

AppWindow::~AppWindow()
{
}

void AppWindow::createMenus()
{
    // Create menu bar
    QMenuBar* menuBar = this->menuBar();
    
    // Add file menu
    QMenu* fileMenu = menuBar->addMenu(tr("File"));
    
    // Add open file action
    QAction* openAction = new QAction(tr("Open Model..."), this);
    fileMenu->addAction(openAction);
    connect(openAction, &QAction::triggered, this, &AppWindow::openFile);
    
    setStatusBar(new QStatusBar(this));
}

void AppWindow::openFile()
{
    // Open file dialog to select 3D model file
    QString filePath = QFileDialog::getOpenFileName(
        this,
        tr("Open 3D Model"),
        QString(),
        tr("3D Model Files (*.obj *.fbx *.dae *.gltf *.glb *.stl *.3ds *.ply);;All Files (*)")
    );
    
    // If user cancels selection, filePath is empty
    if (filePath.isEmpty()) {
        return;
    }
    
    // Load model
    loadModelFromFile(filePath);
}

void AppWindow::dragEnterEvent(QDragEnterEvent* event)
{
    // Debug output
    qDebug() << "Drag enter event triggered";
    
    // Check if drag data contains URLs
    if (event->mimeData()->hasUrls()) {
        qDebug() << "Drag data contains URLs";
        
        // Get first URL
        QUrl url = event->mimeData()->urls().first();
        qDebug() << "Drag URL: " << url.toString();
        
        // Check if URL is a local file
        if (url.isLocalFile()) {
            QString filePath = url.toLocalFile();
            qDebug() << "Local file path: " << filePath;
            
            // Check if file is a supported 3D model format
            if (isSupportedModelFile(filePath)) {
                // Accept drag event
                qDebug() << "Accept drag: File type supported";
                event->acceptProposedAction();
                
                // Update status bar
                statusBar()->showMessage(tr("Ready to drop: %1").arg(QFileInfo(filePath).fileName()), 3000);
                return;
            } else {
                qDebug() << "Reject drag: Unsupported file type";
                statusBar()->showMessage(tr("Unsupported file type"), 3000);
            }
        } else {
            qDebug() << "Reject drag: Not a local file";
            statusBar()->showMessage(tr("Please drop local files"), 3000);
        }
    } else {
        qDebug() << "Reject drag: No URL data";
        statusBar()->showMessage(tr("Please drop files"), 3000);
    }
    
    // If not a supported file type, reject drag event
    event->ignore();
}

void AppWindow::dropEvent(QDropEvent* event)
{
    // Debug output
    qDebug() << "Drop event triggered";
    
    // Get drop URLs
    const QMimeData* mimeData = event->mimeData();
    
    // Ensure there are URLs
    if (mimeData->hasUrls()) {
        qDebug() << "Drop data contains URLs";
        
        // Get first URL
        QUrl url = mimeData->urls().first();
        qDebug() << "Drop URL: " << url.toString();
        
        // Check if URL is a local file
        if (url.isLocalFile()) {
            // Get local file path
            QString filePath = url.toLocalFile();
            qDebug() << "Local file path: " << filePath;
            
            // Load model
            if (loadModelFromFile(filePath)) {
                // Accept drop event
                qDebug() << "Model loaded successfully";
                event->acceptProposedAction();
                return;
            } else {
                qDebug() << "Failed to load model";
                statusBar()->showMessage(tr("Failed to load model: %1").arg(QFileInfo(filePath).fileName()), 5000);
            }
        } else {
            qDebug() << "Not a local file";
            statusBar()->showMessage(tr("Please drop local files"), 3000);
        }
    } else {
        qDebug() << "Drop data does not contain URLs";
        statusBar()->showMessage(tr("Please drop files"), 3000);
    }
    
    // If loading fails, ignore event
    event->ignore();
}

bool AppWindow::loadModelFromFile(const QString& filePath)
{
    // Debug output
    qDebug() << "Attempting to load model: " << filePath;
    
    // Check if file exists
    QFileInfo fileInfo(filePath);
    if (!fileInfo.exists()) {
        qDebug() << "File does not exist: " << filePath;
        QMessageBox::warning(this, tr("File Error"), tr("File does not exist: %1").arg(filePath));
        return false;
    }
    
    // Check if file is readable
    if (!fileInfo.isReadable()) {
        qDebug() << "File is not readable: " << filePath;
        QMessageBox::warning(this, tr("File Error"), tr("File is not readable: %1").arg(filePath));
        return false;
    }
    
    // Check if file is a supported 3D model format
    if (!isSupportedModelFile(filePath)) {
        qDebug() << "Unsupported file format: " << filePath;
        QMessageBox::warning(this, tr("Format Error"), tr("Unsupported file format: %1\nSupported formats: obj, fbx, dae, gltf, glb, stl, 3ds, ply").arg(fileInfo.suffix()));
        return false;
    }
    
    // Convert file path to QUrl
    QUrl fileUrl = QUrl::fromLocalFile(filePath);
    qDebug() << "File URL: " << fileUrl.toString();
    
    // Check if current model entity exists
    if (m_currentMeshEntity) {
        // Update current model source URL
        m_currentMeshEntity->setSourceUrl(fileUrl);
        qDebug() << "Updated existing model source URL";
    } else {
        // Create new mesh entity
        m_currentMeshEntity = new MeshEntity(m_rootEntity);
        m_currentMeshEntity->setSourceUrl(fileUrl);
        qDebug() << "Created new mesh entity";
    }
    
    // Update status bar
    statusBar()->showMessage(tr("Model loaded: %1").arg(fileInfo.fileName()), 5000);
    Logger::instance().info(QString("Model loaded: %1").arg(filePath));
    
    return true;
}

bool AppWindow::isSupportedModelFile(const QString& filePath)
{
    QFileInfo fileInfo(filePath);
    QString suffix = fileInfo.suffix().toLower();
    
    // List of supported 3D model formats
    QStringList supportedFormats = {
        "obj", "fbx", "dae", "gltf", "glb", "stl", "3ds", "ply"
    };
    
    return supportedFormats.contains(suffix);
} 