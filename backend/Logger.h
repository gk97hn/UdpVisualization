#ifndef LOGGER_H
#define LOGGER_H

#include <QObject>
#include <QFile>
#include <QMutex>

class Logger : public QObject
{
    Q_OBJECT
public:
    static Logger& instance();
    void log(const QString &message, const QString &level = "INFO");

    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

private:
    Logger();
    ~Logger();

    QFile m_logFile;
    QMutex m_mutex;
};

#endif // LOGGER_H