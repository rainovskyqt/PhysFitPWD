#ifndef MAINMENU_H
#define MAINMENU_H

#include <QMainWindow>

namespace Ui {
class MainMenu;
}

class MainMenu : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainMenu(QWidget *parent = nullptr);
    ~MainMenu();

private slots:
    void on_btn_examineeBase_clicked();

    void on_btn_dictionaries_clicked();

private:
    Ui::MainMenu *ui;
};

#endif // MAINMENU_H
