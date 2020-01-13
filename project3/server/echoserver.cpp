#include "echoserver.h"
#include "clientsocket.h"

EchoServer::EchoServer(QObject *parent)
    :QTcpServer(parent){
}

void EchoServer::incomingConnection(int socketId){
    ClientSocket *socket = new ClientSocket(this);

    socket->setSocketDescriptor(socketId);
}
