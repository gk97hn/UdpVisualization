#include "Logger.h"
#include <QDateTime>
#include <QDir>

Logger& Logger::instance()
{
    static Logger instance;
    return instance;
}

Logger::Logger()
{
    QString logPath = QDir::currentPath() + "/application.log";
    m_logFile.setFileName(logPath);
    
    if (!m_logFile.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
        qWarning() << "Failed to open log file:" << logPath;
    }
}

Logger::~Logger()
{
    if (m_logFile.isOpen()) {
        m_logFile.close();
    }
}

void Logger::log(const QString &message, const QString &level)
{
    QMutexLocker locker(&m_mutex);
    
    if (!m_logFile.isOpen()) return;
    
    QString timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz");
    QString logMessage = QString("%1 [%2]: %3\n").arg(timestamp, level, message);
    
    m_logFile.write(logMessage.toUtf8());
    m_logFile.flush();

    qDebug() << logMessage.trimmed();
}
