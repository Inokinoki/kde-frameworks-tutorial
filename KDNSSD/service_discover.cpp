#include <DNSSD/ServiceBrowser>
#include <DNSSD/PublicService>
#include <QDebug>
#include <QCoreApplication>

/**
 * /usr/include/KF5
 * KDNSSD/
 * ├── dnssd
 * │   ├── domainbrowser.h
 * │   ├── domainmodel.h
 * │   ├── kdnssd_export.h
 * │   ├── publicservice.h
 * │   ├── remoteservice.h
 * │   ├── servicebase.h
 * │   ├── servicebrowser.h
 * │   ├── servicemodel.h
 * │   └── servicetypebrowser.h
 * └── DNSSD
 *     ├── DomainBrowser
 *     ├── DomainModel
 *     ├── PublicService
 *     ├── RemoteService
 *     ├── ServiceBase
 *     ├── ServiceBrowser
 *     ├── ServiceModel
 *     └── ServiceTypeBrowser
 */

class ServiceExplorer : public QObject
{
public:
    ServiceExplorer()
    {
        m_browser = new KDNSSD::ServiceBrowser(QStringLiteral("_http._tcp"));

        connect(m_browser, &KDNSSD::ServiceBrowser::serviceAdded,
                this, [](KDNSSD::RemoteService::Ptr service) {
                    qDebug() << "Service found on" << service->hostName() << service->serviceName();
                });
        connect(m_browser, &KDNSSD::ServiceBrowser::serviceRemoved,
                this, [](KDNSSD::RemoteService::Ptr service) {
                    qDebug() << "Service unregistered on" << service->hostName();
                });
        
        m_browser->startBrowse();
    }

    ~ServiceExplorer()
    {
        if (m_browser) delete m_browser;
    }

private:
    KDNSSD::ServiceBrowser *m_browser;
};

int main(int argc, char **argv)
{
    QCoreApplication app(argc, argv);
    if (KDNSSD::ServiceBrowser::isAvailable() == KDNSSD::ServiceBrowser::State::Unsupported) {
        qDebug() << "DNSSD Unsupported";
    }
    else {
        qDebug() << "Localhost name:" << KDNSSD::ServiceBrowser::getLocalHostName();

        ServiceExplorer explorer;

        return app.exec();
    }

    return -1;
}

