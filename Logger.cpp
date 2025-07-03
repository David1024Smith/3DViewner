#include "Logger.h"
#include <QDateTime>
#include <QDebug>

Logger::Logger()
    : m_logLevel(Debug), m_logToFile(false)
{
}

Logger::~Logger()
{
    if (m_logFile.isOpen()) {
        m_logFile.close();
    }
}

Logger& Logger::instance()
{
    static Logger instance;
    return instance;
}

void Logger::setLogLevel(LogLevel level)
{
    QMutexLocker locker(&m_mutex);
    m_logLevel = level;
}

void Logger::setLogToFile(bool enabled, const QString& filePath)
{
    QMutexLocker locker(&m_mutex);
    
    if (m_logFile.isOpen()) {
        m_logStream.setDevice(nullptr);
        m_logFile.close();
    }
    
    m_logToFile = enabled;
    
    if (enabled) {
        m_logFile.setFileName(filePath);
        if (m_logFile.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
            m_logStream.setDevice(&m_logFile);
        } else {
            qDebug() << "Failed to open log file:" << filePath;
            m_logToFile = false;
        }
    }
}

void Logger::debug(const QString& message)
{
    log(Debug, message);
}

void Logger::info(const QString& message)
{
    log(Info, message);
}

void Logger::warning(const QString& message)
{
    log(Warning, message);
}

void Logger::critical(const QString& message)
{
    log(Critical, message);
}

void Logger::fatal(const QString& message)
{
    log(Fatal, message);
}

void Logger::log(LogLevel level, const QString& message)
{
    if (level < m_logLevel) {
        return;
    }
    
    QMutexLocker locker(&m_mutex);
    
    QString timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz");
    QString logMessage = QString("[%1] [%2] %3")
                            .arg(timestamp)
                            .arg(levelToString(level))
                            .arg(message);
    
    // Output to console
    QTextStream(stdout) << logMessage << Qt::endl;
    
    // Output to file if enabled
    if (m_logToFile && m_logFile.isOpen()) {
        m_logStream << logMessage << Qt::endl;
        m_logStream.flush();
    }
}

QString Logger::levelToString(LogLevel level)
{
    switch (level) {
    case Debug:
        return "DEBUG";
    case Info:
        return "INFO";
    case Warning:
        return "WARNING";
    case Critical:
        return "CRITICAL";
    case Fatal:
        return "FATAL";
    default:
        return "UNKNOWN";
    }
} 