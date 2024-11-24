#ifndef SERVERCHATWINDOW_H
#define SERVERCHATWINDOW_H

#include <QWidget>
#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>
#include <QKeyEvent>

QT_BEGIN_NAMESPACE
namespace Ui {
class ServerChatWindow;
}
QT_END_NAMESPACE

class ServerChatWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ServerChatWindow(QWidget *parent = nullptr);
    ~ServerChatWindow();
    void appendMessage(const QString &message);
    void keyPressEvent(QKeyEvent *event) override;

signals:
    void sendMessageToClient(const QString &message);

private slots:
    void onSendButtonClicked();

private:
    Ui::ServerChatWindow *ui;
    QTextEdit *chatBox;
    QLineEdit *inputBox;
    QPushButton *sendButton;
};

#endif // SERVERCHATWINDOW_H
