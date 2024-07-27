#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "notificationmanager.h"
#include "ui_mainwindow.h"
#include "notificationscheduler.h"

class QVBoxLayout;
class QWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent *event) override {
        if (manager->getQueueWindow()) {
            manager->getQueueWindow()->close();
        }
        QMainWindow::closeEvent(event);
    }

private:
    NotificationManager *manager;
    QVBoxLayout *nLayout;
    QWidget *nWidget;
    Ui::MainWindow *ui;
    void NewNotification(const QString &title, const QString &message);
    NotificationScheduler *scheduler;
    int height;
    int count;
    void ToggleQueue();
};

#endif // MAINWINDOW_H
