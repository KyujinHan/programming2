#include "secmainwindow.h"
#include "ui_secmainwindow.h"
#include "secmainwindow.h"
#include <QLineEdit>
#include <iostream>
#include <string>
#include <array>
#include <vector>

// minus btn
bool minus_flag = false;
int g_count = 0;
int month = QDate::currentDate().month();
vector<int> order_arr; // SAVE order num in vector

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

    // re-ordering
    qry.exec("ALTER TABLE projectDB AUTO_INCREMENT=1");

    // set text(?)
    qry.exec("UPDATE userTable SET money='Write money' WHERE user_name= '"+username+"'");
    qry.exec("UPDATE userTable SET title='Add title' WHERE user_name= '"+username+"'");

    // make frame(?)
    set_frame(month);

    // set text
    QString month_text;
    if(month==1){
        month_text = "January";
    } else if(month == 2){
        month_text = "February";
    } else if(month == 3){
        month_text = "March";
    } else if(month == 4){
        month_text = "April";
    } else if(month == 5){
        month_text = "May";
    } else if(month == 6){
        month_text = "June";
    } else if(month == 7){
        month_text = "July";
    } else if(month == 8){
        month_text = "August";
    } else if(month == 9){
        month_text = "September";
    } else if(month == 10){
        month_text = "October";
    } else if(month == 11){
        month_text = "November";
    } else if(month == 12){
        month_text = "December";
    }
    ui -> month_line -> setText(month_text);

    // income
    QString income_text;
    int income = 0;
    qry.exec("SELECT money FROM projectDB WHERE user_name='"+username+"' and month="+QString::number(month)+" and money_type='income'");
    while(qry.next()){
        income += qry.value(0).toInt();
    }
    income_text = QString::number(income);
    ui -> income_line -> setText(income_text+"₩");

    // expense
    QString expense_text;
    int expense = 0;
    qry.exec("SELECT money FROM projectDB WHERE user_name='"+username+"' and month="+QString::number(month)+" and money_type='expense'");
    while(qry.next()){
        expense += qry.value(0).toInt();
    }
    expense_text = QString::number(expense);
    ui -> expense_line -> setText(expense_text+"₩");



}

Secmainwindow::~Secmainwindow()
{
    delete ui;
}


void Secmainwindow::handleButton(){

    //qDebug() << "hi";

    // default: find user name
    QSqlQuery qry;
    QString username,order;
    qry.exec("SELECT user_name FROM userTable WHERE implement='Y'");
    qry.next(); // only 1 orw
    username = qry.value(0).toString();

    order = QString::number(order_arr.front());
    qDebug() << order;

    // If click btn, remove data.
    if(!(qry.exec("DELETE FROM projectDB WHERE user_name='"+username+"' and order_num="+order+""))){
        qDebug() << qry.lastError().text();
    }


    // refresh
    hide();
    Secmainwindow *new_page;
    new_page= new Secmainwindow(this);
    new_page->show();

}


