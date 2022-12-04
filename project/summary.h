#ifndef SUMMARY_H
#define SUMMARY_H

#include <QDialog>

// summary page class
namespace Ui {
class summary;
}

class summary : public QDialog
{
    Q_OBJECT

public:
    explicit summary(QWidget *parent = nullptr);
    ~summary();

private slots:
    void on_go_secpage_clicked();

    void on_month_btn_clicked();

    void on_year_btn_clicked();

    void on_week_btn_clicked();

    void set_year_frame();

    void set_month_frame();

    void set_week_frame();

private:
    Ui::summary *ui;
    // Secmainwindow *secmain_page;
};


#endif // SUMMARY_H
