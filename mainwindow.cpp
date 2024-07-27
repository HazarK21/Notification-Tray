#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    manager(new NotificationManager),
    ui(new Ui::MainWindow),
    scheduler(new NotificationScheduler)
{
    ui->setupUi(this);
    connect(scheduler, &NotificationScheduler::newNotification, manager, [=](const QString& title, const QString& message) {
        manager->showNotification(title, message, nLayout);
    });
    connect(manager, SIGNAL(notificationReceived(QString,QString)), this, SLOT(NewNotification()));
    connect(ui->toggleQueueButton, &QPushButton::clicked, this, &MainWindow::ToggleQueue);

    scheduler->startTimer();
    nWidget = new QWidget(this);
    nLayout = new QVBoxLayout(nWidget);
    ui->verticalLayout_2->insertWidget(0, nWidget);
    manager->setNotificationLayout(nLayout);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::NewNotification(const QString &title, const QString &message) {
    manager->showNotification(title, message, nLayout);
}


void MainWindow::ToggleQueue(){

    manager->queueWindow->setFixedHeight(700);

    if(manager->isVisible !=true){
        manager->queueWindow->show();
        ui->toggleQueueButton->setText("Hide Queue");
        manager->isVisible = true;

    } else{
        manager->queueWindow->hide();
        ui->toggleQueueButton->setText("Show Queue");
        manager->isVisible = false;
    }
}
