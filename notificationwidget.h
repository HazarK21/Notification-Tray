#ifndef NOTIFICATIONWIDGET_H
#define NOTIFICATIONWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include "Notification.h"

class NotificationWidget : public QWidget {
    Q_OBJECT

public:
    NotificationWidget(const Notification &notification, QWidget *parent = nullptr);

private slots:
    void dismissButtonClicked();

signals:
    void dismissed(NotificationWidget *widget); // Signal to notify when the widget is dismissed

private:
    QVBoxLayout *layout;
    QLabel *titleLabel;
    QLabel *bodyLabel;     // Optional
    QPushButton *dismissButton; // Optional
    Notification notificationData;
};

#endif // NOTIFICATIONWIDGET_H
