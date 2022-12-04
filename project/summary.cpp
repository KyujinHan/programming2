#include "summary.h"
#include "ui_summary.h"
#include "secmainwindow.h"
#include <iostream>
#include <vector>

using namespace std;

//int sum_month = sec_month;
bool b_month = true;
bool b_year = false;
bool b_week = false;

summary::summary(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::summary)
{
    ui->setupUi(this);
    QPixmap pix(":/images/summary.png");
    ui->summary_pic->setPixmap(pix.scaled(375,812));

    if(b_month){
        set_month_frame();
        ui->year_btn->setStyleSheet("background-color:rgb(255,255,255); font: 700 14pt '맑은 고딕'; color: rgb(0,0,0); border: 0px solid rgb(0,0,0); border-radius: 10px;");
        ui->month_btn->setStyleSheet("background-color:rgb(0,255,0); font: 700 14pt '맑은 고딕'; color: rgb(255,255,255); border: 2px solid rgb(0,0,0); border-radius: 10px;");
        ui->week_btn->setStyleSheet("background-color:rgb(255,255,255); font: 700 14pt '맑은 고딕'; color: rgb(0,0,0); border: 0px solid rgb(0,0,0); border-radius: 10px;");
    } else if(b_year){
        set_year_frame();
        ui->month_btn->setStyleSheet("background-color:rgb(255,255,255); font: 700 14pt '맑은 고딕'; color: rgb(0,0,0); border: 0px solid rgb(0,0,0); border-radius: 10px;");
        ui->year_btn->setStyleSheet("background-color:rgb(0,255,0); font: 700 14pt '맑은 고딕'; color: rgb(255,255,255); border: 2px solid rgb(0,0,0); border-radius: 10px;");
        ui->week_btn->setStyleSheet("background-color:rgb(255,255,255); font: 700 14pt '맑은 고딕'; color: rgb(0,0,0); border: 0px solid rgb(0,0,0); border-radius: 10px;");
    } else {
        set_week_frame();
        ui->year_btn->setStyleSheet("background-color:rgb(255,255,255); font: 700 14pt '맑은 고딕'; color: rgb(0,0,0); border: 0px solid rgb(0,0,0); border-radius: 10px;");
        ui->week_btn->setStyleSheet("background-color:rgb(0,255,0); font: 700 14pt '맑은 고딕'; color: rgb(255,255,255); border: 2px solid rgb(0,0,0); border-radius: 10px;");
        ui->month_btn->setStyleSheet("background-color:rgb(255,255,255); font: 700 14pt '맑은 고딕'; color: rgb(0,0,0); border: 0px solid rgb(0,0,0); border-radius: 10px;");
    }
}


summary::~summary()
{
    delete ui;
}

void summary::set_week_frame(){
    qDebug() << "Not yet";
}

