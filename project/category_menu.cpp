#include "category_menu.h"
#include "ui_category_menu.h"
#include "recordplan.h"

int currentnum;

category_menu::category_menu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::category_menu)
{
    ui->setupUi(this);
    QPixmap pix(":/images/category_page.png");
    ui->category_pic->setPixmap(pix.scaled(375,812));
}

category_menu::~category_menu()
{
    delete ui;
}


void check_category(int currentnum){
    // record database
    QSqlQuery qry;
    QString username;
    // i) first find user name
    qry.exec("SELECT user_name FROM userTable WHERE implement='Y'");
    qry.next(); // only 1 orw
    //qDebug() << qry.value(0); // ex) QVariant(QString, "kyujin")
    username = qry.value(0).toString();

    QString field_num;
    field_num = QString::number(currentnum);

    // ii) update
    qry.exec("UPDATE userTable SET field_num="+field_num+" WHERE user_name= '"+username+"'");
}


void category_menu::on_go_recordpage_clicked()
{
    currentnum = 99;
    check_category(currentnum);

    hide();
    Recordplan *recordplan;
    recordplan = new Recordplan(this);
    recordplan->show();
}


void category_menu::on_meal_btn_clicked()
{
    ui -> meal_btn -> setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.0)");
    ui -> snack_btn -> setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.3)");
    ui -> medicine_btn -> setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.3)");
    ui -> car_btn -> setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.3)");
    ui -> trans_btn -> setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.3)");
    ui -> edu_btn -> setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.3)");
    ui -> live_btn -> setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.3)");
    ui -> travel_btn -> setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.3)");
    ui -> daily_btn -> setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.3)");
    ui -> exer_btn -> setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.3)");
    ui -> cloth_btn -> setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.3)");
    ui -> beauty_btn -> setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.3)");

    currentnum = 0;
    check_category(currentnum);
}


void category_menu::on_snack_btn_clicked()
{
    ui -> meal_btn -> setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.3)");
    ui -> snack_btn -> setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.0)");
    ui -> medicine_btn -> setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.3)");
    ui -> car_btn -> setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.3)");
    ui -> trans_btn -> setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.3)");
    ui -> edu_btn -> setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.3)");
    ui -> live_btn -> setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.3)");
    ui -> travel_btn -> setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.3)");
    ui -> daily_btn -> setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.3)");
    ui -> exer_btn -> setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.3)");
    ui -> cloth_btn -> setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.3)");
    ui -> beauty_btn -> setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.3)");

    currentnum = 1;
    check_category(currentnum);
}


void category_menu::on_medicine_btn_clicked()
{
    ui -> meal_btn -> setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.3)");
    ui -> snack_btn -> setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.3)");
    ui -> medicine_btn -> setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.0)");
    ui -> car_btn -> setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.3)");
    ui -> trans_btn -> setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.3)");
    ui -> edu_btn -> setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.3)");
    ui -> live_btn -> setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.3)");
    ui -> travel_btn -> setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.3)");
    ui -> daily_btn -> setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.3)");
    ui -> exer_btn -> setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.3)");
    ui -> cloth_btn -> setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.3)");
    ui -> beauty_btn -> setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.3)");

    currentnum = 2;
    check_category(currentnum);
}


void category_menu::on_car_btn_clicked()
{
    ui -> meal_btn -> setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.3)");
    ui -> snack_btn -> setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.3)");
    ui -> medicine_btn -> setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.3)");
    ui -> car_btn -> setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.0)");
    ui -> trans_btn -> setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.3)");
    ui -> edu_btn -> setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.3)");
    ui -> live_btn -> setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.3)");
    ui -> travel_btn -> setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.3)");
    ui -> daily_btn -> setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.3)");
    ui -> exer_btn -> setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.3)");
    ui -> cloth_btn -> setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.3)");
    ui -> beauty_btn -> setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.3)");

    currentnum = 3;
    check_category(currentnum);
}


void category_menu::on_trans_btn_clicked()
{
    ui -> meal_btn -> setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.3)");
    ui -> snack_btn -> setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.3)");
    ui -> medicine_btn -> setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.3)");
    ui -> car_btn -> setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.3)");
    ui -> trans_btn -> setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.0)");
    ui -> edu_btn -> setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.3)");
    ui -> live_btn -> setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.3)");
    ui -> travel_btn -> setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.3)");
    ui -> daily_btn -> setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.3)");
    ui -> exer_btn -> setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.3)");
    ui -> cloth_btn -> setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.3)");
    ui -> beauty_btn -> setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.3)");

    currentnum = 4;
    check_category(currentnum);
}


