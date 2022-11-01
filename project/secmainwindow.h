#ifndef SECMAINWINDOW_H
#define SECMAINWINDOW_H

#include <QDialog>
#include "summary.h"
#include "recordplan.h"

namespace Ui {
class Secmainwindow;
}

class Secmainwindow : public QDialog
{
    Q_OBJECT

public:
    explicit Secmainwindow(QWidget *parent = nullptr);
    ~Secmainwindow();

private slots:
    void on_go_summary_clicked();

    void on_go_adding_clicked();

    void set_frame();

private:
    Ui::Secmainwindow *ui;
    summary *summary_page;
    Recordplan *record_page;
};

#endif // SECMAINWINDOW_H
