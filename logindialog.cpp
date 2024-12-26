#include "LoginDialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>

LoginDialog::LoginDialog(QWidget *parent) : QDialog(parent)
{
    // 创建界面元素
    usernameEdit = new QLineEdit(this);
    usernameEdit->setPlaceholderText("用户名");

    passwordEdit = new QLineEdit(this);
    passwordEdit->setEchoMode(QLineEdit::Password);  // 密码框
    passwordEdit->setPlaceholderText("密码");

    loginButton = new QPushButton("登录", this);
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
    mainLayout->addWidget(errorLabel);

    // 连接信号与槽
    connect(loginButton, &QPushButton::clicked, this, &LoginDialog::onLoginClicked);
}

LoginDialog::~LoginDialog()
{
}

void LoginDialog::onLoginClicked()
{
    // 获取用户名和密码
    QString username = usernameEdit->text();
    QString password = passwordEdit->text();

    // 假设的登录验证
    if (username == "admin" && password == "123456") {
        accept();  // 登录成功，关闭对话框
    } else {
        errorLabel->setText("用户名或密码错误");
        errorLabel->setStyleSheet("color: red;");  // 设置错误提示的颜色
    }
}
