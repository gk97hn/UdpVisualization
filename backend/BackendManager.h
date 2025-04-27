#ifndef BACKENDMANAGER_H
#define BACKENDMANAGER_H

#include <QObject>
#include "XmlParser.h"
#include "UdpHandler.h"
#include "SocketCanHandler.h"

class BackendManager : public QObject
{
    Q_OBJECT
public:
    explicit BackendManager(QObject *parent = nullptr);
    ~BackendManager();

    Q_INVOKABLE void loadXmlFile(const QString &filePath);
    Q_INVOKABLE void refreshUdpSockets();
    Q_INVOKABLE void connectToUdp(const QString &address, quint16 port, bool asPublisher);
    Q_INVOKABLE void sendUdpMessage(const QString &message);
    Q_INVOKABLE void setupCanInterface(const QString &interface, int baudrate);
    Q_INVOKABLE void sendCanMessage(const QByteArray &message);
    Q_INVOKABLE QStringList getCanInterfaces();
signals:
    void shapesUpdated(const QVariantList &shapes);
    void udpSocketsUpdated(const QVariantList &sockets);
    void udpMessagesReceived(const QString &message);
    void errorOccurred(const QString &error);
    void connectionStatusChanged(bool connected);
    void publisherStatusChanged(bool active);
    void canInterfacesUpdated(const QVariantList &interfaces);
    void canMessageReceived(const QString &message);

private:
    XmlParser *m_xmlParser;
    UdpHandler *m_udpHandler;
    SocketCanHandler *m_canHandler;
    Logger &m_logger;
};

#endif // BACKENDMANAGER_H
