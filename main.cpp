#include "LoginDialog.h"
#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // 创建并显示登录窗口
    LoginDialog loginDialog;
    if (loginDialog.exec() == QDialog::Accepted) {
        // 登录成功后执行的逻辑
        QMessageBox::information(nullptr, "登录成功", "欢迎进入系统！");
    } else {
        // 登录失败
        QMessageBox::warning(nullptr, "登录失败", "登录失败，请检查用户名或密码");
    }
    MainWindow w;
    w.show();
    return a.exec();
}
