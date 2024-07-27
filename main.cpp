#include "mainwindow.h"
#include <QApplication>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    QString dirPath = QCoreApplication::applicationDirPath();
    QString filePath = dirPath + "/Theme.qss";
    QFile file(filePath);
    file.open(QFile::ReadOnly);
    QString styleSheet { QLatin1String(file.readAll()) };

    a.setStyleSheet(styleSheet);
    w.show();
    return a.exec();
}
