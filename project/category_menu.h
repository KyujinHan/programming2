#ifndef CATEGORY_MENU_H
#define CATEGORY_MENU_H

#include <QDialog>
#include <QtSql>
#include <QtDebug>
#include <QFileInfo>

namespace Ui {
class category_menu;
}

class category_menu : public QDialog
{
    Q_OBJECT

public:
    explicit category_menu(QWidget *parent = nullptr);
    ~category_menu();

private slots:
    void on_go_recordpage_clicked();

    void on_meal_btn_clicked();

    void on_snack_btn_clicked();

    void on_medicine_btn_clicked();

    void on_car_btn_clicked();

    void on_trans_btn_clicked();

    void on_edu_btn_clicked();

    void on_live_btn_clicked();

    void on_travel_btn_clicked();

    void on_daily_btn_clicked();

    void on_exer_btn_clicked();

    void on_cloth_btn_clicked();

    void on_beauty_btn_clicked();


    void on_selete_btn_clicked();

private:
    Ui::category_menu *ui;
    QSqlDatabase mydb;
};

#endif // CATEGORY_MENU_H
