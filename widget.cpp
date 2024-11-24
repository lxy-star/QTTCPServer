#include "widget.h"
#include "./ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
    , chatWindow(nullptr)
    , server(new QTcpServer)
    , socket(nullptr)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
    delete server;
    if(socket){
        delete socket;
    }
    if (chatWindow) {
        delete chatWindow;
    }
}

void Widget::handleNewConnection(){
    socket = server->nextPendingConnection();
    // 连接读取数据的槽函数
    connect(socket, &QTcpSocket::readyRead, this, &Widget::onReadyRead);

    // 连接断开连接的槽函数
    connect(socket, &QTcpSocket::disconnected, this, &Widget::onClientDisconnected);

    if(!chatWindow){
        chatWindow = new ServerChatWindow(nullptr);
        chatWindow->show();
        connect(chatWindow,&ServerChatWindow::sendMessageToClient,this,&Widget::onSendMessageToClient);
    }
    // 关闭主窗口
    this->hide();
}

void Widget::onReadyRead() {
    QByteArray data = socket->readAll();
    QString message = QString::fromUtf8(data);

    if (chatWindow) {
        chatWindow->appendMessage(message);  // 显示接收到的消息
    }
}

void Widget::onSendMessageToClient(const QString &message){
    if (socket && socket->state() == QAbstractSocket::ConnectedState) {
        socket->write(message.toUtf8());
    }
}

void Widget::on_connectButton_clicked()
{
    QString host = ui->hostLineEdit->text();
    QString portStr = ui->portLineEdit->text();
    int port = portStr.toInt();
    QHostAddress address(host);
    server->listen(address,port);
    connect(server, &QTcpServer::newConnection, this, &Widget::handleNewConnection);
}

void Widget::on_pushButton_2_clicked()
{
    this->close();
}

void Widget::onClientDisconnected(){
    // 弹出消息框提示客户端已断开连接
    QMessageBox::information(this, "客户端断开连接", "客户端已断开连接");

    // 可以在这里进行一些清理工作，比如关闭socket
    if (socket) {
        socket->deleteLater(); // 安全地删除socket对象
        socket = nullptr;      // 将socket置为空指针，防止野指针
    }

    // 如果需要重新显示主窗口，可以取消注释以下行
    chatWindow->close();
    this->show();
}
