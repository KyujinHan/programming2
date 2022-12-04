#include "recordplan.h"
#include "ui_recordplan.h"
#include "secmainwindow.h"
#include <cctype>
#include <string>
#include <time.h>
#include <QDate>
#include <chrono>

//using namespace std;

// global_variable
bool choose_flag=false;
bool expense_flag;

Recordplan::Recordplan(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Recordplan)
{
    ui->setupUi(this);
    QPixmap pix(":/images/record_page.png");
    ui->record_pic->setPixmap(pix.scaled(375,812));

    // Define database
    // Database
    /*
    mydb = QSqlDatabase::addDatabase("QSQLITE"); // database make object
    mydb.setDatabaseName("./project_data.db"); // database name
    if(!mydb.open()){
        qDebug() << "It is not connected"; // label is objectName
    }
    */

    // check the num
    QSqlQuery qry;
    QString field_num, money, title;
    qry.exec("SELECT field_num FROM userTable WHERE implement='Y'");
    qry.next(); // only 1 orw
    //qDebug() << qry.value(0); // ex) QVariant(QString, "kyujin")
    field_num = qry.value(0).toString();
    //qDebug() << field_num;

    if(field_num.toInt() != 99){
        ui -> category_list -> setCurrentRow(field_num.toInt());
        if(field_num.toInt()==12){ // custom
            ui -> category_list -> setCurrentRow(field_num.toInt());
            qry.exec("SELECT custom_category FROM userTable WHERE implement='Y'");
            qry.next();
            QString custom = qry.value(0).toString();
            qDebug() << custom;
            //qDebug() << ui->category_list->currentTextChanged()
            ui -> category_list -> currentItem() -> setText(custom);
            //qDebug() << "good";
        }
    }

    // set text(?)
    qry.exec("SELECT money FROM userTable WHERE implement='Y'");
    qry.next();
    money = qry.value(0).toString();
    ui -> money_line -> setText(money);

    qry.exec("SELECT title FROM userTable WHERE implement='Y'");
    qry.next();
    title = qry.value(0).toString();
    ui -> title_line -> setText(title);

    // set Date
    qry.exec("SELECT set_month, set_year FROM userTable WHERE implement='Y'");
    qry.next();
    QString user_year = qry.value(1).toString();
    QString user_month = qry.value(0).toString();
    int month = qry.value(0).toInt();
    QString date_string;
    QDate start_date;
    if(month<10){
        date_string = user_year+"/0"+user_month+"/01";

    } else {
        date_string = user_year+"/"+user_month+"/01";
    }

    start_date = QDate::fromString(date_string, "yyyy/MM/dd");
    ui -> date_edit -> setDate(start_date);
    ui -> date_edit -> setMinimumDate(start_date);

    if(month==1){
        date_string = user_year+"/0"+user_month+"/31";
        QDate end_date = QDate::fromString(date_string, "yyyy/MM/dd");
        ui -> date_edit -> setMaximumDate(end_date);

    } else if(month == 2){
        // checking
        QString user_day = feb_day(user_year);
        date_string = user_year+"/0"+user_month+"/"+user_day;
        QDate end_date = QDate::fromString(date_string, "yyyy/MM/dd");
        ui -> date_edit -> setMaximumDate(end_date);

    } else if(month == 3){
        date_string = user_year+"/0"+user_month+"/31";
        QDate end_date = QDate::fromString(date_string, "yyyy/MM/dd");
        ui -> date_edit -> setMaximumDate(end_date);

    } else if(month == 4){
        date_string = user_year+"/0"+user_month+"/30";
        QDate end_date = QDate::fromString(date_string, "yyyy/MM/dd");
        ui -> date_edit -> setMaximumDate(end_date);

    } else if(month == 5){
        date_string = user_year+"/0"+user_month+"/31";
        QDate end_date = QDate::fromString(date_string, "yyyy/MM/dd");
        ui -> date_edit -> setMaximumDate(end_date);

    } else if(month == 6){
        date_string = user_year+"/0"+user_month+"/30";
        QDate end_date = QDate::fromString(date_string, "yyyy/MM/dd");
        ui -> date_edit -> setMaximumDate(end_date);

    } else if(month == 7){
        date_string = user_year+"/0"+user_month+"/31";
        QDate end_date = QDate::fromString(date_string, "yyyy/MM/dd");
        ui -> date_edit -> setMaximumDate(end_date);

    } else if(month == 8){
        date_string = user_year+"/0"+user_month+"/31";
        QDate end_date = QDate::fromString(date_string, "yyyy/MM/dd");
        ui -> date_edit -> setMaximumDate(end_date);

    } else if(month == 9){
        date_string = user_year+"/0"+user_month+"/30";
        QDate end_date = QDate::fromString(date_string, "yyyy/MM/dd");
        ui -> date_edit -> setMaximumDate(end_date);

    } else if(month == 10){
        date_string = user_year+"/"+user_month+"/31";
        QDate end_date = QDate::fromString(date_string, "yyyy/MM/dd");
        ui -> date_edit -> setMaximumDate(end_date);

    } else if(month == 11){
        date_string = user_year+"/"+user_month+"/30";
        QDate end_date = QDate::fromString(date_string, "yyyy/MM/dd");
        ui -> date_edit -> setMaximumDate(end_date);

    } else if(month == 12){
        date_string = user_year+"/"+user_month+"/31";
        QDate end_date = QDate::fromString(date_string, "yyyy/MM/dd");
        ui -> date_edit -> setMaximumDate(end_date);
    }
}

