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
int year = QDate::currentDate().year();
int d_height = 812;
int s_height = 0;
vector<int> order_arr; // SAVE order num in vector

Secmainwindow::Secmainwindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Secmainwindow)
{
    ui->setupUi(this);
    QPixmap pix(":/images/secmainwindow.png");
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
    set_frame(month, year);
    qry.exec("UPDATE userTable SET set_month="+QString::number(month)+" WHERE user_name= '"+username+"'");
    qry.exec("UPDATE userTable SET set_year="+QString::number(year)+" WHERE user_name= '"+username+"'");



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

    QString year_text;
    year_text = QString::number(year);
    ui -> year -> setText(year_text);

    // income
    QString income_text;
    int income = 0;
    qry.exec("SELECT money FROM projectDB WHERE user_name='"+username+"' and month="+QString::number(month)+" and year="+QString::number(year)+" and money_type='income'");
    while(qry.next()){
        income += qry.value(0).toInt();
    }
    income_text = QString::number(income);
    ui -> income_line -> setText(income_text+"₩");

    // expense
    QString expense_text;
    int expense = 0;
    qry.exec("SELECT money FROM projectDB WHERE user_name='"+username+"' and month="+QString::number(month)+" and year="+QString::number(year)+" and money_type='expense'");
    while(qry.next()){
        expense += qry.value(0).toInt();
    }
    expense_text = QString::number(expense);
    ui -> expense_line -> setText(expense_text+"₩");

    set_target();

    // scroll setting
    s_height = (g_count*62)+445;
    if(s_height > 812){
        qDebug() << "high";
        ui->verticalScrollBar->setMaximum(s_height-812);
    } else {
        qDebug() << "low";
    }

    coordinates.resize(g_count, vector<int>(14)); // (x,14)
    check_coordinates();
}

Secmainwindow::~Secmainwindow()
{
    delete ui;
}

void Secmainwindow::check_coordinates()
{

    QLabel *minus_label;
    QPushButton *minus_btn;
    QLineEdit *text_title;
    QLineEdit *text_day;
    QLineEdit *text_info;
    QLineEdit *text_money;
    QLabel *label;

    for(int i=0; i<g_count; i++){
        QString text = "minus_label_"+QString::number(order_arr[i]);
        QString text_btn = "minus_btn_"+QString::number(order_arr[i]);
        QString title = "text_title_"+QString::number(order_arr[i]);
        QString day = "text_day_"+QString::number(order_arr[i]);
        QString info = "text_info_"+QString::number(order_arr[i]);
        QString money = "text_money_"+QString::number(order_arr[i]);
        QString label_text = "label_"+QString::number(order_arr[i]);

        minus_label = findChild<QLabel*>(text);
        int X0 = minus_label->geometry().x();
        int Y0 = minus_label->geometry().y();
        coordinates[i][0] = X0;
        coordinates[i][1] = Y0;
        //qDebug() << "check3";

        minus_btn = findChild<QPushButton*>(text_btn);
        int X1 = minus_btn->geometry().x();
        int Y1 = minus_btn->geometry().y();
        coordinates[i][2] = X1;
        coordinates[i][3] = Y1;

        text_title = findChild<QLineEdit*>(title);
        int X2 = text_title->geometry().x();
        int Y2 = text_title->geometry().y();
        coordinates[i][4] = X2;
        coordinates[i][5] = Y2;

        text_day = findChild<QLineEdit*>(day);
        int X3 = text_day->geometry().x();
        int Y3 = text_day->geometry().y();
        coordinates[i][6] = X3;
        coordinates[i][7] = Y3;

        text_info = findChild<QLineEdit*>(info);
        int X4 = text_info->geometry().x();
        int Y4 = text_info->geometry().y();
        coordinates[i][8] = X4;
        coordinates[i][9] = Y4;

        text_money = findChild<QLineEdit*>(money);
        int X5 = text_money->geometry().x();
        int Y5 = text_money->geometry().y();
        coordinates[i][10] = X5;
        coordinates[i][11] = Y5;

        label = findChild<QLabel*>(label_text);
        int X6 = label->geometry().x();
        int Y6 = label->geometry().y();
        coordinates[i][12] = X6;
        coordinates[i][13] = Y6;
    }
}

