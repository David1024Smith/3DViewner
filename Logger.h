#ifndef LOGGER_H
#define LOGGER_H

#include <QString>
#include <QFile>
#include <QTextStream>
#include <QMutex>

class Logger
{
public:
    enum LogLevel {
        Debug,
        Info,
        Warning,
        Critical,
        Fatal
    };

    static Logger& instance();

    void setLogLevel(LogLevel level);
    void setLogToFile(bool enabled, const QString& filePath = "application.log");

    void debug(const QString& message);
    void info(const QString& message);
    void warning(const QString& message);
    void critical(const QString& message);
    void fatal(const QString& message);

    void log(LogLevel level, const QString& message);

private:
    Logger();
    ~Logger();
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    LogLevel m_logLevel;
    bool m_logToFile;
    QFile m_logFile;
    QTextStream m_logStream;
    QMutex m_mutex;

    QString levelToString(LogLevel level);
};

#endif // LOGGER_H 