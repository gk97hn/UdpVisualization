#ifndef UDPHANDLER_H
#define UDPHANDLER_H

#include <QObject>
#include <QUdpSocket>
#include <QNetworkInterface>
#include <QList>
#include "Logger.h"
#include "models/UdpSocketModel.h"

class UdpHandler : public QObject
{
    Q_OBJECT
public:
    enum Mode { Listener, Publisher };
    
    explicit UdpHandler(QObject *parent = nullptr);
    void refreshAvailableSockets();
    void setupConnection(const QString &address, quint16 port, Mode mode);
    void sendMessage(const QString &message);

signals:
    void socketsUpdated(const QList<UdpSocketModel*> &sockets);
    void messageReceived(const QString &message);
    void connectionStatusChanged(bool connected);
    void publisherStatusChanged(bool active);
    void errorOccurred(const QString &error);

private slots:
    void onReadyRead();

private:
    QUdpSocket *m_udpSocket;
    Mode m_currentMode;
    QList<UdpSocketModel*> m_availableSockets;
    Logger &m_logger;
};

#endif // UDPHANDLER_H
