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

class ServicePubisher : public QObject
{
public:
    ServicePubisher()
    {
        m_service = new KDNSSD::PublicService("My files", "_http._tcp", 8080);
        connect(m_service, &KDNSSD::PublicService::published, this, &ServicePubisher::isPublished);
        m_service->publishAsync();

        /* Or sync:
        bool isOK = service->publish();

        if (isOK) {
            qDebug() << "My files Service published";
        } else {
            qDebug() << "My files Service not published";
        }
        */
    }

    ~ServicePubisher()
    {
        if (m_service) delete m_service;
    }

    void isPublished(bool state)
    {
        if (state) {
            qDebug() << "Service published";
        } else {
            qDebug() << "Service not published";
        }
    }

private:
    KDNSSD::PublicService *m_service;
};

int main(int argc, char **argv)
{
    QCoreApplication app(argc, argv);
    if (KDNSSD::ServiceBrowser::isAvailable() == KDNSSD::ServiceBrowser::State::Unsupported) {
        qDebug() << "DNSSD Unsupported";
    }
    else {
        qDebug() << "Localhost name:" << KDNSSD::ServiceBrowser::getLocalHostName();

        ServicePubisher publisher;

        return app.exec();
    }

    return -1;
}

