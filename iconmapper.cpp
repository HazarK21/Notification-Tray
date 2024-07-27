#include "iconmapper.h"

IconMapper::IconMapper()
{
    iconMap.insert("Welcome", "icons/welcome_icon.png");
    iconMap.insert("Notification", "icons/notification_icon.png");
    iconMap.insert("New Message", "icons/message_icon.png");
    iconMap.insert("Alert", "icons/alert_icon.png");
    dismissIcon = QIcon("icons/dismiss_icon.png");
}

QIcon IconMapper::getIconForTitle(const QString &title) const
{
    QString iconPath = iconMap.value(title);
    return QIcon(iconPath);
}
