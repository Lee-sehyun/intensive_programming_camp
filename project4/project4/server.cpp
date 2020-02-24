#include "server.h"
#include "ui_server.h"

#include <QDebug>
#include <QHostAddress>
#include <QAbstractSocket>
#include <QtNetwork>

server::server(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::server),
    _server_1(this),
    _server_2(this)
{
    ui->setupUi(this);
    this->setWindowTitle("Project4 오목게임 서버편");
    connect(&_server_1, SIGNAL(newConnection()), this, SLOT(onNewConnection()));
    connect(&_server_2, SIGNAL(newConnection()), this, SLOT(onNewConnection()));
}

server::~server()
{
    delete ui;
}


void server::on_Open_clicked()
{
    _server_1.listen(QHostAddress::Any, 8010);
    _server_2.listen(QHostAddress::Any, 8000);
    QList<QHostAddress> addrlist = QNetworkInterface::allAddresses();
    foreach(QHostAddress addr, addrlist){
        if ( 0 >= addr.toIPv4Address() ) continue;
        else {
              if (addr.toString().contains("127.0.0.1") ) continue;
              else { ui->ip->append(addr.toString());  break; }
        }
    }
}

void server::onNewConnection()
{
   QTcpSocket *clientSocket = _server_1.nextPendingConnection();
   connect(clientSocket, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
   connect(clientSocket, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this, SLOT(onSocketStateChanged(QAbstractSocket::SocketState)));

    _sockets.push_back(clientSocket);
}
