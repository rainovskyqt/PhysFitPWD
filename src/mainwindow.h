#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QKeyEvent>
#include <QMainWindow>

class User;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(User* user, QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    User *m_user;

};
#endif // MAINWINDOW_H
