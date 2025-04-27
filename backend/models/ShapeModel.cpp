#include "ShapeModel.h"

ShapeModel::ShapeModel(const QString &type, const QVariantMap &properties, QObject *parent) :
    QObject(parent),
    m_type(type),
    m_properties(properties)
{
}

QString ShapeModel::type() const
{
    return m_type;
}

QVariantMap ShapeModel::properties() const
{
    return m_properties;
}