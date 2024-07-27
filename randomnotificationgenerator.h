// randomnotificationgenerator.h
#ifndef RANDOMNOTIFICATIONGENERATOR_H
#define RANDOMNOTIFICATIONGENERATOR_H

#include <QString>
#include <QStringList>
#include <QRandomGenerator>

class RandomNotificationGenerator {
public:
    static QString generateRandomTitle();
    static QString generateRandomMessage();
};

#endif // RANDOMNOTIFICATIONGENERATOR_H
