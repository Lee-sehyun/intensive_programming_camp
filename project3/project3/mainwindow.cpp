#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QHostAddress>

QString name;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    server=new QTcpServer(this);

    socket=new QTcpSocket(this);

    connect(socket,SIGNAL(connected()),this,SLOT(on_connected()));
    connect(server,SIGNAL(newConnection()),this,SLOT(on_newconn()));
    connect(socket,SIGNAL(readyRead()),this,SLOT(read_socket()));
//    connect(socket,SIGNAL(disconnected()),this,SLOT(socket_disconnected()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