Recordplan::~Recordplan()
{
    delete ui;
}

void Recordplan::on_go_secpage_clicked()
{
    ui -> go_secpage -> setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.0)");

    hide();
    Secmainwindow *secmain_page;
    secmain_page = new Secmainwindow(this);
    secmain_page->show();
}

QString Recordplan::feb_day(QString user_year){
    int year = user_year.toInt();
    int day;
    if((year%400) == 0 || ((year%100) != 0 && (year % 4) == 0)){
        day = 29;
    } else {
        day = 28;
    }

    return QString::number(day);

}


// money: only integer
// money_type: must choose
bool check_money_type(string money){
    if(money==""){
        return false;
    }

    for(char i : money){
        if(!isdigit(i)){
            return false;
        }
    }
    return true;
}

/*
int calculate_money(QString money_type, QString money, QString username, QString year, QString month, QString day){
    int count = 0;
    // calculate sum
    QSqlQuery qry;
    qry.exec("SELECT * FROM projectDB WHERE user_name='"+username+"'");
    while(qry.next()){
        count ++;
    }

    int sum;
    int before_sum;
    if (count == 0){
        if(money_type=="income"){
            sum = money.toInt();
        } else{
            sum = money.toInt() * (-1); // expense
        }
    } else {
        qry.exec("SELECT sum FROM projectDB WHERE user_name='"+username+"' AND year>="+year+" AND month>="+month+" AND day>="+day+" \
 ORDER BY year, month, day");
        while(qry.next()){
            before_sum = qry.value(0).toInt();
            if(money_type=="income"){
                sum = before_sum + money.toInt();
            } else {
                sum = before_sum - money.toInt();
            }
        }
    }

    return sum;
}
*/

