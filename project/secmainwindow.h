#ifndef SECMAINWINDOW_H
#define SECMAINWINDOW_H

#include <QDialog>
#include "summary.h"
#include "recordplan.h"
#include "planning.h"


class QLineEdit;

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

    void set_frame(int month);

    void on_edit_btn_clicked();

    void on_go_planning_clicked();

    void on_back_btn_clicked();

    void on_next_btn_clicked();

    //void on_verticalScrollBar_sliderMoved(int position);

    void handleButton();

private:
    Ui::Secmainwindow *ui;
    summary *summary_page;
    Recordplan *record_page;
    Planning *plan_page;
};

#endif // SECMAINWINDOW_H
