#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>
#include "serverchatwindow.h"
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void handleNewConnection();
    void onReadyRead();
    void onSendMessageToClient(const QString &message);
    void onClientDisconnected();
    void on_connectButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Widget *ui;
    QTcpServer *server;
    QTcpSocket *socket;
    ServerChatWindow *chatWindow;
};
#endif // WIDGET_H