void Secmainwindow::set_target(){
    // default: find user name
    QSqlQuery qry;
    QString username;
    qry.exec("SELECT user_name FROM userTable WHERE implement='Y'");
    qry.next(); // only 1 orw
    username = qry.value(0).toString();

    // i) count variable & ii) sorting
    //qry.exec("SELECT * FROM projectDB WHERE user_name='"+username+"' and month="+QString::number(month)+" ORDER BY year DESC, month DESC, day DESC");
    //QString income;
    //income = ui -> income_line -> text();
    // expense
    QString expense_text;
    int expense = 0;
    int cur_month = QDate::currentDate().month();
    int cur_year = QDate::currentDate().year();
    qry.exec("SELECT money FROM projectDB WHERE user_name='"+username+"' and month="+QString::number(cur_month)+" and year="+QString::number(cur_year)+" and money_type='expense'");
    while(qry.next()){
        expense += qry.value(0).toInt();
    }
    expense_text = QString::number(expense);

    if(!(qry.exec("SELECT money FROM planning WHERE username='"+username+"' and month="+QString::number(cur_month)+" and year="+QString::number(cur_year)+" and money_type='expense'"))){
        ui -> target_line -> setText("Please make a spending plan");
        ui -> target_line_2 -> setText("for this month.");
    } else{
        QString target;
        int predict = 0;
        int result;
        while(qry.next()){
            predict += qry.value(0).toInt();
        }
        if(predict > expense_text.toInt()){
            result = predict - expense_text.toInt();
            qDebug() << result;
            qDebug() << expense_text;
            ui -> target_line_3 -> setText("You have");
            target = QString::number(result)+"₩ left to spend";
            ui -> target_line -> setText(target);
            ui -> target_line -> setStyleSheet("font: 700 13pt '맑은 고딕'; color: rgb(0, 255, 0); background-color: rgba(255, 255, 255, 0.0); border: 0px;");
            ui -> target_line_2 -> setText("from your spending plan.");
            ui -> target_line_2 -> setStyleSheet("font: 700 13pt '맑은 고딕'; color: rgb(255, 255, 255); background-color: rgba(255, 255, 255, 0.0); border: 0px;");
        } else {
            result = expense_text.toInt() - predict;
            ui -> target_line_3 -> setText("You have");
            ui -> target_line -> setText("exceeded the spending plan of");
            ui -> target_line -> setStyleSheet("font: 700 13pt '맑은 고딕'; color: rgb(255, 255, 255); background-color: rgba(255, 255, 255, 0.0); border: 0px;");
            target = "this month by "+QString::number(result)+"₩.";
            ui -> target_line_2 -> setText(target);
            ui -> target_line_2 -> setStyleSheet("font: 700 13pt '맑은 고딕'; color: rgb(0, 255, 0); background-color: rgba(255, 255, 255, 0.0); border: 0px;");

        }
    }
}

void Secmainwindow::handleButton(){

    //qDebug() << "hi";

    // default: find user name
    QSqlQuery qry;
    QString username, order;
    qry.exec("SELECT user_name FROM userTable WHERE implement='Y'");
    qry.next(); // only 1 orw
    username = qry.value(0).toString();

    // delete content
    dialog_delete = new Dialog_delete;
    dialog_delete->setModal(true);
    dialog_delete->exec();

    QPushButton* buttonSender = qobject_cast<QPushButton*>(sender());
    QString buttonText = buttonSender->objectName();
    order = buttonText.split("_").back();
    qDebug() << order;

    //order = QString::number(order_arr.front());
    //qDebug() << sec_order;

    // If click btn, remove data.
    qry.exec("SELECT delete_flag FROM userTable WHERE implement='Y'");
    qry.next();
    QString flag = qry.value(0).toString();
    if(flag=="Y"){
        if(!(qry.exec("DELETE FROM projectDB WHERE user_name='"+username+"' and order_num="+order+""))){
            qDebug() << order + "?";
            qDebug() << qry.lastError().text();
        }
    }

    // refresh
    hide();
    Secmainwindow *new_page;
    new_page= new Secmainwindow(this);
    new_page->show();

}


