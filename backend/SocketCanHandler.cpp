#include "SocketCanHandler.h"
#include <QCanBus>
#include <QCanBusFrame>
#include <QTimer>
#include <QVariant>

SocketCanHandler::SocketCanHandler(QObject *parent) : QObject(parent),
    m_logger(Logger::instance())
{
    refreshCanInterfaces();
}

void SocketCanHandler::refreshCanInterfaces()
{
    m_availableInterfaces.clear();

    const QList<QCanBusDeviceInfo> devices = QCanBus::instance()->availableDevices("socketcan");

    for (const QCanBusDeviceInfo &device : devices) {
        m_availableInterfaces.append(device.name());
    }

    m_logger.log(QString("Available CAN interfaces: %1").arg(m_availableInterfaces.join(", ")));
    emit interfacesUpdated(m_availableInterfaces);
}
QStringList SocketCanHandler::availableCanInterfaces() const
{
    QStringList interfaces;
    for (const auto info : m_availableInterfaces) {
        interfaces.append(info);
    }
    return interfaces;
}
void SocketCanHandler::setupCanInterface(const QString &interface, int baudrate)
{
    if (m_canDevice) {
        m_canDevice->disconnectDevice();
        delete m_canDevice;
    }

    m_canDevice = QCanBus::instance()->createDevice("socketcan", interface);
    if (!m_canDevice) {
        m_logger.log(QString("Failed to create CAN device for interface %1").arg(interface), "ERROR");
        emit errorOccurred(tr("Failed to create CAN device"));
        return;
    }

    connect(m_canDevice, &QCanBusDevice::framesReceived, this, &SocketCanHandler::onCanFrameReceived);
    connect(m_canDevice, &QCanBusDevice::errorOccurred, this, [this](QCanBusDevice::CanBusError error) {
        emit errorOccurred(m_canDevice->errorString());
    });

    if (!m_canDevice->connectDevice()) {
        m_logger.log(QString("Failed to connect to CAN interface %1").arg(interface), "ERROR");
        emit errorOccurred(tr("Failed to connect to CAN interface"));
        return;
    }

    m_canDevice->setConfigurationParameter(QCanBusDevice::BitRateKey, QVariant(baudrate));

    m_logger.log(QString("Connected to CAN interface %1 with baudrate %2").arg(interface).arg(baudrate));
}

void SocketCanHandler::sendCanMessage(const QByteArray &message)
{
    if (!m_canDevice || m_canDevice->state() != QCanBusDevice::ConnectedState) {
        emit errorOccurred(tr("CAN device not connected"));
        return;
    }

    QCanBusFrame frame;
    frame.setPayload(message);
    m_canDevice->writeFrame(frame);

    m_logger.log(QString("CAN message sent: %1").arg(QString::fromLatin1(message.toHex())));
}

void SocketCanHandler::onCanFrameReceived()
{
    if (!m_canDevice) return;

    while (m_canDevice->framesAvailable()) {
        const QCanBusFrame frame = m_canDevice->readFrame();
        QString message = QString::fromLatin1(frame.payload().toHex());

        m_logger.log(QString("CAN message received: %1").arg(message));
        emit messageReceived(message);
    }
}
