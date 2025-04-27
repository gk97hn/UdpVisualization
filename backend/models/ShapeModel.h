#ifndef SHAPEMODEL_H
#define SHAPEMODEL_H

#include <QObject>
#include <QVariantMap>
#include <QMap>
class ShapeModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString type READ type CONSTANT)
    Q_PROPERTY(QVariantMap properties READ properties CONSTANT)

public:
    ShapeModel(const QString &type, const QVariantMap &properties, QObject *parent = nullptr);
    
    QString type() const;
    QVariantMap properties() const;

private:
    QString m_type;
    QVariantMap m_properties;
};

#endif // SHAPEMODEL_H
