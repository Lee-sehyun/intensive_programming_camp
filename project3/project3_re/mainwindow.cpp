#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QHostAddress>
#include <QAbstractSocket>

QString name;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , tcpsocket(this)
{
    ui->setupUi(this);
//    this->setWindowFlag(Qt::WindowCloseButtonHint /*| Qt::NSWindowsFixedSizeDialogHint*/);
    this->setWindowTitle("Project3 남들과 함께 얘기해요");


    m_connected = false;
//    QString r = "0", g = "0", b = "0";
//    QString rgb = "background:rgb(" + r + "," + g + "," + b + ")";
    this->setStyleSheet("background:rgb(200, 170, 255)");
    ui->Chating->setStyleSheet("background:rgb(255, 255, 255)");
    ui->Name->setStyleSheet("background:rgb(255, 255, 255)");
    ui->ipAddress->setStyleSheet("background:rgb(255, 255, 255)");
    ui->Connect->setStyleSheet("background:hsla(120,100%,75%, 1)");
    ui->frame->setStyleSheet("background:hsla(120,100%,75%, 1)");

//    tcpserver.listen(QHostAddress::Any, 8010);

//    connect(&tcpserver, SIGNAL(newConnection()), this, SLOT(connected()));
    connect(&tcpsocket, SIGNAL(readyRead()), this, SLOT(read()));
    connect(&tcpsocket, SIGNAL(connected()), this, SLOT(onconnected_Server()));
    connect(&tcpsocket, SIGNAL(disconnected()), this, SLOT(disconnected()));
    connect(&tcpsocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(error()));
//    QObject::connect(&tcpsocket, SIGNAL(readyRead()), this, SLOT(onReadyRead()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void MainWindow::on_Connect_clicked()
{
    name = ui->Name->text();

    connected();
}

void MainWindow::on_Disconnect_clicked()
{
    QTextStream out(&tcpsocket);

    QString str = name + "님이 나갔습니다!";

    ui->Chating->append(str);

    out << str;

//    disconnected();
    tcpsocket.close();
}

void MainWindow::connected(){
    QString ip = ui->ipAddress->text();
    if(ip.isEmpty()){
        tcpsocket.connectToHost(QHostAddress::LocalHost, 8010);
    }
    else{
        tcpsocket.connectToHost(ip, 8010);
    }

//    onconnected_Server();

//    QTcpSocket *clientSocket = tcpserver.nextPendingConnection();
//    connect(clientSocket, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
//    connect(clientSocket, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this, SLOT(onSocketStateChanged(QAbstractSocket::SocketState)));

//    tcpsockets.push_back(clientSocket);
//    for (QTcpSocket* socket : tcpsockets) {
//        socket->write(QByteArray::fromStdString(clientSocket->peerAddress().toString().toStdString() + " connected to server !\n"));
//    }

}

void MainWindow::disconnected(){

    if (m_connected == true){
//        tcpsocket.close();
        ui->Chating->setText("");
        m_connected = false;
        ui->stackedWidget->setCurrentIndex(0);
    }
}

void MainWindow::onconnected_Server(){
    ui->Chating->append("연결되었습니다.");
    m_connected = true;
    ui->stackedWidget->setCurrentIndex(1);

    QTextStream out(&tcpsocket);

    QString str = name + "님이 들어왔습니다!";

    ui->Chating->append(str);

    out << str;
}

void MainWindow::on_send_clicked()
{
    send();
}

void MainWindow::send(){
    QString strtemp;
    QString str = ui->Chat->text();
    QTextStream out(&tcpsocket);

    if (str.isEmpty() == false){
        strtemp = name + " : " + str;

        ui->Chating->append(strtemp);

        //소켓으로 전송
        out<<strtemp;
        ui->Chat->setText("");
    }

//    strtemp = name + " : " + str;

//    ui->Chating->append(strtemp);

//    tcpsocket.write(str.toUtf8().constData());

//    tcpsocket.flush();

//    ui->Chat->setText("");





//    QByteArray block;
//    QDataStream out(&block, QIODevice::WriteOnly);

//    out<<quint16(0);

//    out<<ui->Chat->text();

//    out.device()->seek(0);

//    out<<quint16(block.size() - sizeof(quint16));

//    tcpsocket.write(block);
}

void MainWindow::read(){
    QString Message;
    QString Messagetemp;

    QTextStream in(&tcpsocket);

    Message = tcpsocket.readLine();
    ui->Chating->append(Message);

//    while(true){
//        if(tcpsocket.canReadLine()){
//            Message = tcpsocket.readLine();
//            Messagetemp = name + " : " + Message;
//            ui->Chating->append(Messagetemp);
//            break;
//        }
//    }


//    while(tcpsocket.canReadLine()){
//        QByteArray buffer= tcpsocket.readLine();
//        if(strcmp(buffer.constData(), "!exit\n") == 0)
//        {
//            qDebug("No data");
//        }
//        else
//            ui->Chating->append(buffer);

//    }



//    QDataStream in(&tcpsocket);

//    while(true){
//        //nextBlcokSize 가 0 이면 아직 데이터를 못받은것
//       if(nextBlockSize == 0){
//           //수신된 데이터가 nextBlockSize 바이트보다 큰지 확인
//           if(tcpsocket.bytesAvailable() < sizeof(quint16))
//               ;
//           else
//               in>>nextBlockSize;
//           continue;
//       }
//       else if(tcpsocket.bytesAvailable() < nextBlockSize)
//            continue;

//       else if(tcpsocket.bytesAvailable() >= nextBlockSize){
//           QString strBuf;
//           in>>strBuf;

//           ui->Chating->setText(strBuf);
//           this->nextBlockSize = 0;

//           break;
//       }
//    }
}

void MainWindow::on_Chat_returnPressed()
{
    on_send_clicked();
}

void MainWindow::error(){
    ui->Chating->setText(tcpsocket.errorString());
}