void Secmainwindow::set_frame(int month, int year){

    // make frame based on database

    // default: find user name
    QSqlQuery qry;
    QString username;
    qry.exec("SELECT user_name FROM userTable WHERE implement='Y'");
    qry.next(); // only 1 orw
    username = qry.value(0).toString();

    // i) count variable & ii) sorting
    qry.exec("SELECT * FROM projectDB WHERE user_name='"+username+"' and month="+QString::number(month)+" and year="+QString::number(year)+" ORDER BY year DESC, month DESC, day DESC");

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
        QString category, title, money_type, method, money, year, month, day, order, category_2;
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

        if(category=="Cafe/Snack"){
            category = "Snack";
        } else if ((category!="Meal") and (category != "Medicine") and (category!="Car") and (category!="Transportation") and (category!="Education") \
                and (category!="Living") and (category!="Travel") and (category!="Daily") and (category!="Exercise") and (category!="Clothes") and \
                (category!="Beauty")){
            category_2 = category;
            category = "Other";
        }

        QPixmap pix(":/images/"+category+".png");
        label->setPixmap(pix.scaled(40,40));
        label->setGeometry(23, 425+i, 41, 48);
        label->setObjectName("label_"+order);

        QPixmap pix_delete(":/images/minus_btn.png");
        QPushButton *btn = new QPushButton(this);
        QLabel *label_sec = new QLabel(this);
        label_sec->setPixmap(pix_delete.scaled(15,15));
        label_sec->setStyleSheet("background-color:rgba(255,255,255,0);"); // no-background
        label_sec->setGeometry(20, 425+i, 15, 15);
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
        btn->setGeometry(20, 425+i, 15, 15);
        btn->hide(); // hide
        btn->setObjectName("minus_btn_"+order);
        // Connect button signal to appropriate slot
        order_arr.push_back(order.toInt()); // save order num
        sec_order = order; // private

        QString text_btn = "minus_btn_"+order;
        QPushButton *minus_btn;
        minus_btn = findChild<QPushButton*>(text_btn);
        connect(minus_btn, &QPushButton::released, this, &Secmainwindow::handleButton);
        btn->setCursor(Qt::OpenHandCursor);
        btn->setEnabled(false); // not using this time
        //qDebug() << label_sec -> objectName(); // minus_label

        QLineEdit *text_title = new QLineEdit(this); // title
        text_title->setText(title + " | " + method);
        text_title->setGeometry(72, 445+i, 171, 24); //text_title->setGeometry(72, 423+i, 171, 30);
        text_title->setStyleSheet("font: 700 11pt '맑은 고딕'; color: rgb(165, 165, 165); background-color: rgb(255, 255, 255); border: 0px"); //setStyleSheet("font: 700 9pt '맑은 고딕'; color: rgb(0, 0, 0); background-color: rgb(255, 255, 255); border: 0px");
        text_title->setReadOnly(true);
        text_title->setObjectName("text_title_"+order);

        QLineEdit *text_info = new QLineEdit(this); // category
        if (category!="Other"){
            text_info->setText(category);
        } else {
            text_info->setText(category_2);
        }
        text_info->setGeometry(72, 423+i, 171, 30); //text_info->setGeometry(72, 443+i, 171, 24);
        text_info->setStyleSheet("font: 700 14pt '맑은 고딕'; color: rgb(0, 0, 0); background-color: rgb(255, 255, 255); border: 0px"); //setStyleSheet("font: 700 7pt '맑은 고딕'; color: rgb(165, 165, 165); background-color: rgb(255, 255, 255); border: 0px");
        text_info->setReadOnly(true);
        text_info->setObjectName("text_info_"+order);

        QLineEdit *text_day = new QLineEdit(this);
        text_day->setText(month + "/" + day + "/" + year);
        text_day->setGeometry(252, 445+i, 101, 24);
        text_day->setStyleSheet("font: 700 11pt '맑은 고딕'; color: rgb(165, 165, 165); background-color: rgb(255, 255, 255); border: 0px");
        text_day->setAlignment(Qt::AlignRight);
        text_day->setReadOnly(true);
        text_day->setObjectName("text_day_"+order);

        QLineEdit *text_money = new QLineEdit(this);
        text_money->setGeometry(252, 423+i, 101, 24);
        if (money_type=="income"){
            text_money->setText("+"+money+"₩");
            text_money->setStyleSheet("font: 700 14pt '맑은 고딕'; color: rgb(0, 255, 0); background-color: rgb(255, 255, 255); border: 0px");
        } else{
            text_money->setText("-"+money+"₩");
            text_money->setStyleSheet("font: 700 14pt '맑은 고딕'; color: rgb(0, 0, 0); background-color: rgb(255, 255, 255); border: 0px");
        }
        text_money->setAlignment(Qt::AlignRight);
        text_money->setReadOnly(true);
        text_money->setObjectName("text_money_"+order);

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
        ui -> edit_btn -> setStyleSheet("background-color:rgb(255,255,255); font: 700 14pt '맑은 고딕'; color: rgb(255,0,0); border: 0px;");
        ui -> edit_btn -> setText("Save");
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
        ui -> edit_btn -> setStyleSheet("background-color:rgb(255,255,255); font: 700 14pt '맑은 고딕'; color: rgb(0,255,0); border: 0px;");
        ui -> edit_btn -> setText("Edit");
        minus_flag = false;
        //qDebug() << "green";
        //qDebug() << order_arr;
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
    // record database
    QSqlQuery qry;
    QString username;
    // i) first find user name
    qry.exec("SELECT user_name FROM userTable WHERE implement='Y'");
    qry.next(); // only 1 orw
    //qDebug() << qry.value(0); // ex) QVariant(QString, "kyujin")
    username = qry.value(0).toString();

    // set month
    month -= 1;
    if(month == 0){
        month = 12;
        year-=1;
    }
    set_frame(month, year);
    qry.exec("UPDATE userTable SET set_month="+QString::number(month)+" WHERE user_name= '"+username+"'");
    qry.exec("UPDATE userTable SET set_year="+QString::number(year)+" WHERE user_name= '"+username+"'");

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
    // record database
    QSqlQuery qry;
    QString username;
    // i) first find user name
    qry.exec("SELECT user_name FROM userTable WHERE implement='Y'");
    qry.next(); // only 1 orw
    //qDebug() << qry.value(0); // ex) QVariant(QString, "kyujin")
    username = qry.value(0).toString();


    month += 1;
    if(month == 13){
        month = 1;
        year+=1;
    }

    //ui -> label_2 -> setStyleSheet("background-color:rgba(255,255,255,1.0);");

    set_frame(month, year);
    qry.exec("UPDATE userTable SET set_month="+QString::number(month)+" WHERE user_name= '"+username+"'");
    qry.exec("UPDATE userTable SET set_year="+QString::number(year)+" WHERE user_name= '"+username+"'");

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


void Secmainwindow::on_verticalScrollBar_sliderMoved(int position)
{
    ui -> secpage_pic -> setGeometry(0, 0-position, 375, 812);

    ui -> go_summary -> setGeometry(250, 150-position, 81, 31);
    ui -> year -> setGeometry(50, 146-position, 113, 21);
    ui -> month_line -> setGeometry(50, 160-position, 191, 31);
    ui -> income_line -> setGeometry(187, 201-position, 137, 21);
    ui -> expense_line -> setGeometry(187, 225-position, 137, 21);

    ui -> back_btn -> setGeometry(38, 213-position, 20, 20);
    ui -> next_btn -> setGeometry(320, 213-position, 20, 20);
    ui -> edit_btn -> setGeometry(20, 290-position, 41, 31);
    ui -> go_adding -> setGeometry(329, 297-position, 20, 20);
    ui -> go_planning -> setGeometry(317, 359-position, 20, 20);
    ui -> target_line -> setGeometry(95, 343-position, 200, 21);
    ui -> target_line_2 -> setGeometry(33, 370-position, 281, 21);
    ui -> target_line_3 -> setGeometry(35, 343-position, 61, 21);

    QLabel *minus_label;
    QPushButton *minus_btn;
    QLineEdit *text_title;
    QLineEdit *text_day;
    QLineEdit *text_info;
    QLineEdit *text_money;
    QLabel *label;
    for(int i=0; i<g_count; i++){
        QString text = "minus_label_"+QString::number(order_arr[i]);
        QString text_btn = "minus_btn_"+QString::number(order_arr[i]);
        QString title = "text_title_"+QString::number(order_arr[i]);
        QString day = "text_day_"+QString::number(order_arr[i]);
        QString info = "text_info_"+QString::number(order_arr[i]);
        QString money = "text_money_"+QString::number(order_arr[i]);
        QString label_text = "label_"+QString::number(order_arr[i]);

        minus_label = findChild<QLabel*>(text);
        minus_label->setGeometry(coordinates[i][0], coordinates[i][1]-position, 15, 15);

        minus_btn = findChild<QPushButton*>(text_btn);
        minus_btn->setGeometry(coordinates[i][2], coordinates[i][3]-position, 15, 15);

        text_title = findChild<QLineEdit*>(title);
        text_title->setGeometry(coordinates[i][4], coordinates[i][5]-position, 171, 24);

        text_day = findChild<QLineEdit*>(day);
        text_day->setGeometry(coordinates[i][6], coordinates[i][7]-position, 101, 24);

        text_info = findChild<QLineEdit*>(info);
        text_info->setGeometry(coordinates[i][8], coordinates[i][9]-position, 171, 30);

        text_money = findChild<QLineEdit*>(money);
        text_money->setGeometry(coordinates[i][10], coordinates[i][11]-position, 101, 24);

        label = findChild<QLabel*>(label_text);
        label->setGeometry(coordinates[i][12], coordinates[i][13]-position, 41, 48);

        /*
         * example
        minus_label = findChild<QLabel*>(text);
        minus_btn = findChild<QPushButton*>(text_btn);
        minus_label->hide();
        minus_btn->hide();
        minus_btn->setEnabled(false);
        */
}


}

