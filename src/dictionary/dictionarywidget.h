#ifndef DICTIONARYWIDGET_H
#define DICTIONARYWIDGET_H

#include <QListWidgetItem>
#include <QWidget>

#include "dictionary/dictionary.h"

using T = Dictionary::Type;

namespace Ui {
class DictionaryWidget;
}

class DictionaryWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DictionaryWidget(QWidget *parent = nullptr);
    ~DictionaryWidget();
    void setDictionary(T type);

private slots:
    void on_btn_up_clicked();
    void on_btn_down_clicked();
    void on_btn_add_clicked();
    void on_btn_edit_clicked();
    void on_btn_delete_clicked();
    void on_lw_valuesList_itemDoubleClicked(QListWidgetItem *item);

private:
    Ui::DictionaryWidget *ui;

    T m_currentDictory;

    bool exists(QString name);
    void swapOrder(int row1, int row2, int current);
};

#endif // DICTIONARYWIDGET_H
