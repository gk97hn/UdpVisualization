#ifndef SOCKETCANHANDLER_H
#define SOCKETCANHANDLER_H

#include <QObject>
#include <QCanBus>
#include "Logger.h"

class SocketCanHandler : public QObject
{
    Q_OBJECT

    public:
    Q_INVOKABLE QStringList availableCanInterfaces() const;
    explicit SocketCanHandler(QObject *parent = nullptr);
    void refreshCanInterfaces();
    void setupCanInterface(const QString &interface, int baudrate);
    void sendCanMessage(const QByteArray &message);

signals:
    void interfacesUpdated(const QStringList &interfaces);
    void messageReceived(const QString &message);
    void errorOccurred(const QString &error);

private slots:
    void onCanFrameReceived();

private:
    QCanBusDevice *m_canDevice;
    QStringList m_availableInterfaces;
    Logger &m_logger;
};

#endif // SOCKETCANHANDLER_H