void Secmainwindow::set_frame(int month){

    // make frame based on database

    // default: find user name
    QSqlQuery qry;
    QString username;
    qry.exec("SELECT user_name FROM userTable WHERE implement='Y'");
    qry.next(); // only 1 orw
    username = qry.value(0).toString();

    // i) count variable & ii) sorting
    qry.exec("SELECT * FROM projectDB WHERE user_name='"+username+"' and month="+QString::number(month)+" ORDER BY year DESC, month DESC, day DESC");

    /*
    // some example
    qry.next();
    qry.next();
    qry.next();
    qDebug() << qry.value(1).toString(); // cafe
    */

    // iii) print
    // green: expense & black: income
    int count = 0;
    // reset vector
    while (!order_arr.empty()) {
        order_arr.pop_back();
    }

    while(qry.next()){ // check person (we expected 1)
        int i = 62*(count);
        QString category, title, money_type, method, money, year, month, day, order;
        QLabel *label = new QLabel(this);
        category = qry.value(1).toString();
        title = qry.value(6).toString();
        money_type = qry.value(8).toString();
        method = qry.value(7).toString();
        money = qry.value(2).toString();
        year = qry.value(3).toString();
        month = qry.value(4).toString();
        day = qry.value(5).toString();
        order = qry.value(9).toString();

        if(category=="Café/Snack"){
            category = "Snack";
        }
        QPixmap pix(":/images/"+category+".png");
        label->setPixmap(pix.scaled(40,40));
        label->setGeometry(23, 395+i, 41, 48);

        QPixmap pix_delete(":/images/minus_btn.png");
        QPushButton *btn = new QPushButton(this);
        QLabel *label_sec = new QLabel(this);
        label_sec->setPixmap(pix_delete.scaled(15,15));
        label_sec->setStyleSheet("background-color:rgba(255,255,255,0);"); // no-background
        label_sec->setGeometry(20, 397+i, 15, 15);
        label_sec->hide(); // u=initial hide
        label_sec->setObjectName("minus_label_"+order);

        //QPushButton *btn;
        /*
        //QString text_btn = "minus_btn_"+QString::number(order_arr[i]);
        minus_btn = findChild<QPushButton*>("minus_btn_"+QString::number(count+1));
        qDebug() << minus_btn -> objectName();
        minus_btn->setObjectName("minus_btn_"+order); // rename
        minus_btn->hide();
        //minus_btn->setEnabled(false);
        qDebug() << minus_btn -> objectName();
        order_arr.push_back(order.toInt()); // save order num
        */
        btn->setStyleSheet("border: 5px; background-color:rgba(255,255,255,0.0)");
        btn->setGeometry(20, 397+i, 15, 15);
        btn->hide(); // hide
        btn->setObjectName("minus_btn_"+order);
        // Connect button signal to appropriate slot
        order_arr.push_back(order.toInt()); // save order num
        connect(btn, &QPushButton::released, this, &Secmainwindow::handleButton);
        btn->setCursor(Qt::OpenHandCursor);
        btn->setEnabled(false); // not using this time
        //qDebug() << label_sec -> objectName(); // minus_label

        QLineEdit *text_title = new QLineEdit(this);
        text_title->setText(title);
        text_title->setGeometry(72, 395+i, 171, 30);
        text_title->setStyleSheet("font: 700 9pt '맑은 고딕'; color: rgb(0, 0, 0); background-color: rgb(255, 255, 255); border: 0px");
        text_title->setReadOnly(true);

        QLineEdit *text_info = new QLineEdit(this);
        text_info->setText(category + " | " + method);
        text_info->setGeometry(72, 415+i, 171, 24);
        text_info->setStyleSheet("font: 700 7pt '맑은 고딕'; color: rgb(165, 165, 165); background-color: rgb(255, 255, 255); border: 0px");
        text_info->setReadOnly(true);

        QLineEdit *text_day = new QLineEdit(this);
        text_day->setText(month + "/" + day + "/" + year);
        text_day->setGeometry(252, 415+i, 101, 24);
        text_day->setStyleSheet("font: 700 7pt '맑은 고딕'; color: rgb(165, 165, 165); background-color: rgb(255, 255, 255); border: 0px");
        text_day->setAlignment(Qt::AlignRight);
        text_day->setReadOnly(true);

        QLineEdit *text_money = new QLineEdit(this);
        text_money->setGeometry(252, 395+i, 101, 24);
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
    g_count = count; // save
    //qDebug() << g_count;
}


void Secmainwindow::on_go_summary_clicked()
{
    hide();
    summary_page = new summary(this);
    summary_page->show();
}


void Secmainwindow::on_go_adding_clicked()
{
    ui -> go_adding -> setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.0)");

    hide();
    record_page = new Recordplan(this);
    record_page -> show(); // record page moving
}

// check edit or no-edit
void Secmainwindow::on_edit_btn_clicked()
{

    if(minus_flag==false){
        ui -> edit_btn -> setStyleSheet("background-color:rgb(255,255,255); font: 700 11pt '맑은 고딕'; color: rgb(255,0,0); border: 0px;");
        minus_flag = true;
        //qDebug() << "red";

        // show minus btn
        QLabel *minus_label;
        QPushButton *minus_btn;
        for(int i=0; i<g_count; i++){
            QString text = "minus_label_"+QString::number(order_arr[i]);
            QString text_btn = "minus_btn_"+QString::number(order_arr[i]);
            qDebug() << QString::number(order_arr[i]);
            minus_label = findChild<QLabel*>(text);
            minus_btn = findChild<QPushButton*>(text_btn);
            //qDebug() << minus_btn -> objectName();
            minus_label->show();
            minus_btn->show();
            minus_btn->activateWindow();
            minus_btn->raise();
            //minus_btn->setStyleSheet("background-color:rgb(255,0,0);"); // checking

            minus_btn->setEnabled(true);
            //qDebug() << minus_btn -> objectName();
        }


    } else if(minus_flag==true){
        ui -> edit_btn -> setStyleSheet("background-color:rgb(255,255,255); font: 700 11pt '맑은 고딕'; color: rgb(0,255,0); border: 0px;");
        minus_flag = false;
        //qDebug() << "green";

        // hide minus btn
        QLabel *minus_label;
        QPushButton *minus_btn;
        //QPushButton *minus_btn;
        for(int i=0; i<g_count; i++){
            QString text = "minus_label_"+QString::number(order_arr[i]);
            QString text_btn = "minus_btn_"+QString::number(order_arr[i]);
            minus_label = findChild<QLabel*>(text);
            minus_btn = findChild<QPushButton*>(text_btn);
            minus_label->hide();
            minus_btn->hide();
            minus_btn->setEnabled(false);
        }
    }
}


