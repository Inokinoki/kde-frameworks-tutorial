#include <QCoreApplication>
#include <KNotification>

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    KNotification *notification = new KNotification("Notif Test", KNotification::CloseOnTimeout, nullptr);
    notification->setComponentName(QStringLiteral("KFrameworksTutorial"));
    notification->setText("Test notifications");
    notification->sendEvent();
    notification->deleteLater();

    return app.exec();
}
