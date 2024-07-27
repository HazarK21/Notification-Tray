#ifndef NOTIFICATION_H
#define NOTIFICATION_H
#include <QString>
#include <QPixmap>

struct Notification {
    QString title;
    QString body; // Optional
    QPixmap icon;  // Optional
};

#endif // NOTIFICATION_H
