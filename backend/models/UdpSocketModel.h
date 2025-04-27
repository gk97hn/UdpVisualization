#ifndef UDPSOCKETMODEL_H
#define UDPSOCKETMODEL_H

#include <QObject>
#include <QMetaType>

class UdpSocketModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString address READ address CONSTANT)
    Q_PROPERTY(quint16 port READ port CONSTANT)
    Q_PROPERTY(QString protocol READ protocol CONSTANT)

public:
    explicit UdpSocketModel(QObject *parent = nullptr);
    UdpSocketModel(const QString &address, quint16 port, const QString &protocol, QObject *parent = nullptr);

    QString address() const;
    quint16 port() const;
    QString protocol() const;

private:
    QString m_address;
    quint16 m_port;
    QString m_protocol;
};

Q_DECLARE_METATYPE(UdpSocketModel*)

#endif // UDPSOCKETMODEL_H
