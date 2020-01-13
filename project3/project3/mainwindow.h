#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSizePolicy>
#include <QTcpSocket>
#include <QTcpServer>
//#include "client.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void listen();

private slots:
    void on_Connect_clicked();

    void on_Disconnect_clicked();

    void connecttoserver();

    void on_connected();

    void write();

    void on_send_clicked();

    void on_Chat_returnPressed();

    void on_newconn();

    void read_socket();

    void socket_disconnected();

private:
    Ui::MainWindow *ui;
    QTcpSocket *socket;
    QTcpServer *server;
};
#endif // MAINWINDOW_H
