#ifndef NOTIFICATIONMANAGER_H
#define NOTIFICATIONMANAGER_H

#include <QString>
#include <QVBoxLayout>
#include "notificationscheduler.h"
#include <QQueue>
#include <QTableWidget>
#include <QGroupBox>
#include "iconmapper.h"
#include <QMouseEvent>
#include <QPoint>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QApplication>
#include <QFrame>

class QVBoxLayout;

class NotificationManager : public QObject {
    Q_OBJECT

public:
    NotificationManager(QObject *parent = nullptr);
    void showQueueContents();
    void setNotificationLayout(QVBoxLayout *layout);
    QWidget* getQueueWindow() const {
        return queueWindow;
    }
    bool isVisible = false;
    QWidget *queueWindow;

signals:
    void notificationReceived(QString title, QString message);
    void notificationEnqueued(const QString &title, const QString &message);

public slots:
    void showNotification(const QString &title, const QString &message, QVBoxLayout *notificationLayout);
    void dismissNotification(QFrame *groupBox, QVBoxLayout *notificationLayout);
    void CreateQueueWindow();

private:
    QVBoxLayout *nLayout;
    NotificationScheduler *scheduler;
    QQueue<QPair<QString, QString>> notificationQueue;
    QVBoxLayout *QueueLayout;
    QTableWidget *tableWidget;
    int row = 0;
    IconMapper mapper;
    bool eventFilter(QObject *obj, QEvent *event);
    QPoint cur_pos;
    QPoint new_pos;

};

#endif // NOTIFICATIONMANAGER_H
