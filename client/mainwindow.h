#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QMessageBox>
#include <QDebug>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QStandardItem>
#include <QJsonArray>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void sockReady();
    void sockDisc();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
    QTcpSocket *socket;
    QByteArray Data;
    QJsonDocument doc;
    QJsonParseError docError;
    int requireSize;
    bool complexData = false;
};
#endif // MAINWINDOW_H
