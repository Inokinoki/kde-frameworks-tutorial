#include <QCoreApplication>
#include <QGuiApplication>
#include <QTimer>

#include <KJob>
#include <KJobTrackerInterface>
#include <KIO/JobTracker>


class FakeJob : public KJob
{
private:
    int m_progress;
    QTimer m_timer;
public:
    FakeJob(QObject *parent) : KJob(parent), m_progress(0), m_timer(this) {
        connect(&m_timer, &QTimer::timeout, this, &FakeJob::increment);
    }
    virtual ~FakeJob() override {}

    void start() override { m_timer.start(100); }
    void increment()
    {
        if (m_progress >= 100)
        {
            m_timer.stop();
            deleteLater();
            Q_EMIT emitResult();
        }
        else
        {
            m_progress++; setPercent(m_progress);
        }
    }
};

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    QGuiApplication::setDesktopFileName(QStringLiteral("KF5TutorialKJobProgress"));

    // Create a FakeJob
    FakeJob *job = new FakeJob(nullptr);
    KIO::getJobTracker()->registerJob(job);

    // Start the job
    job->start();

    return app.exec();
}
