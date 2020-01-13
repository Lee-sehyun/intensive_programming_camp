#ifndef CLIENTSOCKET_H
#define CLIENTSOCKET_H

#include <QTcpSocket>

class ClientSocket : public QTcpSocket{
    Q_OBJECT
public:
    ClientSocket(QObject *parent=0);

private slots:
    void readClient();
private:
};

#endif // CLIENTSOCKET_H