void Secmainwindow::on_go_planning_clicked()
{
    hide();
    plan_page = new Planning(this);
    plan_page -> show(); // record page moving
}


void Secmainwindow::on_back_btn_clicked()
{
    // set month
    month -= 1;
    if(month == 0){
        month = 12;
    }
    set_frame(month);

    // record database
    QSqlQuery qry;
    QString username;
    // i) first find user name
    qry.exec("SELECT user_name FROM userTable WHERE implement='Y'");
    qry.next(); // only 1 orw
    //qDebug() << qry.value(0); // ex) QVariant(QString, "kyujin")
    username = qry.value(0).toString();

    // set text
    QString month_text;
    if(month==1){
        month_text = "January";
    } else if(month == 2){
        month_text = "February";
    } else if(month == 3){
        month_text = "March";
    } else if(month == 4){
        month_text = "April";
    } else if(month == 5){
        month_text = "May";
    } else if(month == 6){
        month_text = "June";
    } else if(month == 7){
        month_text = "July";
    } else if(month == 8){
        month_text = "August";
    } else if(month == 9){
        month_text = "September";
    } else if(month == 10){
        month_text = "October";
    } else if(month == 11){
        month_text = "November";
    } else if(month == 12){
        month_text = "December";
    }
    ui -> month_line -> setText(month_text);

    // income
    QString income_text;
    int income = 0;
    qry.exec("SELECT money FROM projectDB WHERE user_name='"+username+"' and month="+QString::number(month)+" and money_type='income'");
    while(qry.next()){
        income += qry.value(0).toInt();
    }
    income_text = QString::number(income);
    ui -> income_line -> setText(income_text+"₩");

    // expense
    QString expense_text;
    int expense = 0;
    qry.exec("SELECT money FROM projectDB WHERE user_name='"+username+"' and month="+QString::number(month)+" and money_type='expense'");
    while(qry.next()){
        expense += qry.value(0).toInt();
    }
    expense_text = QString::number(expense);
    ui -> expense_line -> setText(expense_text+"₩");

    ui -> widget -> update(); // refresing

    hide();
    Secmainwindow *new_page;
    new_page= new Secmainwindow(this);
    new_page->show();
}


void Secmainwindow::on_next_btn_clicked()
{
    month += 1;
    if(month == 13){
        month = 1;
    }
    set_frame(month);

    // record database
    QSqlQuery qry;
    QString username;
    // i) first find user name
    qry.exec("SELECT user_name FROM userTable WHERE implement='Y'");
    qry.next(); // only 1 orw
    //qDebug() << qry.value(0); // ex) QVariant(QString, "kyujin")
    username = qry.value(0).toString();

    // set text
    QString month_text;
    if(month==1){
        month_text = "January";
    } else if(month == 2){
        month_text = "February";
    } else if(month == 3){
        month_text = "March";
    } else if(month == 4){
        month_text = "April";
    } else if(month == 5){
        month_text = "May";
    } else if(month == 6){
        month_text = "June";
    } else if(month == 7){
        month_text = "July";
    } else if(month == 8){
        month_text = "August";
    } else if(month == 9){
        month_text = "September";
    } else if(month == 10){
        month_text = "October";
    } else if(month == 11){
        month_text = "November";
    } else if(month == 12){
        month_text = "December";
    }
    ui -> month_line -> setText(month_text);

    // income
    QString income_text;
    int income = 0;
    qry.exec("SELECT money FROM projectDB WHERE user_name='"+username+"' and month="+QString::number(month)+" and money_type='income'");
    while(qry.next()){
        income += qry.value(0).toInt();
    }
    income_text = QString::number(income);
    ui -> income_line -> setText(income_text+"₩");

    // expense
    QString expense_text;
    int expense = 0;
    qry.exec("SELECT money FROM projectDB WHERE user_name='"+username+"' and month="+QString::number(month)+" and money_type='expense'");
    while(qry.next()){
        expense += qry.value(0).toInt();
    }
    expense_text = QString::number(expense);
    ui -> expense_line -> setText(expense_text+"₩");

    hide();
    Secmainwindow *new_page;
    new_page= new Secmainwindow(this);
    new_page->show();
}

/*
void Secmainwindow::on_verticalScrollBar_sliderMoved(int position)
{
    ui -> secpage_pic -> setGeometry(0, 0-position, 375, 812);
}
*/


