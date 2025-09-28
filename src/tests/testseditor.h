#ifndef TESTSEDITOR_H
#define TESTSEDITOR_H

#include <QDialog>

namespace Ui {
class TestsEditor;
}

class TestsEditor : public QDialog
{
    Q_OBJECT

public:
    explicit TestsEditor(QWidget *parent = nullptr);
    ~TestsEditor();

private:
    Ui::TestsEditor *ui;
};

#endif // TESTSEDITOR_H