void summary::set_year_frame(){
    // default: find user name
    QSqlQuery qry, qry_p;
    QString username;
    qry.exec("SELECT user_name FROM userTable WHERE implement='Y'");
    qry.next(); // only 1 orw
    username = qry.value(0).toString();

    // i) count variable & ii) sorting
    qry.exec("SELECT * FROM userTable WHERE user_name='"+username+"'");
    qry.next();
    //QString cur_month = qry.value(6).toString();
    QString cur_year = qry.value(7).toString();

    qry.exec("SELECT SUM(money) FROM projectDB WHERE user_name='"+username+"' and year="+cur_year+" and money_type='expense'");
    if(qry.next()){
        if(qry.value(0).toString()==""){
            ui -> money_line -> setText("0₩");
        } else {
            ui -> money_line -> setText(qry.value(0).toString()+"₩");
        }
    }

    ui -> date_info -> setText("(Analysis date: "+cur_year+")");

    if(!(qry.exec("SELECT category, SUM(money) FROM projectDB WHERE user_name='"+username+"' and year="+cur_year+" and money_type='expense' GROUP BY category"))){
        qDebug() << qry.lastError().text();
    }

    qDebug() << "gogo";

    int count = 0;
    vector<string> categories;
    while(qry.next()){ // check person (we expected 1)
        int i = 36*(count); // ******** 줄 사이 간격 맞춤 ********
        QString category, money, year, month, day, category_2;
        //QLabel *label = new QLabel(this);
        category = qry.value(0).toString();
        //money = qry.value(2).toString();
        //year = qry.value(3).toString();
        //month = qry.value(4).toString();
        //day = qry.value(5).toString();
        money = qry.value(1).toString();

        category_2 = category;
        if(category=="Cafe/Snack"){
            //category_2 = category;
            category = "Snack";
        } else if ((category!="Meal") and (category != "Medicine") and (category!="Car") and (category!="Transportation") and (category!="Education") \
                   and (category!="Living") and (category!="Travel") and (category!="Daily") and (category!="Exercise") and (category!="Clothes") and \
                   (category!="Beauty")){
            category = "Other";
            //category_2 = category;
        }


        categories.push_back(category_2.toStdString());

        //QPixmap pix(":/images/s_"+category+".png"); // 이거는 작은 사진들 주소....근데 필요 없을듯 하네요
        QPixmap pix(":/images/"+category+".png");
        QLabel *label_2 = new QLabel(this);
        label_2->setPixmap(pix.scaled(20,20));// 작은 이모티콘 사이즈
        label_2->setGeometry(18, 380+i, 41, 48); // 작은 이모티콘 위치
        label_2->setStyleSheet("font: 800 16pt '맑은 고딕'; color: rgb(0, 0, 0); background-color: rgba(0,0,0,0); border: 0px");

        // planning에 있다면 money, or 0.
        if(qry_p.exec("SELECT money FROM planning WHERE username='"+username+"' and category='"+category_2+"' and year="+cur_year+"")){
            if(qry_p.next()){ // value
                QLineEdit *text_money = new QLineEdit(this); // planning budget
                text_money->setGeometry(50, 383+i, 301, 40); // ******** 텍스트 위치 ********
                text_money->setText(qry_p.value(0).toString()+"₩");
                text_money->setStyleSheet("font: 800 16pt '맑은 고딕'; color: rgb(0, 0, 0); background-color: rgba(0,0,0,0); border: 0px");
                text_money->setAlignment(Qt::AlignRight);
                text_money->setReadOnly(true);
            } else{
                QLineEdit *text_money = new QLineEdit(this); // planning budget
                text_money->setGeometry(50, 383+i, 301, 40); // ******** 텍스트 위치 ********
                text_money->setText("0₩");
                text_money->setStyleSheet("font: 800 16pt '맑은 고딕'; color: rgb(0, 0, 0); background-color: rgba(0,0,0,0); border: 0px");
                text_money->setAlignment(Qt::AlignRight);
                text_money->setReadOnly(true);
            }
        } else {
            qDebug() << qry_p.lastError().text();
        }

        QLineEdit *text_planned_b = new QLineEdit(this); // spent budget
        text_planned_b->setGeometry(-50, 383+i, 301, 40); // ******** 텍스트 위치 ********
        text_planned_b->setText(money+"₩");
        text_planned_b->setStyleSheet("font: 800 16pt '맑은 고딕'; color: rgb(17, 229, 17); background-color: rgba(0,0,0,0); border: 0px");
        text_planned_b->setAlignment(Qt::AlignRight);
        text_planned_b->setReadOnly(true);

        QLineEdit *text_category = new QLineEdit(this); // category
        text_category->setGeometry(47, 383+i, 301, 40); // ******** 텍스트 위치 ********
        if (category!="Other"){
            text_category->setText(category);
        } else {
            text_category->setText(category_2);
        }
        text_category->setStyleSheet("font: 800 16pt '맑은 고딕'; color: rgb(0,0,0); background-color: rgba(0,0,0,0); border: 0px");
        text_category->setAlignment(Qt::AlignLeft);
        text_category->setReadOnly(true);

        count++;
    }

    bool check;
    qry.exec("SELECT category, money FROM planning WHERE username='"+username+"' and year="+cur_year+" and money_type='expense'");
    while(qry.next()){ // check person (we expected 1)
        int i = 36*(count); // ******** 줄 사이 간격 맞춤 ********
        QString category, money, year, month, day, category_2;
        //QLabel *label = new QLabel(this);
        category = qry.value(0).toString();
        check = true;
        //cout << categories;
        for (string s: categories){
            if(s==category.toStdString()){
                check = false;
            }
        }
        //money = qry.value(2).toString();
        //year = qry.value(3).toString();
        //month = qry.value(4).toString();
        //day = qry.value(5).toString();
        money = qry.value(1).toString();

        if((check) && (money.toInt() != 0)){
            category_2 = category;
            if(category=="Cafe/Snack"){
                //category_2 = category;
                category = "Snack";
            } else if ((category!="Meal") and (category != "Medicine") and (category!="Car") and (category!="Transportation") and (category!="Education") \
                       and (category!="Living") and (category!="Travel") and (category!="Daily") and (category!="Exercise") and (category!="Clothes") and \
                       (category!="Beauty")){
                category = "Other";
                //category_2 = category;
            }


            //QPixmap pix(":/images/s_"+category+".png"); // 이거는 작은 사진들 주소....근데 필요 없을듯 하네요
            QPixmap pix(":/images/"+category+".png");
            QLabel *label_2 = new QLabel(this);
            label_2->setPixmap(pix.scaled(20,20));// 작은 이모티콘 사이즈
            label_2->setGeometry(18, 380+i, 41, 48); // 작은 이모티콘 위치
            label_2->setStyleSheet("font: 800 16pt '맑은 고딕'; color: rgb(0, 0, 0); background-color: rgba(0,0,0,0); border: 0px");

            // planning에 있다면 money, or 0.

            QLineEdit *text_money = new QLineEdit(this); // planning budget
            text_money->setGeometry(50, 383+i, 301, 40); // ******** 텍스트 위치 ********
            text_money->setText(qry.value(1).toString()+"₩");
            text_money->setStyleSheet("font: 800 16pt '맑은 고딕'; color: rgb(0, 0, 0); background-color: rgba(0,0,0,0); border: 0px");
            text_money->setAlignment(Qt::AlignRight);
            text_money->setReadOnly(true);

            QLineEdit *text_planned_b = new QLineEdit(this); // spent budget
            text_planned_b->setGeometry(-50, 383+i, 301, 40); // ******** 텍스트 위치 ********
            text_planned_b->setText("0₩");
            text_planned_b->setStyleSheet("font: 800 16pt '맑은 고딕'; color: rgb(17, 229, 17); background-color: rgba(0,0,0,0); border: 0px");
            text_planned_b->setAlignment(Qt::AlignRight);
            text_planned_b->setReadOnly(true);

            QLineEdit *text_category = new QLineEdit(this); // category
            text_category->setGeometry(47, 383+i, 301, 40); // ******** 텍스트 위치 ********
            if (category!="Other"){
                text_category->setText(category);
            } else {
                text_category->setText(category_2);
            }
            text_category->setStyleSheet("font: 800 16pt '맑은 고딕'; color: rgb(0,0,0); background-color: rgba(0,0,0,0); border: 0px");
            text_category->setAlignment(Qt::AlignLeft);
            text_category->setReadOnly(true);

            count++;
        }
    }
}

