#include "server.h"

server::server() {}

server::~server(){}

void server::startServer(){
    if(this->listen(QHostAddress::Any,5555)){
        qDebug() << "Listening";
    } else{
        qDebug() << "Not Listening";
    }
}

void server::incomingConnection(qintptr socketDescriptor){
    socket = new QTcpSocket(this);
    socket->setSocketDescriptor(socketDescriptor);

    connect(socket,SIGNAL(readyRead()),this, SLOT(sockReady()));
    connect(socket,SIGNAL(disconnected()),this, SLOT(sockDisc()));

    qDebug() << socketDescriptor << "Client connected";

    socket->write("You are connected");
    qDebug() << "Send client status connection - YES";
}

void server::sockReady(){

}

void server::sockDisc(){
    qDebug() << "Disconnect";
    socket->deleteLater();
}
