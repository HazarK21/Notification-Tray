// notificationscheduler.cpp
#include "notificationscheduler.h"
#include "randomnotificationgenerator.h"

NotificationScheduler::NotificationScheduler(QObject *parent) : QObject(parent)
{
    timer.setInterval(3000);
}

void NotificationScheduler::startTimer()
{
    connect(&timer, &QTimer::timeout, this, &NotificationScheduler::scheduleNextNotification);
    timer.start();
}

void NotificationScheduler::scheduleNextNotification() {

    title = RandomNotificationGenerator::generateRandomTitle();
    message = RandomNotificationGenerator::generateRandomMessage();
        emit newNotification(title, message);
}
