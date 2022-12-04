#ifndef SECMAINWINDOW_H
#define SECMAINWINDOW_H

#include <QDialog>
#include "summary.h"
#include "recordplan.h"
#include "planning.h"
#include "dialog_delete.h"
#include <vector>

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

    //int month = QDate::currentDate().month();

    //int sec_month;

    //void handleButton(QString sec_order=0);

private slots:
    //int get_month();

    void on_go_summary_clicked();

    void on_go_adding_clicked();

    void set_frame(int month, int year);

    void on_edit_btn_clicked();

    void on_go_planning_clicked();

    void on_back_btn_clicked();

    void on_next_btn_clicked();

    void handleButton();

    void set_target();

    void on_verticalScrollBar_sliderMoved(int position);

    void check_coordinates();

private:
    vector<vector<int>> coordinates; // 2D vector

    Ui::Secmainwindow *ui;
    summary *summary_page;
    Recordplan *record_page;
    Planning *plan_page;
    Dialog_delete *dialog_delete;

    QString sec_order;
};

#endif // SECMAINWINDOW_H
