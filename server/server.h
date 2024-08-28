#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QFile>
#include <QSqlDatabase>
#include <QSqlQuery>

class server: public QTcpServer
{
    Q_OBJECT
public:
    server();
    ~server();
    void sendData();
public slots:
    void startServer();
    void incomingConnection(qintptr socketDescriptor);
    void sockReady();
    void sockDisc();
private:
    QTcpSocket* socket;
    QByteArray Data;
    QJsonDocument doc;
    QJsonParseError docError;
    QSqlDatabase db;
    QByteArray itog;
};

#endif // SERVER_H
