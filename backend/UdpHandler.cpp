#include "UdpHandler.h"
#include <QNetworkDatagram>
#include <QTimer>

UdpHandler::UdpHandler(QObject *parent) : QObject(parent), 
    m_udpSocket(new QUdpSocket(this)),
    m_logger(Logger::instance())
{
    connect(m_udpSocket, &QUdpSocket::readyRead, this, &UdpHandler::onReadyRead);
    refreshAvailableSockets();
}

void UdpHandler::refreshAvailableSockets()
{
    m_availableSockets.clear();
    
    QList<QNetworkInterface> interfaces = QNetworkInterface::allInterfaces();
    for (const QNetworkInterface &interface : interfaces)
    {
        if (interface.flags() & QNetworkInterface::IsUp && !(interface.flags() & QNetworkInterface::IsLoopBack))
        {
            QList<QNetworkAddressEntry> entries = interface.addressEntries();
            for (const QNetworkAddressEntry &entry : entries)
            {
                if (entry.ip().protocol() == QAbstractSocket::IPv4Protocol)
                {
                    UdpSocketModel *socket = new UdpSocketModel(
                        entry.ip().toString(),
                        0,
                        "UDP",
                        this
                    );
                    m_availableSockets.append(socket);
                }
            }
        }
    }
    
    emit socketsUpdated(m_availableSockets);
}

void UdpHandler::setupConnection(const QString &address, quint16 port, Mode mode)
{
    m_currentMode = mode;
    
    if (m_udpSocket->state() != QAbstractSocket::UnconnectedState) {
        m_udpSocket->close();
    }

    if (mode == Listener)
    {
        if (m_udpSocket->bind(QHostAddress(address), port))
        {
            m_logger.log(QString("UDP listener started on %1:%2").arg(address).arg(port));
            emit connectionStatusChanged(true);
        } else {
            m_logger.log(QString("Failed to bind UDP socket: %1").arg(m_udpSocket->errorString()), "ERROR");
            emit errorOccurred(tr("Failed to bind UDP socket"));
        }
    }
    else
    {
        m_udpSocket->connectToHost(address, port);
        emit publisherStatusChanged(true);
    }
}

void UdpHandler::sendMessage(const QString &message)
{
    if (m_currentMode != Publisher)
    {
        emit errorOccurred(tr("Not in publisher mode"));
        return;
    }

    QByteArray datagram = message.toUtf8();
    qint64 bytesSent = m_udpSocket->write(datagram);
    
    if (bytesSent == -1)
    {
        m_logger.log(QString("Failed to send UDP message: %1").arg(m_udpSocket->errorString()), "ERROR");
        emit errorOccurred(tr("Failed to send UDP message"));
    }
    else
    {
        m_logger.log(QString("UDP message sent: %1").arg(message));
    }
}

void UdpHandler::onReadyRead()
{
    while (m_udpSocket->hasPendingDatagrams())
    {
        QNetworkDatagram datagram = m_udpSocket->receiveDatagram();
        QString message = QString::fromUtf8(datagram.data());
        
        m_logger.log(QString("UDP message received from %1:%2: %3")
            .arg(datagram.senderAddress().toString())
            .arg(datagram.senderPort())
            .arg(message));
        
        emit messageReceived(message);
    }
}
