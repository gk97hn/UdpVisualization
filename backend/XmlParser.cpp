#include "XmlParser.h"
#include <QFile>
#include <QXmlStreamReader>
#include <QDebug>

XmlParser::XmlParser(QObject *parent) : QObject(parent), m_logger(Logger::instance())
{
    connect(&m_fileWatcher, &QFileSystemWatcher::fileChanged, this, &XmlParser::onXmlFileChanged);
}

bool XmlParser::parseXmlFile(const QString &filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        m_logger.log(QString("Failed to open XML file: %1").arg(filePath), "ERROR");
        emit parseError(tr("Failed to open XML file"));
        return false;
    }

    QList<ShapeModel*> shapes;
    QXmlStreamReader xml(&file);

    while (!xml.atEnd() && !xml.hasError()) {
        xml.readNext();
        
        if (xml.isStartElement() && xml.name() == "Shapes") {
            while (!(xml.isEndElement() && xml.name() == "Shapes")) {
                xml.readNext();
                
                if (xml.isStartElement()) {
                    QVariantMap properties;
                    for (const auto &attr : xml.attributes()) {
                        properties.insert(attr.name().toString(), attr.value().toString());
                    }
                    
                    ShapeModel *shape = new ShapeModel(xml.name().toString(), properties, this);
                    shapes.append(shape);
                }
            }
        }
    }

    if (xml.hasError()) {
        m_logger.log(QString("XML parse error: %1").arg(xml.errorString()), "ERROR");
        emit parseError(xml.errorString());
        file.close();
        return false;
    }

    file.close();
    if (!m_currentFile.isEmpty()) {
        m_fileWatcher.removePath(m_currentFile);
    }
    m_fileWatcher.addPath(filePath);
    m_currentFile = filePath;

    m_logger.log(QString("Successfully parsed XML file: %1").arg(filePath));
    emit shapesParsed(shapes);
    return true;
}

void XmlParser::onXmlFileChanged(const QString &path)
{
    m_logger.log(QString("XML file changed: %1").arg(path));
    parseXmlFile(path);
}
