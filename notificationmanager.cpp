#include "notificationmanager.h"

NotificationManager::NotificationManager(QObject *parent) : QObject(parent), scheduler(new NotificationScheduler) {
    CreateQueueWindow();
}

void NotificationManager::showNotification(const QString &title, const QString &message, QVBoxLayout *notificationLayout) {
    if (nLayout->count() < 3) {
        QFrame *groupBox = new QFrame();
        QGridLayout *mainLayout = new QGridLayout();
        QLabel *titleLabel = new QLabel(title);
        QLabel *messageLabel = new QLabel(message);
        QLabel *timerLabel = new QLabel("01:00");
        QPushButton *dismissButton = new QPushButton("");
        dismissButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        QLabel *iconLabel = new QLabel();
        iconLabel->setFixedSize(40, 105);
        groupBox->setFixedSize(500, 120);
        iconLabel->setStyleSheet("border: none;");
        iconLabel->setStyleSheet("background-color: orange;");
        iconLabel->setAlignment(Qt::AlignVCenter);
        titleLabel->setStyleSheet("font-weight: bold; color: white; font: 22pt 'Eras Demi ITC'");
        messageLabel->setStyleSheet("color: white; font: 12pt");
        timerLabel->setStyleSheet("color: white; font-weight: bold");
        groupBox->setStyleSheet("QFrame {background-color: gray; }");

        dismissButton->setIcon(mapper.dismissIcon);
        dismissButton->setIconSize(QSize(40, 40));
        dismissButton->setStyleSheet("QPushButton { border: none; background-color: transparent; }"
                                     "QPushButton:hover { background-color: rgba(193, 193, 193, 0.3); }"
                                     "QPushButton:pressed { background-color: rgba(100, 100, 100, 0.5); }"                                     );

        QIcon icon = mapper.getIconForTitle(title);
        iconLabel->setPixmap(icon.pixmap(iconLabel->size()));

        connect(dismissButton, &QPushButton::clicked, this, [this, groupBox, notificationLayout](){
            dismissNotification(groupBox, notificationLayout);
        });

        mainLayout->addWidget(iconLabel, 0, 0, 3, 1, Qt::AlignTop);
        mainLayout->addWidget(titleLabel, 0, 1);
        mainLayout->addWidget(messageLabel, 1, 1);
        mainLayout->addWidget(timerLabel, 2, 1);
        mainLayout->addWidget(dismissButton, 1, 2);
        titleLabel->setAlignment(Qt::AlignTop);
        messageLabel->setAlignment(Qt::AlignTop);
        timerLabel->setAlignment(Qt::AlignTop);
        mainLayout->setColumnStretch(0, 0);
        mainLayout->setColumnStretch(1, 1);
        mainLayout->setHorizontalSpacing(15);
        groupBox->setLayout(mainLayout);
        notificationLayout->insertWidget(0, groupBox);

        QTimer *timer = new QTimer(groupBox);
        timer->setInterval(1000);
        int seconds = 60;

        QObject::connect(timer, &QTimer::timeout, this, [timer, timerLabel, groupBox, notificationLayout, this, title, message, seconds]() mutable {
            --seconds;
            if (seconds >= 0) {
                int minutes = seconds / 60;
                int remainingSeconds = seconds % 60;
                QString text = QString("%1:%2").arg(minutes, 2, 10, QLatin1Char('0')).arg(remainingSeconds, 2, 10, QLatin1Char('0'));
                timerLabel->setText(text);
            } else {
                dismissNotification(groupBox, notificationLayout);
                timer->stop();
                timer->deleteLater();
            }
        });

        timer->start();

        emit notificationReceived(title, message);
    } else {
        notificationQueue.enqueue(qMakePair(title, message));
        showQueueContents();
        emit notificationEnqueued(title, message);
    }
}

void NotificationManager::dismissNotification(QFrame *groupBox, QVBoxLayout *notificationLayout) {
    notificationLayout->removeWidget(groupBox);
    groupBox->deleteLater();

    if (!notificationQueue.isEmpty()) {
        auto nextNotification = notificationQueue.dequeue();
        showNotification(nextNotification.first, nextNotification.second, notificationLayout);
        showQueueContents();
    }
}

void NotificationManager::showQueueContents() {
    tableWidget->clearContents();
    tableWidget->setRowCount(notificationQueue.size());
    int row = 0;

    for (const QPair<QString, QString> &item : notificationQueue) {
        QTableWidgetItem *titleItem = new QTableWidgetItem(item.first);
        QTableWidgetItem *messageItem = new QTableWidgetItem(item.second);
        tableWidget->setItem(row, 0, titleItem);
        tableWidget->setItem(row, 1, messageItem);
        row++;
    }
}

void NotificationManager::setNotificationLayout(QVBoxLayout *layout) {
    nLayout = layout;
}

void NotificationManager::CreateQueueWindow() {
    queueWindow = new QWidget();
    queueWindow->setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::CustomizeWindowHint);
    QueueLayout = new QVBoxLayout(queueWindow);
    queueWindow->setLayout(QueueLayout);
    tableWidget = new QTableWidget();
    tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableWidget->setColumnCount(2);
    QueueLayout->addWidget(tableWidget);
    QStringList headers;
    headers << "Title" << "Message";
    tableWidget->setHorizontalHeaderLabels(headers);
    tableWidget->setColumnCount(2);
    connect(this, &NotificationManager::notificationEnqueued, this, &NotificationManager::showQueueContents);
    queueWindow->installEventFilter(this);
    tableWidget->setSelectionMode(QAbstractItemView::NoSelection);
    tableWidget->setStyleSheet("QTableWidget QHeaderView::section { background-color: rgb(26, 6, 150); color: white; }"
                               "QTableWidget::item { background-color: rgb(193, 193, 193); }");}


bool NotificationManager::eventFilter(QObject *obj, QEvent *event) {
    if (obj == queueWindow) {
        if (event->type() == QEvent::MouseButtonPress) {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
            if (mouseEvent->button() == Qt::LeftButton) {
                cur_pos = mouseEvent->globalPosition().toPoint();
            }
        } else if (event->type() == QEvent::MouseMove && (static_cast<QMouseEvent*>(event)->buttons() & Qt::LeftButton)) {
            QPoint new_pos = static_cast<QMouseEvent*>(event)->globalPosition().toPoint() - cur_pos;
            queueWindow->move(queueWindow->pos() + new_pos);
            cur_pos = static_cast<QMouseEvent*>(event)->globalPosition().toPoint();
            return true;
        }
    }
    return QObject::eventFilter(obj, event);
}


