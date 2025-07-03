#include "AppWindow.h"
#include "Logger.h"

#include <QApplication>
#include <QDebug>

// Custom message handler to capture qDebug output
void customMessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    // Map Qt message type to Logger level
    Logger::LogLevel level;
    switch (type) {
    case QtDebugMsg:
        level = Logger::Debug;
        break;
    case QtInfoMsg:
        level = Logger::Info;
        break;
    case QtWarningMsg:
        level = Logger::Warning;
        break;
    case QtCriticalMsg:
        level = Logger::Critical;
        break;
    case QtFatalMsg:
        level = Logger::Fatal;
        break;
    }
    
    // Log message using Logger
    Logger::instance().log(level, msg);
    
    // If fatal error, terminate application
    if (type == QtFatalMsg) {
        abort();
    }
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
    // Initialize logger
    Logger::instance().setLogToFile(true, "application.log");
    
    // Install custom message handler
    qInstallMessageHandler(customMessageHandler);
    
    // Create main window
    AppWindow w;
    w.show();
    
    // Output application startup information
    qDebug() << "Application started";
    
    return a.exec();
} 