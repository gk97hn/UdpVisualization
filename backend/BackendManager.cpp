#include "BackendManager.h"
#include <QDebug>
#include <QDir>

BackendManager::BackendManager(QObject *parent) : QObject(parent),
    m_xmlParser(new XmlParser(this)),
    m_udpHandler(new UdpHandler(this)),
    m_canHandler(new SocketCanHandler(this)),
    m_logger(Logger::instance())
{

    connect(m_xmlParser, &XmlParser::shapesParsed, this, [this](const QList<ShapeModel*> &shapes) {
        QVariantList list;
        for (const auto *shape : shapes) {
            list.append(QVariant::fromValue(shape));
        }
        emit shapesUpdated(list);
    });

    connect(m_xmlParser, &XmlParser::parseError, this, &BackendManager::errorOccurred);

    connect(m_udpHandler, &UdpHandler::socketsUpdated, this, [this](const QList<UdpSocketModel*> &sockets) {
           QVariantList list;
           for (const auto &socket : sockets) {
               list.append(QVariant::fromValue(socket));
           }
           emit udpSocketsUpdated(list);
       });

    connect(m_udpHandler, &UdpHandler::messageReceived, this, &BackendManager::udpMessagesReceived);
    connect(m_udpHandler, &UdpHandler::connectionStatusChanged, this, &BackendManager::connectionStatusChanged);
    connect(m_udpHandler, &UdpHandler::publisherStatusChanged, this, &BackendManager::publisherStatusChanged);
    connect(m_udpHandler, &UdpHandler::errorOccurred, this, &BackendManager::errorOccurred);

    connect(m_canHandler, &SocketCanHandler::interfacesUpdated, this, [this](const QStringList &interfaces) {
        QVariantList list;
        for (const auto &interface : interfaces) {
            list.append(interface);
        }
        emit canInterfacesUpdated(list);
    });

    connect(m_canHandler, &SocketCanHandler::messageReceived, this, &BackendManager::canMessageReceived);
    connect(m_canHandler, &SocketCanHandler::errorOccurred, this, &BackendManager::errorOccurred);
}

BackendManager::~BackendManager()
{
    delete m_xmlParser;
    delete m_udpHandler;
    delete m_canHandler;
}
QStringList BackendManager::getCanInterfaces()
{
    return m_canHandler->availableCanInterfaces();
}
void BackendManager::loadXmlFile(const QString &filePath)
{
    m_xmlParser->parseXmlFile(filePath);
}

void BackendManager::refreshUdpSockets()
{
    m_udpHandler->refreshAvailableSockets();
}

void BackendManager::connectToUdp(const QString &address, quint16 port, bool asPublisher)
{
    m_udpHandler->setupConnection(address, port, asPublisher ? UdpHandler::Publisher : UdpHandler::Listener);
}

void BackendManager::sendUdpMessage(const QString &message)
{
    m_udpHandler->sendMessage(message);
}

void BackendManager::setupCanInterface(const QString &interface, int baudrate)
{
    m_canHandler->setupCanInterface(interface, baudrate);
}

void BackendManager::sendCanMessage(const QByteArray &message)
{
    m_canHandler->sendCanMessage(message);
}



