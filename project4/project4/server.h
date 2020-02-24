#ifndef SERVER_H
#define SERVER_H

#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>

namespace Ui {
class server;
}

class server : public QWidget
{
    Q_OBJECT

public:
    explicit server(QWidget *parent = nullptr);
    ~server();


public slots:
    void onNewConnection();

    void onSocketStateChanged(QAbstractSocket::SocketState socketState);

    void onReadyRead();

private slots:
    void on_Open_clicked();

private:
    Ui::server *ui;
    QTcpServer  _server_1;
    QTcpServer  _server_2;
    QList<QTcpSocket*>  _sockets;
};

#endif // SERVER_H
