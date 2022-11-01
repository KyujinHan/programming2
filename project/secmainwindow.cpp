#include "secmainwindow.h"
#include "ui_secmainwindow.h"
#include "secmainwindow.h"

Secmainwindow::Secmainwindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Secmainwindow)
{
    ui->setupUi(this);
    QPixmap pix(":/images/mainpage_default.png");
    ui->secpage_pic->setPixmap(pix.scaled(375,812));

    // record database
    QSqlQuery qry;
    QString username;
    // i) first find user name
    qry.exec("SELECT user_name FROM userTable WHERE implement='Y'");
    qry.next(); // only 1 orw
    //qDebug() << qry.value(0); // ex) QVariant(QString, "kyujin")
    username = qry.value(0).toString();

    // recover
    qry.exec("UPDATE userTable SET field_num=99 WHERE user_name= '"+username+"'");


    // make frame(?)
    set_frame();

}

Secmainwindow::~Secmainwindow()
{
    delete ui;
}

void Secmainwindow::set_frame(){
    // make frame based on database

    // default: find user name
    QSqlQuery qry;
    QString username;
    qry.exec("SELECT user_name FROM userTable WHERE implement='Y'");
    qry.next(); // only 1 orw
    username = qry.value(0).toString();

    // i) count variable & ii) sorting
    qry.exec("SELECT * FROM projectDB WHERE user_name='"+username+"' ORDER BY year DESC, month DESC, day DESC");
    /*
    // some example
    qry.next();
    qry.next();
    qry.next();
    qDebug() << qry.value(1).toString(); // cafe
    */

    // iii) print
    // green: expense & black: income
    int count=0;
    while(qry.next()){ // check person (we expected 1)
        int i = 62*(count);
        QString category, title, money_type, method, money, year, month, day;
        QLabel *label = new QLabel(this);
        category = qry.value(1).toString();
        title = qry.value(6).toString();
        money_type = qry.value(8).toString();
        method = qry.value(7).toString();
        money = qry.value(2).toString();
        year = qry.value(3).toString();
        month = qry.value(4).toString();
        day = qry.value(5).toString();


        if(category=="Café/Snack"){
            category = "Snack";
        }
        QPixmap pix(":/images/"+category+".png");
        label->setPixmap(pix.scaled(40,40));
        label->setGeometry(23, 325+i, 41, 48);

        QLineEdit *text_title = new QLineEdit(this);
        text_title->setText(title);
        text_title->setGeometry(72, 325+i, 171, 30);
        text_title->setStyleSheet("font: 700 9pt '맑은 고딕'; color: rgb(0, 0, 0); background-color: rgb(255, 255, 255); border: 0px");
        text_title->setReadOnly(true);

        QLineEdit *text_info = new QLineEdit(this);
        text_info->setText(category + " | " + method);
        text_info->setGeometry(72, 345+i, 171, 24);
        text_info->setStyleSheet("font: 700 7pt '맑은 고딕'; color: rgb(165, 165, 165); background-color: rgb(255, 255, 255); border: 0px");
        text_info->setReadOnly(true);

        QLineEdit *text_day = new QLineEdit(this);
        text_day->setText(month + "/" + day + "/" + year);
        text_day->setGeometry(252, 345+i, 101, 24);
        text_day->setStyleSheet("font: 700 7pt '맑은 고딕'; color: rgb(165, 165, 165); background-color: rgb(255, 255, 255); border: 0px");
        text_day->setAlignment(Qt::AlignRight);
        text_day->setReadOnly(true);

        QLineEdit *text_money = new QLineEdit(this);
        text_money->setGeometry(252, 325+i, 101, 24);
        if (money_type=="income"){
            text_money->setText("+"+money+"₩");
            text_money->setStyleSheet("font: 700 12pt '맑은 고딕'; color: rgb(0, 0, 0); background-color: rgb(255, 255, 255); border: 0px");
        } else{
            text_money->setText("-"+money+"₩");
            text_money->setStyleSheet("font: 700 12pt '맑은 고딕'; color: rgb(0, 255, 0); background-color: rgb(255, 255, 255); border: 0px");
        }
        text_money->setAlignment(Qt::AlignRight);
        text_money->setReadOnly(true);

        count++;
    }
    //qDebug() << count;
}

void Secmainwindow::on_go_summary_clicked()
{
    hide();
    summary_page = new summary(this);
    summary_page->show();
}


void Secmainwindow::on_go_adding_clicked()
{
    hide();
    record_page = new Recordplan(this);
    record_page -> show(); // record page moving
}

