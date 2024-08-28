#include "server.h"

server::server() {}

server::~server(){}

void server::startServer()
{
    if(this->listen(QHostAddress::Any,5555))
    {
        qDebug() << "Listening";
        db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName("D:\\workers.db");
        if (db.open())
        {
            qDebug() << "Db open";
        } else
        {
            qDebug() << "DB not open";
        }
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
    if(docError.errorString() == "no error occurred")
    {
        sendData();
    }
}

void server::sockDisc(){
    qDebug() << "Disconnect";
    socket->deleteLater();
}

void server::sendData()
{
    doc = QJsonDocument::fromJson(Data, &docError);
    if ((doc.object().value("type").toString() == "select") &&
        (doc.object().value("params").toString() == "workers"))
    {
        if (db.isOpen())
        {
            QByteArray itog = "{\"type\":\"resultSelect\",\"result\":[";

            QSqlQuery *query = new QSqlQuery(db);
            if (query->exec("SELECT name FROM listworkers"))
            {
                while (query->next())
                {
                    itog.append("{\"name\":\"" + query->value(0).toString()+"\"},");
                }
                itog.remove(itog.length() - 1, 1);
                itog.append("]}");

                socket->write(itog);
                socket->waitForBytesWritten(500);
            } else
            {
                qDebug() << "Query not success.";
            }
        }
    }
}