void summary::set_month_frame(){
    // default: find user name
    QSqlQuery qry, qry_p;
    QString username;
    qry.exec("SELECT user_name FROM userTable WHERE implement='Y'");
    qry.next(); // only 1 orw
    username = qry.value(0).toString();

    // i) count variable & ii) sorting
    qry.exec("SELECT * FROM userTable WHERE user_name='"+username+"'");
    qry.next();
    QString cur_month = qry.value(6).toString();
    QString cur_year = qry.value(7).toString();

    qry.exec("SELECT SUM(money) FROM projectDB WHERE user_name='"+username+"' and month="+cur_month+" and year="+cur_year+" and money_type='expense'");
    if(qry.next()){
        if(qry.value(0).toString()==""){
            ui -> money_line -> setText("0₩");
        } else {
            ui -> money_line -> setText(qry.value(0).toString()+"₩");
        }
    }

    if(!(qry.exec("SELECT category, SUM(money) FROM projectDB WHERE user_name='"+username+"' and month="+cur_month+" and year="+cur_year+" and money_type='expense' GROUP BY category"))){
        qDebug() << qry.lastError().text();
    }

    //int num_month = cur_month.toInt();
    //qDebug() << cur_month;
    if (cur_month.length()==2){
        ui -> date_info -> setText("(Analysis date: "+cur_year+"/"+cur_month+")");
    } else {
        ui -> date_info -> setText("(Analysis date: "+cur_year+"/0"+cur_month+")");
        //qDebug() << cur_month;
    }

    qDebug() << "gogo";

    int count = 0;
    vector<string> categories;
    while(qry.next()){ // check person (we expected 1)
        int i = 36*(count); // ******** 줄 사이 간격 맞춤 ********
        QString category, money, year, month, day, category_2;
        //QLabel *label = new QLabel(this);
        category = qry.value(0).toString();
        //money = qry.value(2).toString();
        //year = qry.value(3).toString();
        //month = qry.value(4).toString();
        //day = qry.value(5).toString();
        money = qry.value(1).toString();

        category_2 = category;
        if(category=="Cafe/Snack"){
            //category_2 = category;
            category = "Snack";
        } else if ((category!="Meal") and (category != "Medicine") and (category!="Car") and (category!="Transportation") and (category!="Education") \
                   and (category!="Living") and (category!="Travel") and (category!="Daily") and (category!="Exercise") and (category!="Clothes") and \
                   (category!="Beauty")){

            category = "Other";
            //category_2 = category;
        }

        categories.push_back(category_2.toStdString());

        //QPixmap pix(":/images/s_"+category+".png"); // 이거는 작은 사진들 주소....근데 필요 없을듯 하네요
        QPixmap pix(":/images/"+category+".png");
        QLabel *label_2 = new QLabel(this);
        label_2->setPixmap(pix.scaled(20,20));// 작은 이모티콘 사이즈
        label_2->setGeometry(18, 380+i, 41, 48); // 작은 이모티콘 위치
        label_2->setStyleSheet("font: 800 16pt '맑은 고딕'; color: rgb(0, 0, 0); background-color: rgba(0,0,0,0); border: 0px");

        // planning에 있다면 money, or 0.
        if(qry_p.exec("SELECT money FROM planning WHERE username='"+username+"' and category='"+category_2+"' and month="+cur_month+" and year="+cur_year+"")){
            if(qry_p.next()){ // value
                QLineEdit *text_money = new QLineEdit(this); // planning budget
                text_money->setGeometry(50, 383+i, 301, 40); // ******** 텍스트 위치 ********
                text_money->setText(qry_p.value(0).toString()+"₩");
                text_money->setStyleSheet("font: 800 16pt '맑은 고딕'; color: rgb(0, 0, 0); background-color: rgba(0,0,0,0); border: 0px");
                text_money->setAlignment(Qt::AlignRight);
                text_money->setReadOnly(true);
            } else{
                QLineEdit *text_money = new QLineEdit(this); // planning budget
                text_money->setGeometry(50, 383+i, 301, 40); // ******** 텍스트 위치 ********
                text_money->setText("0₩");
                text_money->setStyleSheet("font: 800 16pt '맑은 고딕'; color: rgb(0, 0, 0); background-color: rgba(0,0,0,0); border: 0px");
                text_money->setAlignment(Qt::AlignRight);
                text_money->setReadOnly(true);
            }
        } else {
            qDebug() << qry_p.lastError().text();
        }

        QLineEdit *text_planned_b = new QLineEdit(this); // spent budget
        text_planned_b->setGeometry(-50, 383+i, 301, 40); // ******** 텍스트 위치 ********
        text_planned_b->setText(money+"₩");
        text_planned_b->setStyleSheet("font: 800 16pt '맑은 고딕'; color: rgb(17, 229, 17); background-color: rgba(0,0,0,0); border: 0px");
        text_planned_b->setAlignment(Qt::AlignRight);
        text_planned_b->setReadOnly(true);

        QLineEdit *text_category = new QLineEdit(this); // category
        text_category->setGeometry(47, 383+i, 301, 40); // ******** 텍스트 위치 ********
        if (category!="Other"){
            text_category->setText(category);
        } else {
            text_category->setText(category_2);
        }
        text_category->setStyleSheet("font: 800 16pt '맑은 고딕'; color: rgb(0,0,0); background-color: rgba(0,0,0,0); border: 0px");
        text_category->setAlignment(Qt::AlignLeft);
        text_category->setReadOnly(true);

        count++;
    }
    //g_count = count; // save
    bool check;
    qry.exec("SELECT category, money FROM planning WHERE username='"+username+"' and month="+cur_month+" and year="+cur_year+" and money_type='expense'");
    while(qry.next()){ // check person (we expected 1)
        int i = 36*(count); // ******** 줄 사이 간격 맞춤 ********
        QString category, money, year, month, day, category_2;
        //QLabel *label = new QLabel(this);
        category = qry.value(0).toString();
        check = true;
        for (string s: categories){
            if(s==category.toStdString()){
                check = false;
            }
        }
        //money = qry.value(2).toString();
        //year = qry.value(3).toString();
        //month = qry.value(4).toString();
        //day = qry.value(5).toString();
        money = qry.value(1).toString();

        if((check) && (money.toInt() != 0)){
            category_2 = category;
            if(category=="Cafe/Snack"){
                //category_2 = category;
                category = "Snack";
            } else if ((category!="Meal") and (category != "Medicine") and (category!="Car") and (category!="Transportation") and (category!="Education") \
                       and (category!="Living") and (category!="Travel") and (category!="Daily") and (category!="Exercise") and (category!="Clothes") and \
                       (category!="Beauty")){
                category = "Other";
                //category_2 = category;
            }

            //QPixmap pix(":/images/s_"+category+".png"); // 이거는 작은 사진들 주소....근데 필요 없을듯 하네요
            QPixmap pix(":/images/"+category+".png");
            QLabel *label_2 = new QLabel(this);
            label_2->setPixmap(pix.scaled(20,20));// 작은 이모티콘 사이즈
            label_2->setGeometry(18, 380+i, 41, 48); // 작은 이모티콘 위치
            label_2->setStyleSheet("font: 800 16pt '맑은 고딕'; color: rgb(0, 0, 0); background-color: rgba(0,0,0,0); border: 0px");

            // planning에 있다면 money, or 0.

            QLineEdit *text_money = new QLineEdit(this); // planning budget
            text_money->setGeometry(50, 383+i, 301, 40); // ******** 텍스트 위치 ********
            text_money->setText(qry.value(1).toString()+"₩");
            text_money->setStyleSheet("font: 800 16pt '맑은 고딕'; color: rgb(0, 0, 0); background-color: rgba(0,0,0,0); border: 0px");
            text_money->setAlignment(Qt::AlignRight);
            text_money->setReadOnly(true);

            QLineEdit *text_planned_b = new QLineEdit(this); // spent budget
            text_planned_b->setGeometry(-50, 383+i, 301, 40); // ******** 텍스트 위치 ********
            text_planned_b->setText("0₩");
            text_planned_b->setStyleSheet("font: 800 16pt '맑은 고딕'; color: rgb(17, 229, 17); background-color: rgba(0,0,0,0); border: 0px");
            text_planned_b->setAlignment(Qt::AlignRight);
            text_planned_b->setReadOnly(true);

            QLineEdit *text_category = new QLineEdit(this); // category
            text_category->setGeometry(47, 383+i, 301, 40); // ******** 텍스트 위치 ********
            if (category!="Other"){
                text_category->setText(category);
            } else {
                text_category->setText(category_2);
            }
            text_category->setStyleSheet("font: 800 16pt '맑은 고딕'; color: rgb(0,0,0); background-color: rgba(0,0,0,0); border: 0px");
            text_category->setAlignment(Qt::AlignLeft);
            text_category->setReadOnly(true);

            count++;
        }
    }


}

