#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QNetworkAccessManager>

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = nullptr);
    ~LoginDialog();

private slots:
    void onLoginClicked();        // 登录按钮点击槽
    void onRegisterClicked();     // 注册按钮点击槽
    void onNetworkReply(QNetworkReply *reply);  // 网络请求完成槽

private:
    // 界面元素
    QLineEdit *usernameEdit;      // 用户名输入框
    QLineEdit *passwordEdit;      // 密码输入框
    QPushButton *loginButton;     // 登录按钮
    QPushButton *registerButton;  // 注册按钮
    QLabel *errorLabel;           // 错误提示标签

    QNetworkAccessManager *manager;  // 网络管理器，用于发送 HTTP 请求
};

#endif // LOGINDIALOG_H