void category_menu::on_edu_btn_clicked()
{
    ui -> meal_btn -> setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.3)");
    ui -> snack_btn -> setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.3)");
    ui -> medicine_btn -> setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.3)");
    ui -> car_btn -> setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.3)");
    ui -> trans_btn -> setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.3)");
    ui -> edu_btn -> setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.0)");
    ui -> live_btn -> setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.3)");
    ui -> travel_btn -> setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.3)");
    ui -> daily_btn -> setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.3)");
    ui -> exer_btn -> setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.3)");
    ui -> cloth_btn -> setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.3)");
    ui -> beauty_btn -> setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.3)");

    currentnum = 5;
    check_category(currentnum);
}


void category_menu::on_live_btn_clicked()
{
    ui -> meal_btn -> setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.3)");
    ui -> snack_btn -> setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.3)");
    ui -> medicine_btn -> setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.3)");
    ui -> car_btn -> setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.3)");
    ui -> trans_btn -> setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.3)");
    ui -> edu_btn -> setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.3)");
    ui -> live_btn -> setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.0)");
    ui -> travel_btn -> setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.3)");
    ui -> daily_btn -> setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.3)");
    ui -> exer_btn -> setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.3)");
    ui -> cloth_btn -> setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.3)");
    ui -> beauty_btn -> setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.3)");

    currentnum = 6;
    check_category(currentnum);
}


void category_menu::on_travel_btn_clicked()
{
    ui -> meal_btn -> setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.3)");
    ui -> snack_btn -> setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.3)");
    ui -> medicine_btn -> setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.3)");
    ui -> car_btn -> setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.3)");
    ui -> trans_btn -> setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.3)");
    ui -> edu_btn -> setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.3)");
    ui -> live_btn -> setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.3)");
    ui -> travel_btn -> setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.0)");
    ui -> daily_btn -> setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.3)");
    ui -> exer_btn -> setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.3)");
    ui -> cloth_btn -> setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.3)");
    ui -> beauty_btn -> setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.3)");

    currentnum = 7;
    check_category(currentnum);
}


void category_menu::on_daily_btn_clicked()
{
    ui -> meal_btn -> setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.3)");
    ui -> snack_btn -> setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.3)");
    ui -> medicine_btn -> setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.3)");
    ui -> car_btn -> setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.3)");
    ui -> trans_btn -> setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.3)");
    ui -> edu_btn -> setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.3)");
    ui -> live_btn -> setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.3)");
    ui -> travel_btn -> setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.3)");
    ui -> daily_btn -> setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.0)");
    ui -> exer_btn -> setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.3)");
    ui -> cloth_btn -> setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.3)");
    ui -> beauty_btn -> setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.3)");

    currentnum = 8;
    check_category(currentnum);
}


void category_menu::on_exer_btn_clicked()
{
    ui -> meal_btn -> setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.3)");
    ui -> snack_btn -> setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.3)");
    ui -> medicine_btn -> setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.3)");
    ui -> car_btn -> setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.3)");
    ui -> trans_btn -> setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.3)");
    ui -> edu_btn -> setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.3)");
    ui -> live_btn -> setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.3)");
    ui -> travel_btn -> setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.3)");
    ui -> daily_btn -> setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.3)");
    ui -> exer_btn -> setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.0)");
    ui -> cloth_btn -> setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.3)");
    ui -> beauty_btn -> setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.3)");

    currentnum = 9;
    check_category(currentnum);
}


void category_menu::on_cloth_btn_clicked()
{
    ui -> meal_btn -> setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.3)");
    ui -> snack_btn -> setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.3)");
    ui -> medicine_btn -> setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.3)");
    ui -> car_btn -> setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.3)");
    ui -> trans_btn -> setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.3)");
    ui -> edu_btn -> setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.3)");
    ui -> live_btn -> setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.3)");
    ui -> travel_btn -> setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.3)");
    ui -> daily_btn -> setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.3)");
    ui -> exer_btn -> setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.3)");
    ui -> cloth_btn -> setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.0)");
    ui -> beauty_btn -> setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.3)");

    currentnum = 10;
    check_category(currentnum);
}


void category_menu::on_beauty_btn_clicked()
{
    ui -> meal_btn -> setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.3)");
    ui -> snack_btn -> setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.3)");
    ui -> medicine_btn -> setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.3)");
    ui -> car_btn -> setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.3)");
    ui -> trans_btn -> setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.3)");
    ui -> edu_btn -> setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.3)");
    ui -> live_btn -> setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.3)");
    ui -> travel_btn -> setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.3)");
    ui -> daily_btn -> setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.3)");
    ui -> exer_btn -> setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.3)");
    ui -> cloth_btn -> setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.3)");
    ui -> beauty_btn -> setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.0)");

    currentnum = 11;
    check_category(currentnum);
}


void category_menu::on_selete_btn_clicked()
{
    hide();
    Recordplan *record_page;
    record_page = new Recordplan(this);
    record_page->show();
}

