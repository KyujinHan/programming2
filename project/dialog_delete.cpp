#include "dialog_delete.h"
#include "ui_dialog_delete.h"
#include "secmainwindow.h"

bool yes = false;
bool no = false;

Dialog_delete::Dialog_delete(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_delete)
{
    ui->setupUi(this);
    QPixmap pix(":/images/delete_content.png");

    QSqlQuery qry;
    QString username;
    // i) first find user name
    qry.exec("SELECT user_name FROM userTable WHERE implement='Y'");
    qry.next(); // only 1 row
    //qDebug() << qry.value(0); // ex) QVariant(QString, "kyujin")
    username = qry.value(0).toString();

    qry.exec("UPDATE userTable SET delete_flag='F' WHERE user_name= '"+username+"'");

}

Dialog_delete::~Dialog_delete()
{
    delete ui;
}

void Dialog_delete::on_yes_btn_clicked()
{
    ui -> yes_btn -> setStyleSheet("background-color:rgb(0,255,0); font: 700 14pt '맑은 고딕'; color: rgb(0,0,0); border: 2px solid rgb(0,255,0); border-radius: 5px;");
    ui -> no_btn -> setStyleSheet("background-color:rgb(255,255,255); font: 700 14pt '맑은 고딕'; color: rgb(0,0,0); border: 2px solid rgb(0,0,0); border-radius: 5px;");

    if (yes==false){
        yes=true;
        no=false;
    } else {
        QSqlQuery qry;
        QString username;
        // i) first find user name
        qry.exec("SELECT user_name FROM userTable WHERE implement='Y'");
        qry.next(); // only 1 row
        //qDebug() << qry.value(0); // ex) QVariant(QString, "kyujin")
        username = qry.value(0).toString();

        qry.exec("UPDATE userTable SET delete_flag='Y' WHERE user_name= '"+username+"'");
        yes=false;
        hide();
    }



}


void Dialog_delete::on_no_btn_clicked()
{
    ui -> yes_btn -> setStyleSheet("background-color:rgb(255,255,255); font: 700 14pt '맑은 고딕'; color: rgb(0,0,0); border: 2px solid rgb(0,0,0); border-radius: 5px;");
    ui -> no_btn -> setStyleSheet("background-color:rgb(0,255,0); font: 700 14pt '맑은 고딕'; color: rgb(0,0,0); border: 2px solid rgb(0,255,0); border-radius: 5px;");

    if (no==false){
        no=true;
        yes=false;
    } else {
        QSqlQuery qry;
        QString username;
        // i) first find user name
        qry.exec("SELECT user_name FROM userTable WHERE implement='Y'");
        qry.next(); // only 1 row
        //qDebug() << qry.value(0); // ex) QVariant(QString, "kyujin")
        username = qry.value(0).toString();

        qry.exec("UPDATE userTable SET delete_flag='F' WHERE user_name= '"+username+"'");
        no=false;
        hide();
    }

}

