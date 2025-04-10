#include "formlogin.h"
#include "ui_formlogin.h"

#include <QKeyEvent>
#include <QMessageBox>

#include <QDebug>

#include "globalvals.h"
#include "mainmenu.h"

FormLogin::FormLogin(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FormLogin)
{
    ui->setupUi(this);
}

FormLogin::~FormLogin()
{
    delete ui;
}

void FormLogin::on_btn_close_clicked()
{
    this->close();
}

bool FormLogin::checkLogin(QString login, QString password)
{
    User *u = new User("login");
    GlobalVals::get()->setUser(u);
    return true;
}

void FormLogin::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) {
        on_btn_enter_clicked();
    } else {
        QWidget::keyPressEvent(event);
    }
}

void FormLogin::on_btn_enter_clicked()
{
    bool ok = checkLogin(ui->line_login->text().simplified().toLower(),
                           ui->line_password->text());

    if(ok){
        MainMenu *w = new MainMenu();
        w->show();
        this->close();
    } else {
        QMessageBox::critical(this, "Ошибка входа", "Не верные логин или пароль");
    }
}

