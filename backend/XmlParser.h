#ifndef XMLPARSER_H
#define XMLPARSER_H

#include <QObject>
#include <QFileSystemWatcher>
#include "Logger.h"
#include "models/ShapeModel.h"

class XmlParser : public QObject
{
    Q_OBJECT
public:
    explicit XmlParser(QObject *parent = nullptr);
    bool parseXmlFile(const QString &filePath);

signals:
    void shapesParsed(const QList<ShapeModel*> &shapes); // Changed to QList<ShapeModel*>
    void parseError(const QString &error);

private slots:
    void onXmlFileChanged(const QString &path);

private:
    QFileSystemWatcher m_fileWatcher;
    QString m_currentFile;
    Logger &m_logger;
};

#endif // XMLPARSER_H
