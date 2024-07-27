// notificationscheduler.h
#ifndef NOTIFICATIONSCHEDULER_H
#define NOTIFICATIONSCHEDULER_H

#include <QObject>
#include <QTimer>

class NotificationScheduler : public QObject {
    Q_OBJECT
public:
    explicit NotificationScheduler(QObject *parent = nullptr);
    QString title;
    QString message;
    void startTimer();

signals:
    void newNotification(const QString &title, const QString &message);

private slots:
    void scheduleNextNotification();

private:
    QTimer timer;
};

#endif // NOTIFICATIONSCHEDULER_H
