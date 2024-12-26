#include "LoginDialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QUrl>

LoginDialog::LoginDialog(QWidget *parent) : QDialog(parent), manager(new QNetworkAccessManager(this))
{
    // 创建界面元素
    usernameEdit = new QLineEdit(this);
    usernameEdit->setPlaceholderText("用户名");

    passwordEdit = new QLineEdit(this);
    passwordEdit->setEchoMode(QLineEdit::Password);  // 密码框
    passwordEdit->setPlaceholderText("密码");

    loginButton = new QPushButton("登录", this);
    registerButton = new QPushButton("注册", this);
    errorLabel = new QLabel("", this);

    // 布局
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QHBoxLayout *usernameLayout = new QHBoxLayout();
    QHBoxLayout *passwordLayout = new QHBoxLayout();

    usernameLayout->addWidget(new QLabel("用户名:"));
    usernameLayout->addWidget(usernameEdit);
    passwordLayout->addWidget(new QLabel("密码:"));
    passwordLayout->addWidget(passwordEdit);

    mainLayout->addLayout(usernameLayout);
    mainLayout->addLayout(passwordLayout);
    mainLayout->addWidget(loginButton);
    mainLayout->addWidget(registerButton);
    mainLayout->addWidget(errorLabel);

    // 连接信号与槽
    connect(loginButton, &QPushButton::clicked, this, &LoginDialog::onLoginClicked);
    connect(registerButton, &QPushButton::clicked, this, &LoginDialog::onRegisterClicked);

    // 连接网络请求槽
    connect(manager, &QNetworkAccessManager::finished, this, &LoginDialog::onNetworkReply);
}

LoginDialog::~LoginDialog()
{
    delete manager;
}

void LoginDialog::onLoginClicked()
{
    QString username = usernameEdit->text();
    QString password = passwordEdit->text();

    if (username.isEmpty() || password.isEmpty()) {
        errorLabel->setText("请输入用户名和密码");
        errorLabel->setStyleSheet("color: red;");
        return;
    }

    // 发送登录请求
    QUrl url("http://example.com/login");
    QNetworkRequest request(url);

    // 设置请求的内容类型
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    // 创建 JSON 数据
    QJsonObject json;
    json["username"] = username;
    json["password"] = password;
    QJsonDocument doc(json);

    // 发送 POST 请求
    manager->post(request, doc.toJson());
}

void LoginDialog::onRegisterClicked()
{
    // 这里可以弹出一个注册对话框或者直接发起注册请求
    // 暂时使用一个提示框表示注册逻辑
    QMessageBox::information(this, "注册", "注册功能未实现");
}

void LoginDialog::onNetworkReply(QNetworkReply *reply)
{
    if (reply->error() != QNetworkReply::NoError) {
        // 处理错误情况
        errorLabel->setText("无法连接到服务器");
        errorLabel->setStyleSheet("color: red;");
    } else {
        // 获取服务器响应
        QByteArray responseData = reply->readAll();
        QJsonDocument doc = QJsonDocument::fromJson(responseData);
        QJsonObject jsonResponse = doc.object();

        // 假设服务器返回 JSON 格式的数据，包含一个 "status" 字段
        QString status = jsonResponse["status"].toString();

        if (status == "success") {
            accept();  // 登录成功，关闭对话框
        } else {
            errorLabel->setText("用户名或密码错误");
            errorLabel->setStyleSheet("color: red;");
        }
    }

    reply->deleteLater();  // 释放回复对象
}
