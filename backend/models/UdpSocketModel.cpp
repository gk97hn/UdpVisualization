#include "UdpSocketModel.h"

UdpSocketModel::UdpSocketModel(QObject *parent) : QObject(parent),
    m_address(""),
    m_port(0),
    m_protocol("")
{
}

UdpSocketModel::UdpSocketModel(const QString &address, quint16 port, const QString &protocol, QObject *parent) :
    QObject(parent),
    m_address(address),
    m_port(port),
    m_protocol(protocol)
{
}

QString UdpSocketModel::address() const
{
    return m_address;
}

quint16 UdpSocketModel::port() const
{
    return m_port;
}

QString UdpSocketModel::protocol() const
{
    return m_protocol;
}
