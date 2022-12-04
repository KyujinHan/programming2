#ifndef DELETE_DIALOG_H
#define DELETE_DIALOG_H

#include <QDialog>

namespace Ui {
class delete_Dialog;
}

class delete_Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit delete_Dialog(QWidget *parent = nullptr);
    ~delete_Dialog();

private:
    Ui::delete_Dialog *ui;
};

#endif // DELETE_DIALOG_H
