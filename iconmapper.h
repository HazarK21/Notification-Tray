#ifndef ICONMAPPER_H
#define ICONMAPPER_H

#include <QMap>
#include <QString>
#include <QIcon>

class IconMapper
{
public:
    IconMapper();
    QIcon dismissIcon;
    QIcon getIconForTitle(const QString &title) const;

private:
    QMap<QString, QString> iconMap;
};

#endif