// save your budget recording
void Recordplan::on_save_btn_clicked()
{
    // define database variable
    QString category, method, money, year, month, day, title, money_type, sum; // 8 variables
    int category_row = ui -> category_list -> currentRow();
    if(category_row<0){
        qDebug() << "You must select category";
        return;
    }
    category = ui -> category_list -> currentItem() -> text(); // current category get
    //qDebug() << category;

    money = ui -> money_line -> text(); // now Qstring form. We will change integer type!
    string money_check = money.toStdString(); // QString -> string
    bool money_flag = check_money_type(money_check);
    if (money_flag==false){ // checking money is integer?
        qDebug() << "The money input type is not integer.";
        return;
    }

    title = ui -> title_line -> text();

    int method_row = ui -> method_list -> currentRow();
    if(method_row<0){
        qDebug() << "You must method category";
        return;
    }
    method = ui -> method_list -> currentItem() -> text(); // card, cash, etc.

    if(choose_flag==true){
        if (expense_flag==true){ // expense? income? Using global variables
            money_type = "expense";
        } else if (expense_flag==false) {
            money_type = "income";
        }
    } else {
        qDebug() << "There is no money_type. Please click expense or income";
        return ;
    }

    // This will change type int -> QString
    int year_int = ui -> date_edit -> date().year();
    year = QString::number(year_int);
    int month_int = ui -> date_edit -> date().month();
    month = QString::number(month_int);
    int day_int = ui -> date_edit -> date().day();
    day = QString::number(day_int);

    // record database
    QSqlQuery qry;
    QString username;
    // i) first find user name
    qry.exec("SELECT user_name FROM userTable WHERE implement='Y'");
    qry.next(); // only 1 orw
    //qDebug() << qry.value(0); // ex) QVariant(QString, "kyujin")
    username = qry.value(0).toString();

    // take sum money
    //int sum_int = calculate_money(money_type, money, username, year, month, day);
    //sum = QString::number(sum_int);

    // save database
    /*
    if (qry.exec("INSERT INTO projectDB (user_name, category, money, year, month, day, title, method, money_type) "
                 "VALUES ('"+username+"'"+" "+category+""+" "+money+" "+year+" "+month+" "+day+" "+" '"+title+"'"+" '"+method+"'"+" '"+money_type+"')")){
        qDebug() << "1";
    } else {
        qDebug() << qry.lastError().text();
        return;
    }
    */
    qry.prepare("INSERT INTO projectDB (user_name, category, money, year, month, day, title, method, money_type) "
                "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?)");
    qry.addBindValue(username);
    qry.addBindValue(category);
    qry.addBindValue(money);
    qry.addBindValue(year);
    qry.addBindValue(month);
    qry.addBindValue(day);
    qry.addBindValue(title);
    qry.addBindValue(method);
    qry.addBindValue(money_type);
    //qry.addBindValue(sum);

    if(qry.exec()){
        qDebug() << "complete save";
    } else {
        qDebug() << qry.lastError().text();
        return;
    }

    //change_save_btn();

    // move sec_page
    hide();
    Secmainwindow *secmain_page;
    secmain_page = new Secmainwindow(this);
    secmain_page->show();
}

void Recordplan::change_save_btn(){
    ui -> save_btn -> setStyleSheet("background-color:rgb(0,255,0); font: 700 12pt '맑은 고딕'; color: rgb(0,0,0); border: 2px solid rgb(0,255,0); border-radius: 5px;");
    clock_t delay = 1 * CLOCKS_PER_SEC; // 1sec delay
    clock_t start = clock();
    while (clock() - start < delay);
}

// expense btn
void Recordplan::on_expense_btn_clicked()
{
    choose_flag=true;
    expense_flag=true;

    /*
    font: 700 11pt "맑은 고딕";
    color: rgb(0,0,0);
    background-color: white;
    border: 2px solid rgb(0,0,0);
    border-radius: 5px;
    */

    ui -> expense_btn -> setStyleSheet("background-color:rgb(0,255,0); font: 700 14pt '맑은 고딕'; color: rgb(0,0,0); border: 2px solid rgb(0,255,0); border-radius: 5px;");
    ui -> income_btn -> setStyleSheet("background-color:rgb(255,255,255); font: 700 14pt '맑은 고딕'; color: rgb(0,0,0); border: 2px solid rgb(0,0,0); border-radius: 5px;");
}

// income btn
void Recordplan::on_income_btn_clicked()
{
    choose_flag=true;
    expense_flag=false;

    ui -> expense_btn -> setStyleSheet("background-color:rgb(255,255,255); font: 700 14pt '맑은 고딕'; color: rgb(0,0,0); border: 2px solid rgb(0,0,0); border-radius: 5px;");
    ui -> income_btn -> setStyleSheet("background-color:rgb(0,255,0); font: 700 14pt '맑은 고딕'; color: rgb(0,0,0); border: 2px solid rgb(0,255,0); border-radius: 5px;");
}

// remove money
void Recordplan::on_remove_money_clicked()
{
    ui -> remove_money -> setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.0)");
    ui -> money_line -> setText("");
}


void Recordplan::on_go_category_menu_clicked()
{
    QString record_money = ui -> money_line -> text();
    QString record_title = ui -> title_line -> text();

    // record database
    QSqlQuery qry;
    QString username;
    // i) first find user name
    qry.exec("SELECT user_name FROM userTable WHERE implement='Y'");
    qry.next(); // only 1 orw
    //qDebug() << qry.value(0); // ex) QVariant(QString, "kyujin")
    username = qry.value(0).toString();

    // ii) update
    if(!(qry.exec("UPDATE userTable SET money='"+record_money+"' WHERE implement='Y'"))){
        qDebug() << qry.lastError().text();
    }
    qry.exec("UPDATE userTable SET title='"+record_title+"' WHERE implement='Y'");

    hide();
    category = new category_menu(this);
    category->show();
}

