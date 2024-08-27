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

    socket->write("{\"type\":\"connect\",\"status\":\"yes\"}");
    qDebug() << "Send client status connection - YES";
}

void server::sockReady()
{
    Data = socket->readAll();
    qDebug() << "Data" << Data;
    doc = QJsonDocument::fromJson(Data, &docError);

    if(docError.errorString() == "no error occurred")
    {
        if ((doc.object().value("type").toString() == "select") &&
            (doc.object().value("params").toString() == "workers"))
        {
            QFile file;
            file.setFileName("C:\\Projects qt\\clientserverapp\\clientserverapp\\workers.json");
            if (file.open(QIODevice::ReadOnly | QFile::Text))
            {
                QByteArray fromFile = file.readAll();
                QByteArray itog = "{\"type\":\"resultSelect\",\"result\":" + fromFile+"}";

                socket->write(itog);
                socket->waitForBytesWritten(500);
            }
            file.close();
        }
    }
}

void server::sockDisc(){
    qDebug() << "Disconnect";
    socket->deleteLater();
}
