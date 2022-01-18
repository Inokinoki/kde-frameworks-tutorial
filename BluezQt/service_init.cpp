#include <BluezQt/Manager>
#include <BluezQt/InitManagerJob>
#include <QDebug>
#include <QCoreApplication>

class ServiceExplorer : public QObject
{
public:
    ServiceExplorer()
    {
        m_manager = new BluezQt::Manager();
        BluezQt::InitManagerJob *m_job = m_manager->init();

        connect(m_job, &BluezQt::InitManagerJob::result,
                this, [](BluezQt::InitManagerJob *job) {
                    if (job->error())
                    {
                        qDebug() << "BluezQt manager error " << job->errorText();
                        QCoreApplication::exit();
                        return;
                    }

                    // Do something
                    BluezQt::Manager *manager = job->manager();
                    if (manager && manager->isInitialized())
                    {
                        QList<BluezQt::AdapterPtr> adapters = manager->adapters();
                        qDebug() << "BluezQt manager initiated with" << adapters.count() << "adapters:";
                        for (BluezQt::AdapterPtr p : adapters)
                        {
                            qDebug() << p->name() << "@" << p->address();
                        }
                        QList<BluezQt::DevicePtr> devices = manager->devices();
                        qDebug() << "and" << devices.count() << "devices:";
                        for (BluezQt::DevicePtr p : devices)
                        {
                            qDebug() << p->name() << "@" << p->address();
                        }
                    }
                    QCoreApplication::exit();
                });

        m_job->start();
    }

    ~ServiceExplorer()
    {
        if (m_manager) delete m_manager;
    }

private:
    BluezQt::Manager *m_manager;
};

int main(int argc, char **argv)
{
    QCoreApplication app(argc, argv);

    ServiceExplorer explorer;

    return app.exec();
}
