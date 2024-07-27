// randomnotificationgenerator.cpp
#include "randomnotificationgenerator.h"

QString RandomNotificationGenerator::generateRandomTitle() {
    QStringList titles = {"Welcome", "Notification", "New Message", "Alert"};
    return titles[QRandomGenerator::global()->bounded(titles.size())];
}

QString RandomNotificationGenerator::generateRandomMessage() {
    QStringList messages = {"This is a random notification message.", "Something happened!", "Check this out!", "Important update."};
    return messages[QRandomGenerator::global()->bounded(messages.size())];
}
