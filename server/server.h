#ifndef SERVER_H
#define SERVER_H

#include<QTcpServer>
#include<QTcpSocket>

class server: public QTcpServer
{
    Q_OBJECT
public:
    server();
    ~server();
public slots:
    void startServer();
    void incomingConnection(qintptr socketDescriptor);
    void sockReady();
    void sockDisc();
private:
    QTcpSocket* socket;
    QByteArray Data;
};

#endif // SERVER_H