void summary::on_go_secpage_clicked()
{
    b_year = false;
    b_month = true;
    b_week = false;

    hide();
    Secmainwindow *secmain_page;
    secmain_page = new Secmainwindow(this);
    secmain_page->show();
}


void summary::on_month_btn_clicked()
{
    ui->year_btn->setStyleSheet("background-color:rgb(255,255,255); font: 700 11pt '맑은 고딕'; color: rgb(0,0,0); border: 0px solid rgb(0,0,0); border-radius: 10px;");
    ui->month_btn->setStyleSheet("background-color:rgb(0,255,0); font: 700 11pt '맑은 고딕'; color: rgb(255,255,255); border: 2px solid rgb(0,0,0); border-radius: 10px;");
    ui->week_btn->setStyleSheet("background-color:rgb(255,255,255); font: 700 11pt '맑은 고딕'; color: rgb(0,0,0); border: 0px solid rgb(0,0,0); border-radius: 10px;");

    b_year = false;
    b_month = true;
    b_week = false;

    hide();
    summary *summary_page;
    summary_page = new summary(this);
    summary_page->show();

}


void summary::on_year_btn_clicked()
{
    ui->month_btn->setStyleSheet("background-color:rgb(255,255,255); font: 700 11pt '맑은 고딕'; color: rgb(0,0,0); border: 0px solid rgb(0,0,0); border-radius: 10px;");
    ui->year_btn->setStyleSheet("background-color:rgb(0,255,0); font: 700 11pt '맑은 고딕'; color: rgb(255,255,255); border: 2px solid rgb(0,0,0); border-radius: 10px;");
    ui->week_btn->setStyleSheet("background-color:rgb(255,255,255); font: 700 11pt '맑은 고딕'; color: rgb(0,0,0); border: 0px solid rgb(0,0,0); border-radius: 10px;");

    //ui -> label_2 -> setStyleSheet("background-color:rgba(255,255,255,1.0);");
    //ui -> label_2 -> raise();

    b_year = true;
    b_month = false;
    b_week = false;

    //set_year_frame();

    hide();
    summary *summary_page;
    summary_page = new summary(this);
    summary_page->show();

}



void summary::on_week_btn_clicked()
{
    ui->year_btn->setStyleSheet("background-color:rgb(255,255,255); font: 700 11pt '맑은 고딕'; color: rgb(0,0,0); border: 0px solid rgb(0,0,0); border-radius: 10px;");
    ui->week_btn->setStyleSheet("background-color:rgb(0,255,0); font: 700 11pt '맑은 고딕'; color: rgb(255,255,255); border: 2px solid rgb(0,0,0); border-radius: 10px;");
    ui->month_btn->setStyleSheet("background-color:rgb(255,255,255); font: 700 11pt '맑은 고딕'; color: rgb(0,0,0); border: 0px solid rgb(0,0,0); border-radius: 10px;");

    b_year = false;
    b_month = false;
    b_week = true;

    hide();
    summary *summary_page;
    summary_page = new summary(this);
    summary_page->show();

}
