#include "serverchatwindow.h"
#include "ui_serverchatwindow.h"

ServerChatWindow::ServerChatWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ServerChatWindow)
{
    ui->setupUi(this);
    chatBox = new QTextEdit(this);
    chatBox->setReadOnly(true);  // 设置为只读，用户不能编辑
    chatBox->setGeometry(10, 10, 400, 250);  // 设置聊天框的位置和大小

    // 初始化输入框
    inputBox = new QLineEdit(this);
    inputBox->setGeometry(10, 270, 300, 30);  // 设置输入框的位置和大小

    // 初始化发送按钮
    sendButton = new QPushButton("发送", this);
    sendButton->setGeometry(320, 270, 90, 30);  // 设置发送按钮的位置和大小

    connect(sendButton,&QPushButton::clicked,this,&ServerChatWindow::onSendButtonClicked);
}

ServerChatWindow::~ServerChatWindow()
{
    delete ui;
}

void ServerChatWindow::onSendButtonClicked(){
    QString message = inputBox->text();
    if(!message.isEmpty()){
        chatBox->append("服务器: " + message);  // 显示发送的消息

        emit sendMessageToClient(message);

        inputBox->clear();  // 清空输入框
    }
}

void ServerChatWindow::appendMessage(const QString &message){
    chatBox->append("客户端: " + message);
}

void ServerChatWindow::keyPressEvent(QKeyEvent *event){
    if(event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return) {
        onSendButtonClicked();
    } else {
        QWidget::keyPressEvent(event); // 调用基类处理其他按键事件
    }
}
