#include "notificationwidget.h"
#include <QHBoxLayout>

NotificationWidget::NotificationWidget(const Notification &notification, QWidget *parent)
    : QWidget(parent)
{
    layout = new QVBoxLayout(this);
    setLayout(layout);

    titleLabel = new QLabel(notification.title, this);
    layout->addWidget(titleLabel);

    if (!notification.body.isEmpty()) {
        bodyLabel = new QLabel(notification.body, this);
        layout->addWidget(bodyLabel);
    }

    if (notification.icon.isNull()) {
        dismissButton = new QPushButton("Dismiss", this);
        connect(dismissButton, &QPushButton::clicked, this, &NotificationWidget::dismissButtonClicked);
        layout->addWidget(dismissButton);
    } else {
        // Implement icon layout here (optional)
        // You can use a QHBoxLayout and add the icon and title/body labels
    }
}

void NotificationWidget::dismissButtonClicked() {
    emit dismissed(this); // Emit signal to NotificationCenter for removal
}
