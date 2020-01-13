#ifndef ECHOSERVER_H
#define ECHOSERVER_H

#include <QTcpServer>

class EchoServer : public QTcpServer
{
    Q_OBJECT

public:
    EchoServer(QObject *parent=0);

private:
    //overload
    void incomingConnection(int socketId);
};

#endif // ECHOSERVER_H
