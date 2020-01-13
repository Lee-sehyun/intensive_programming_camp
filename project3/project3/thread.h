#ifndef THREAD_H
#define THREAD_H

#include <QThread>
#include <QMutex>
#include <QWaitCondition>

class thread : public QThread
{
    Q_OBJECT

public:
    thread(QObject *parent = 0);
    ~thread();

    void request(const QString &hostName, quint16 port);
    void run();

signals:
    void newFortune(const QString &fortune);
    void error(int socketError, const QString &message);

private:
    QString hostName;
    quint16 port;
    QMutex mutex;
    QWaitCondition cond;
    bool quit;
};

#endif // THREAD_H
