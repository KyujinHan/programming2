#ifndef RECORDPLAN_H
#define RECORDPLAN_H

#include <QDialog>
#include <QtSql>
#include <QtDebug>
#include <QFileInfo>
#include "category_menu.h"

using namespace std;

namespace Ui {
class Recordplan;
}

class Recordplan : public QDialog
{
    Q_OBJECT

public:

    explicit Recordplan(QWidget *parent = nullptr);
    ~Recordplan();

private slots:
    void on_go_secpage_clicked();

    void on_save_btn_clicked();

    void on_expense_btn_clicked();

    void on_income_btn_clicked();

    void on_remove_money_clicked();

    void change_save_btn();

    void on_go_category_menu_clicked();

    QString feb_day(QString year);


private:
    Ui::Recordplan *ui;

    // Database
    QSqlDatabase mydb;
    category_menu *category;
};

#endif // RECORDPLAN_H
