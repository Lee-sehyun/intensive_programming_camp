#include "clientsocket.h"
#include <QByteArray>

ClientSocket::ClientSocket(QObject *parent)
    :QTcpSocket(parent){
    connect(this, SIGNAL(readyRead()), this, SLOT(readClient()));
    connect(this, SIGNAL(disconnected()), this, SLOT(deleteLater()));
}

//클라이언트 요청을 읽고 메아리로 돌려줌
void ClientSocket::readClient(){
    //텍스트 스트림 생성
    QTextStream in(this);
    QString strRead;

    while(true){
        if(this->canReadLine()){
            strRead = this->readLine();
             break;
        }
    }

    //개행문자 삭제
    strRead = strRead.left(strRead.length()-1);

    strRead.append(" by Server\n");

    QTextStream out(this);
    out<<strRead;
}
