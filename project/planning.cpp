#include "planning.h"
#include "ui_planning.h"
#include "secmainwindow.h"
#include <cctype>
#include <QFontDatabase>
//#include <QScrollArea>

bool btn_flag = false;
bool before_flag = false;
int cur_month = QDate::currentDate().month();
int cur_year = QDate::currentDate().year();
int g_month = QDate::currentDate().month();
int g_year = QDate::currentDate().year();

Planning::Planning(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Planning)
{
    ui->setupUi(this);
    QPixmap pix(":/images/Planning.png");
    ui->pic_plan->setPixmap(pix.scaled(375,1376));

    QSqlQuery qry;
    QString username;
    // i) first find user name
    qry.exec("SELECT user_name FROM userTable WHERE implement='Y'");
    qry.next(); // only 1 row
    //qDebug() << qry.value(0); // ex) QVariant(QString, "kyujin")
    username = qry.value(0).toString();
    if(qry.exec("SELECT username FROM userCategory WHERE username='"+username+"' and month="+QString::number(g_month)+" and year="+QString::number(g_year)+"")){
        int count = 0;
        while(qry.next()){
            count++;
        }
        if (count==0){
            qry.exec("INSERT INTO userCategory VALUES ('"+username+"', 'no', 'no', 'no', 'no', "+QString::number(g_year)+", "+QString::number(g_month)+")");
        }
    }

    set_frame();

    ui -> year_line -> setText(QString::number(g_year));
    if (g_month >= 10){
        ui -> month_line -> setText("- "+QString::number(g_month));
    } else {
        ui -> month_line -> setText("- 0"+QString::number(g_month));
    }

    /*

    before_flag true일 때 btn 디자인 -> 흰색
    false일 때 btn 디자인 -> 현재 상태
    */
}

Planning::~Planning()
{
    delete ui;
}

void Planning::set_frame(){
    // make frame database
    QSqlQuery qry, qry_c;
    QString username;
    // i) first find user name
    qry.exec("SELECT user_name FROM userTable WHERE implement='Y'");
    qry.next(); // only 1 row
    //qDebug() << qry.value(0); // ex) QVariant(QString, "kyujin")
    username = qry.value(0).toString();

    if(!(qry.exec("SELECT category,money FROM planning WHERE username='"+username+"' and month="+QString::number(g_month)+" and year="+QString::number(g_year)+""))){
        ui -> expense_line -> setText("0₩");

    } else {
        qry_c.exec("SELECT * FROM userCategory WHERE username='"+username+"' and month="+QString::number(g_month)+" and year="+QString::number(g_year)+"");
        qry_c.next();
        QString category_1, category_2, category_3, category_4;
        category_1 = qry_c.value(1).toString();
        category_2 = qry_c.value(2).toString();
        category_3 = qry_c.value(3).toString();
        category_4 = qry_c.value(4).toString();

        // Font setting
        QFontDatabase::addApplicationFont(":/font/Noto SansKR-Medium.otf");
        QFont noto("Noto SansKR-Medium", 12, QFont::Normal);

        int predict = 0;
        while(qry.next()){
            predict += qry.value(1).toInt();
            QString plan_money, category;
            category = qry.value(0).toString();
            plan_money = qry.value(1).toString();
            if (category=="Meal"){
                ui -> meal_money -> setText(plan_money);
            } else if (category=="Car") {
                ui -> car_money -> setText(plan_money);
            } else if (category == "Education"){
                ui -> edu_money -> setText(plan_money);
            } else if (category == "Living"){
                ui -> living_money -> setText(plan_money);
            } else if (category == "Travel"){
                ui -> travel_money -> setText(plan_money);
            } else if (category == "Medicine") {
                ui -> medicine_money -> setText(plan_money);
            } else if (category == "Cafe/Snack"){
                ui -> snack_money -> setText(plan_money);
            } else if (category == "Daily"){
                ui -> daily_money -> setText(plan_money);
            } else if (category == "Exercise"){
                ui -> exercise_money -> setText(plan_money);
            } else if (category == "Clothes"){
                ui -> cloth_money -> setText(plan_money);
            } else if (category == "Beauty"){
                ui -> beauty_money -> setText(plan_money);
            } else if (category == "Transportation"){
                ui -> trans_money -> setText(plan_money);
            } else if (category == "Other"){
                ui -> other_money1 -> setText(plan_money);
            } else if (category == category_1){
                ui -> category1 -> setText(category);
                ui -> category1 -> setFont(noto);
                ui -> other_money1 -> setText(plan_money);
            } else if (category == category_2){
                ui -> category2 -> setText(category);
                ui -> category2 -> setFont(noto);
                ui -> other_money2 -> setText(plan_money);
            } else if (category == category_3){
                ui -> category3 -> setText(category);
                ui -> category3 -> setFont(noto);
                ui -> other_money3 -> setText(plan_money);
            } else if (category == category_4){
                ui -> category4 -> setText(category);
                ui -> category4 -> setFont(noto);
                ui -> other_money4 -> setText(plan_money);
            }
        }


        QString money = QString::number(predict);
        ui -> expense_line -> setText(money+"₩");

    }
    /*
    QLabel *label0 = new QLabel(this);
    QPixmap pix0(":/images/Meal.png");
    label0->setPixmap(pix0.scaled(40,40));
    label0->setGeometry(24, 312, 40, 40);
    count += 1;

    QLabel *label1 = new QLabel(this);
    QPixmap pix1(":/images/Snack.png");
    label1->setPixmap(pix1.scaled(40,40));
    label1->setGeometry(24, 312+64*count, 40, 40);
    count += 1;

    QLabel *label2 = new QLabel(this);
    QPixmap pix2(":/images/Medicine.png");
    label2->setPixmap(pix2.scaled(40,40));
    label2->setGeometry(24, 312+64*count, 40, 40);
    count += 1;

    QLabel *label3 = new QLabel(this);
    QPixmap pix3(":/images/Car.png");
    label3->setPixmap(pix3.scaled(40,40));
    label3->setGeometry(24, 312+64*count, 40, 40);
    count += 1;

    QLabel *label4 = new QLabel(this);
    QPixmap pix4(":/images/Car.png");
    label4->setPixmap(pix4.scaled(40,40));
    label4->setGeometry(24, 312+64*count, 40, 40);
    count += 1;

    QLabel *label5 = new QLabel(this);
    QPixmap pix5(":/images/Transportation.png");
    label5->setPixmap(pix5.scaled(40,40));
    label5->setGeometry(24, 312+64*count, 40, 40);
    count += 1;

    QLabel *label6 = new QLabel(this);
    QPixmap pix6(":/images/Education.png");
    label6->setPixmap(pix6.scaled(40,40));
    label6->setGeometry(24, 312+64*count, 40, 40);
    count += 1;

    QLabel *label7 = new QLabel(this);
    QPixmap pix7(":/images/Living.png");
    label7->setPixmap(pix7.scaled(40,40));
    label7->setGeometry(24, 312+64*count, 40, 40);
    count += 1;

    QLabel *label8 = new QLabel(this);
    QPixmap pix8(":/images/Travel.png");
    label8->setPixmap(pix8.scaled(40,40));
    label8->setGeometry(24, 312+64*count, 40, 40);
    count += 1;

    QLabel *label9 = new QLabel(this);
    QPixmap pix9(":/images/Daily.png");
    label9->setPixmap(pix9.scaled(40,40));
    label9->setGeometry(24, 312+64*count, 40, 40);
    count += 1;

    QLabel *label10 = new QLabel(this);
    QPixmap pix10(":/images/Exercise.png");
    label10->setPixmap(pix10.scaled(40,40));
    label10->setGeometry(24, 312+64*count, 40, 40);
    count += 1;

    QLabel *label11 = new QLabel(this);
    QPixmap pix11(":/images/Clothes.png");
    label11->setPixmap(pix11.scaled(40,40));
    label11->setGeometry(24, 312+64*count, 40, 40);
    count += 1;

    QLabel *label12 = new QLabel(this);
    QPixmap pix12(":/images/Beauty.png");
    label12->setPixmap(pix12.scaled(40,40));
    label12->setGeometry(24, 312+64*count, 40, 40);
    count += 1;

    QLabel *label13 = new QLabel(this);
    QPixmap pix13(":/images/Other.png");
    label13->setPixmap(pix13.scaled(40,40));
    label13->setGeometry(24, 312+64*count, 40, 40);
    count += 1;
    */

}

void Planning::on_go_secmain_clicked()
{
    hide();
    Secmainwindow *secmain_page;
    secmain_page = new Secmainwindow(this);
    secmain_page->show();
}


void Planning::on_verticalScrollBar_sliderMoved(int position)
{
    ui -> pic_plan -> setGeometry(0, 0-position, 375, 812);

    ui -> edit_btn -> setGeometry(20, 260-position, 41, 31);
    ui -> go_adding -> setGeometry(326, 268-position, 20, 20);
    ui -> next_btn -> setGeometry(320, 200-position, 20, 20);
    ui -> back_btn -> setGeometry(39, 200-position, 20, 20);
    ui -> go_secmain -> setGeometry(23, 59-position, 21, 21);

    ui -> meal_money -> setGeometry(240, 322-position, 91, 21);
    ui -> car_money -> setGeometry(240, 514-position, 91, 21);
    ui -> cloth_money -> setGeometry(240, 962-position, 91, 21);
    ui -> daily_money -> setGeometry(240, 834-position, 91, 21);
    ui -> edu_money -> setGeometry(240, 642-position, 91, 21);
    ui -> exercise_money -> setGeometry(240, 898-position, 91, 21);
    ui -> living_money -> setGeometry(240, 706-position, 91, 21);
    ui -> snack_money -> setGeometry(240, 386-position, 91, 21);
    ui -> trans_money -> setGeometry(240, 578-position, 91, 21);
    ui -> travel_money -> setGeometry(240, 770-position, 91, 21);
    ui -> medicine_money -> setGeometry(240, 450-position, 91, 21);
    ui -> beauty_money -> setGeometry(240, 1026-position, 91, 21);
    ui -> other_money1 -> setGeometry(240, 1090-position, 91, 21);
    ui -> other_money2 -> setGeometry(240, 1154-position, 91, 21);
    ui -> other_money3 -> setGeometry(240, 1218-position, 91, 21);
    ui -> other_money4 -> setGeometry(240, 1282-position, 91, 21);

    ui -> category1 -> setGeometry(93, 1090-position, 91, 21);
    ui -> category2 -> setGeometry(93, 1154-position, 91, 21);
    ui -> category3 -> setGeometry(93, 1218-position, 91, 21);
    ui -> category4 -> setGeometry(93, 1282-position, 91, 21);

    ui -> expense_line -> setGeometry(190, 200-position, 131, 21);
    ui -> month_line -> setGeometry(175, 150-position, 81, 31);
    ui -> year_line -> setGeometry(105, 150-position, 71, 31);
}

bool check_money_types(string money){
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


void Planning::on_edit_btn_clicked()
{
    if(before_flag==false){
        if(btn_flag==false){
            bool text_flag = false;
            ui -> edit_btn -> setStyleSheet("background-color:rgb(255,255,255); font: 700 14pt '맑은 고딕'; color: rgb(255,0,0); border: 0px;");
            ui -> edit_btn -> setText("Save");
            //ui -> go_adding -> setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.0)");
            ui -> meal_money -> setReadOnly(text_flag);
            ui -> car_money -> setReadOnly(text_flag);
            ui -> cloth_money -> setReadOnly(text_flag);
            ui -> daily_money -> setReadOnly(text_flag);
            ui -> edu_money -> setReadOnly(text_flag);
            ui -> exercise_money -> setReadOnly(text_flag);
            ui -> living_money -> setReadOnly(text_flag);
            ui -> snack_money -> setReadOnly(text_flag);
            ui -> trans_money -> setReadOnly(text_flag);
            ui -> travel_money -> setReadOnly(text_flag);
            ui -> medicine_money -> setReadOnly(text_flag);
            ui -> beauty_money -> setReadOnly(text_flag);
            ui -> other_money1 -> setReadOnly(text_flag);
            ui -> other_money2 -> setReadOnly(text_flag);
            ui -> other_money3 -> setReadOnly(text_flag);
            ui -> other_money4 -> setReadOnly(text_flag);

            ui -> category1 -> setReadOnly(text_flag);
            ui -> category1 -> setStyleSheet("background-color: rgba(255, 255, 255, 1.0); color: rgb(0,0,0); font: 700 12pt '맑은 고딕';");
            ui -> category2 -> setReadOnly(text_flag);
            ui -> category2 -> setStyleSheet("background-color: rgba(255, 255, 255, 1.0); color: rgb(0,0,0); font: 700 12pt '맑은 고딕';");
            ui -> category3 -> setReadOnly(text_flag);
            ui -> category3 -> setStyleSheet("background-color: rgba(255, 255, 255, 1.0); color: rgb(0,0,0); font: 700 12pt '맑은 고딕';");
            ui -> category4 -> setReadOnly(text_flag);
            ui -> category4 -> setStyleSheet("background-color: rgba(255, 255, 255, 1.0); color: rgb(0,0,0); font: 700 12pt '맑은 고딕';");
            btn_flag = true;

            // make frame database
            QSqlQuery qry;
            QString username;
            // i) first find user name
            qry.exec("SELECT user_name FROM userTable WHERE implement='Y'");
            qry.next(); // only 1 orw
            //qDebug() << qry.value(0); // ex) QVariant(QString, "kyujin")
            username = qry.value(0).toString();
            int count=0;
            if(qry.exec("SELECT * FROM planning WHERE username='"+username+"' and month="+QString::number(g_month)+" and year="+QString::number(g_year)+"")){
                while(qry.next()){
                    count ++;
                }
                qDebug() << count;
            }

            if(count==0){
                if(!(qry.exec("INSERT INTO planning VALUES ('"+username+"', 'Meal', 0, 'expense', "+QString::number(g_month)+", "+QString::number(g_year)+")"))){
                    qDebug() << qry.lastError().text();
                }
                qry.exec("INSERT INTO planning VALUES ('"+username+"', 'Car', 0, 'expense', "+QString::number(g_month)+", "+QString::number(g_year)+")");
                qry.exec("INSERT INTO planning VALUES ('"+username+"', 'Education', 0, 'expense', "+QString::number(g_month)+", "+QString::number(g_year)+")");
                qry.exec("INSERT INTO planning VALUES ('"+username+"', 'Living', 0, 'expense', "+QString::number(g_month)+", "+QString::number(g_year)+")");
                qry.exec("INSERT INTO planning VALUES ('"+username+"', 'Travel', 0, 'expense', "+QString::number(g_month)+", "+QString::number(g_year)+")");
                qry.exec("INSERT INTO planning VALUES ('"+username+"', 'Medicine', 0, 'expense', "+QString::number(g_month)+", "+QString::number(g_year)+")");
                qry.exec("INSERT INTO planning VALUES ('"+username+"', 'Cafe/Snack', 0, 'expense', "+QString::number(g_month)+", "+QString::number(g_year)+")");
                qry.exec("INSERT INTO planning VALUES ('"+username+"', 'Daily', 0, 'expense', "+QString::number(g_month)+", "+QString::number(g_year)+")");
                qry.exec("INSERT INTO planning VALUES ('"+username+"', 'Exercise', 0, 'expense', "+QString::number(g_month)+", "+QString::number(g_year)+")");
                qry.exec("INSERT INTO planning VALUES ('"+username+"', 'Clothes', 0, 'expense', "+QString::number(g_month)+", "+QString::number(g_year)+")");
                qry.exec("INSERT INTO planning VALUES ('"+username+"', 'Beauty', 0, 'expense', "+QString::number(g_month)+", "+QString::number(g_year)+")");
                //qry.exec("INSERT INTO planning VALUES ('"+username+"', 'Other', 0, 'expense', "+QString::number(g_month)+", "+QString::number(g_year)+")");
                qry.exec("INSERT INTO planning VALUES ('"+username+"', 'Transportation', 0, 'expense', "+QString::number(g_month)+", "+QString::number(g_year)+")");
                //qry.exec("INSERT INTO planning VALUES ('"+username+"', 'other1', 0, 'expense', "+QString::number(g_month)+", "+QString::number(g_year)+")");

            }

        } else{
            bool text_flag = true;
            ui -> edit_btn -> setStyleSheet("background-color:rgb(255,255,255); font: 700 14pt '맑은 고딕'; color: rgb(0,255,0); border: 0px;");
            ui -> edit_btn -> setText("Edit");
            //ui -> go_adding -> setStyleSheet("border: 0px; background-color:rgba(255,255,255,1.0)");
            btn_flag = false;
            ui -> meal_money -> setReadOnly(text_flag);
            ui -> car_money -> setReadOnly(text_flag);
            ui -> cloth_money -> setReadOnly(text_flag);
            ui -> daily_money -> setReadOnly(text_flag);
            ui -> edu_money -> setReadOnly(text_flag);
            ui -> exercise_money -> setReadOnly(text_flag);
            ui -> living_money -> setReadOnly(text_flag);
            ui -> snack_money -> setReadOnly(text_flag);
            ui -> trans_money -> setReadOnly(text_flag);
            ui -> travel_money -> setReadOnly(text_flag);
            ui -> medicine_money -> setReadOnly(text_flag);
            ui -> beauty_money -> setReadOnly(text_flag);
            ui -> other_money1 -> setReadOnly(text_flag);
            ui -> other_money2 -> setReadOnly(text_flag);
            ui -> other_money3 -> setReadOnly(text_flag);
            ui -> other_money4 -> setReadOnly(text_flag);

            // Font setting
            QFontDatabase::addApplicationFont(":/font/Noto SansKR-Medium.otf");
            QFont noto("Noto SansKR-Medium", 12, QFont::Normal);

            ui -> category1 -> setReadOnly(text_flag);
            ui -> category1 -> setStyleSheet("background-color: rgb(240, 240, 240); color: rgb(115, 115, 115); font: 12pt;");
            ui -> category1 -> setFont(noto);
            ui -> category2 -> setReadOnly(text_flag);
            ui -> category2 -> setStyleSheet("background-color: rgb(240, 240, 240); color: rgb(115, 115, 115); font: 12pt;");
            ui -> category2 -> setFont(noto);
            ui -> category3 -> setReadOnly(text_flag);
            ui -> category3 -> setStyleSheet("background-color: rgb(240, 240, 240); color: rgb(115, 115, 115); font: 12pt;");
            ui -> category3 -> setFont(noto);
            ui -> category4 -> setReadOnly(text_flag);
            ui -> category4 -> setStyleSheet("background-color: rgb(240, 240, 240); color: rgb(115, 115, 115); font: 12pt;");
            ui -> category4 -> setFont(noto);

            // save
            QString username, category, money, month, year;
            month = QString::number(g_month);
            year = QString::number(g_year);

            // record database
            QSqlQuery qry;
            // i) first find user name
            qry.exec("SELECT user_name FROM userTable WHERE implement='Y'");
            qry.next(); // only 1 orw
            //qDebug() << qry.value(0); // ex) QVariant(QString, "kyujin")
            username = qry.value(0).toString();

            // checking all category
            // 1)
            category = "Meal";
            money = ui -> meal_money -> text(); // now Qstring form. We will change integer type!
            string money_check = money.toStdString(); // QString -> string
            bool money_flag = check_money_types(money_check);
            if (money_flag==false){ // checking money is integer?
                qDebug() << "The money input type is not integer.";
                money = "0";
            }
            qry.exec("UPDATE planning SET money="+money+" WHERE username= '"+username+"' and category='"+category+"' and month="+QString::number(g_month)+" and year="+QString::number(g_year)+"");
            //qry.exec("INSERT INTO planning VALUES ('"+username+"', 'Meal', 0, 'expense', "+QString::number(g_month)+", "+QString::number(g_year)+"");

            // 2)
            category = "Car";
            money = ui -> car_money -> text(); // now Qstring form. We will change integer type!
            money_check = money.toStdString(); // QString -> string
            money_flag = check_money_types(money_check);
            if (money_flag==false){ // checking money is integer?
                qDebug() << "The car input type is not integer.";
                money = "0";
            }
            qry.exec("UPDATE planning SET money="+money+" WHERE username= '"+username+"' and category='"+category+"' and month="+QString::number(g_month)+" and year="+QString::number(g_year)+"");

            // 3)
            category = "Clothes";
            money = ui -> cloth_money -> text(); // now Qstring form. We will change integer type!
            money_check = money.toStdString(); // QString -> string
            money_flag = check_money_types(money_check);
            if (money_flag==false){ // checking money is integer?
                qDebug() << "The cloth input type is not integer.";
                money = "0";
            }
            qry.exec("UPDATE planning SET money="+money+" WHERE username= '"+username+"' and category='"+category+"' and month="+QString::number(g_month)+" and year="+QString::number(g_year)+"");

            // 4)
            category = "Education";
            money = ui -> edu_money -> text(); // now Qstring form. We will change integer type!
            money_check = money.toStdString(); // QString -> string
            money_flag = check_money_types(money_check);
            if (money_flag==false){ // checking money is integer?
                qDebug() << "The edu input type is not integer.";
                money = "0";
            }
            qry.exec("UPDATE planning SET money="+money+" WHERE username= '"+username+"' and category='"+category+"' and month="+QString::number(g_month)+" and year="+QString::number(g_year)+"");

            // 5)
            category = "Beauty";
            money = ui -> beauty_money -> text(); // now Qstring form. We will change integer type!
            money_check = money.toStdString(); // QString -> string
            money_flag = check_money_types(money_check);
            if (money_flag==false){ // checking money is integer?
                qDebug() << "The beauty input type is not integer.";
                money = "0";
            }
            qry.exec("UPDATE planning SET money="+money+" WHERE username= '"+username+"' and category='"+category+"' and month="+QString::number(g_month)+" and year="+QString::number(g_year)+"");

            // 6)
            category = "Medicine";
            money = ui -> medicine_money -> text(); // now Qstring form. We will change integer type!
            money_check = money.toStdString(); // QString -> string
            money_flag = check_money_types(money_check);
            if (money_flag==false){ // checking money is integer?
                qDebug() << "The medicine input type is not integer.";
                money = "0";
            }
            qry.exec("UPDATE planning SET money="+money+" WHERE username= '"+username+"' and category='"+category+"' and month="+QString::number(g_month)+" and year="+QString::number(g_year)+"");

            // 7)
            category = "Travel";
            money = ui -> travel_money -> text(); // now Qstring form. We will change integer type!
            money_check = money.toStdString(); // QString -> string
            money_flag = check_money_types(money_check);
            if (money_flag==false){ // checking money is integer?
                qDebug() << "The travel input type is not integer.";
                money = "0";
            }
            qry.exec("UPDATE planning SET money="+money+" WHERE username= '"+username+"' and category='"+category+"' and month="+QString::number(g_month)+" and year="+QString::number(g_year)+"");

            // 8)
            category = "Cafe/Snack";
            money = ui -> snack_money -> text(); // now Qstring form. We will change integer type!
            money_check = money.toStdString(); // QString -> string
            money_flag = check_money_types(money_check);
            if (money_flag==false){ // checking money is integer?
                qDebug() << "The cafe input type is not integer.";
                money = "0";
            }
            qry.exec("UPDATE planning SET money="+money+" WHERE username= '"+username+"' and category='"+category+"' and month="+QString::number(g_month)+" and year="+QString::number(g_year)+"");

            // 9)
            /*
            category = "Other";
            money = ui -> other_money1 -> text(); // now Qstring form. We will change integer type!
            money_check = money.toStdString(); // QString -> string
            money_flag = check_money_types(money_check);
            if (money_flag==false){ // checking money is integer?
                qDebug() << "The other input type is not integer.";
                money = "0";
            }
            qry.exec("UPDATE planning SET money="+money+" WHERE username= '"+username+"' and category='"+category+"' and month="+QString::number(g_month)+" and year="+QString::number(g_year)+"");
            */

            // 9)
            category = "Living";
            money = ui -> living_money -> text(); // now Qstring form. We will change integer type!
            money_check = money.toStdString(); // QString -> string
            money_flag = check_money_types(money_check);
            if (money_flag==false){ // checking money is integer?
                qDebug() << "The live input type is not integer.";
                money = "0";
            }
            qry.exec("UPDATE planning SET money="+money+" WHERE username= '"+username+"' and category='"+category+"' and month="+QString::number(g_month)+" and year="+QString::number(g_year)+"");

            // 10)
            category = "Exercise";
            money = ui -> exercise_money -> text(); // now Qstring form. We will change integer type!
            money_check = money.toStdString(); // QString -> string
            money_flag = check_money_types(money_check);
            if (money_flag==false){ // checking money is integer?
                qDebug() << "The exer input type is not integer.";
                money = "0";
            }
            qry.exec("UPDATE planning SET money="+money+" WHERE username= '"+username+"' and category='"+category+"' and month="+QString::number(g_month)+" and year="+QString::number(g_year)+"");

            // 11)
            category = "Daily";
            money = ui -> daily_money -> text(); // now Qstring form. We will change integer type!
            money_check = money.toStdString(); // QString -> string
            money_flag = check_money_types(money_check);
            if (money_flag==false){ // checking money is integer?
                qDebug() << "The daily input type is not integer.";
                money = "0";
            }
            qry.exec("UPDATE planning SET money="+money+" WHERE username= '"+username+"' and category='"+category+"' and month="+QString::number(g_month)+" and year="+QString::number(g_year)+"");

            // 12)
            category = "Transportation";
            money = ui -> trans_money -> text(); // now Qstring form. We will change integer type!
            money_check = money.toStdString(); // QString -> string
            money_flag = check_money_types(money_check);
            if (money_flag==false){ // checking money is integer?
                qDebug() << "The trans input type is not integer.";
                money = "0";
            }
            qry.exec("UPDATE planning SET money="+money+" WHERE username= '"+username+"' and category='"+category+"' and month="+QString::number(g_month)+" and year="+QString::number(g_year)+"");

            // ################################################################################
            // 13)
            QString text1 = ui->category1->text();
            if(text1 != ""){
                qry.exec("SELECT category1 FROM userCategory WHERE username='"+username+"' and month="+QString::number(g_month)+" and year="+QString::number(g_year)+"");
                qry.next();
                QString category1_name = qry.value(0).toString();
                if(category1_name=="no"){ // first
                    qry.exec("INSERT INTO planning VALUES ('"+username+"', '"+text1+"', 0, 'expense', "+QString::number(g_month)+", "+QString::number(g_year)+")");
                    //qry.exec("UPDATE userCategory SET category1='"+text1+"' WHERE username= '"+username+"' and month="+QString::number(g_month)+" and year="+QString::number(g_year)+"");
                } else if (category1_name != text1){
                    // delete
                    //qry.exec("UPDATE userCategory SET category1='"+text1+"' WHERE username= '"+username+"' and month="+QString::number(g_month)+" and year="+QString::number(g_year)+"");
                    if(!qry.exec("DELETE FROM planning WHERE username='"+username+"' and category='"+category1_name+"' and month="+QString::number(g_month)+" and year="+QString::number(g_year)+"")){
                        qDebug() << qry.lastError().text();
                    }
                    qry.exec("INSERT INTO planning VALUES ('"+username+"', '"+text1+"', 0, 'expense', "+QString::number(g_month)+", "+QString::number(g_year)+")");
                }

                money = ui -> other_money1 -> text();
                money_check = money.toStdString(); // QString -> string
                money_flag = check_money_types(money_check);
                if (money_flag==false){ // checking money is integer?
                    qDebug() << "The input type is not integer.";
                    money = "0";
                }
                qry.exec("UPDATE planning SET money="+money+" WHERE username= '"+username+"' and category='"+text1+"' and month="+QString::number(g_month)+" and year="+QString::number(g_year)+"");
                qry.exec("UPDATE userCategory SET category1='"+text1+"' WHERE username= '"+username+"' and month="+QString::number(g_month)+" and year="+QString::number(g_year)+"");

            } else {
                // delete
                qry.exec("SELECT category1 FROM userCategory WHERE username='"+username+"' and month="+QString::number(g_month)+" and year="+QString::number(g_year)+"");
                qry.next();
                QString category1_name = qry.value(0).toString();
                //qDebug() << category1_name;
                if(category1_name != "no"){
                    qDebug() << category1_name;
                    //qDebug() << text1;
                    qry.exec("DELETE FROM planning WHERE username='"+username+"' and category='"+category1_name+"' and month="+QString::number(g_month)+" and year="+QString::number(g_year)+"");
                }
                qry.exec("UPDATE userCategory SET category1='no' WHERE username= '"+username+"' and month="+QString::number(g_month)+" and year="+QString::number(g_year)+"");
                qDebug() << "check";
            }

            // 14)
            QString text2 = ui->category2->text();
            if(text2 != ""){
                qry.exec("SELECT category2 FROM userCategory WHERE username='"+username+"' and month="+QString::number(g_month)+" and year="+QString::number(g_year)+"");
                qry.next();
                QString category2_name = qry.value(0).toString();
                if(category2_name=="no"){ // first
                    qry.exec("INSERT INTO planning VALUES ('"+username+"', '"+text2+"', 0, 'expense', "+QString::number(g_month)+", "+QString::number(g_year)+")");
                    //qry.exec("UPDATE userCategory SET category1='"+text1+"' WHERE username= '"+username+"' and month="+QString::number(g_month)+" and year="+QString::number(g_year)+"");
                } else if (category2_name != text2){
                    // delete
                    //qry.exec("UPDATE userCategory SET category1='"+text1+"' WHERE username= '"+username+"' and month="+QString::number(g_month)+" and year="+QString::number(g_year)+"");
                    if(!qry.exec("DELETE FROM planning WHERE username='"+username+"' and category='"+category2_name+"' and month="+QString::number(g_month)+" and year="+QString::number(g_year)+"")){
                        qDebug() << qry.lastError().text();
                    }
                    qry.exec("INSERT INTO planning VALUES ('"+username+"', '"+text2+"', 0, 'expense', "+QString::number(g_month)+", "+QString::number(g_year)+")");
                }

                money = ui -> other_money2 -> text();
                money_check = money.toStdString(); // QString -> string
                money_flag = check_money_types(money_check);
                if (money_flag==false){ // checking money is integer?
                    qDebug() << "The input type is not integer.";
                    money = "0";
                }
                qry.exec("UPDATE planning SET money="+money+" WHERE username= '"+username+"' and category='"+text2+"' and month="+QString::number(g_month)+" and year="+QString::number(g_year)+"");
                qry.exec("UPDATE userCategory SET category2='"+text2+"' WHERE username= '"+username+"' and month="+QString::number(g_month)+" and year="+QString::number(g_year)+"");

            } else {
                // delete
                qry.exec("SELECT category2 FROM userCategory WHERE username='"+username+"' and month="+QString::number(g_month)+" and year="+QString::number(g_year)+"");
                qry.next();
                QString category2_name = qry.value(0).toString();
                //qDebug() << category1_name;
                if(category2_name != "no"){
                    qDebug() << category2_name;
                    //qDebug() << text1;
                    qry.exec("DELETE FROM planning WHERE username='"+username+"' and category='"+category2_name+"' and month="+QString::number(g_month)+" and year="+QString::number(g_year)+"");
                }
                qry.exec("UPDATE userCategory SET category2='no' WHERE username= '"+username+"' and month="+QString::number(g_month)+" and year="+QString::number(g_year)+"");
                qDebug() << "check";
            }

            // 15)
            QString text3 = ui->category3->text();
            if(text3 != ""){
                qry.exec("SELECT category3 FROM userCategory WHERE username='"+username+"' and month="+QString::number(g_month)+" and year="+QString::number(g_year)+"");
                qry.next();
                QString category3_name = qry.value(0).toString();
                if(category3_name=="no"){ // first
                    qry.exec("INSERT INTO planning VALUES ('"+username+"', '"+text3+"', 0, 'expense', "+QString::number(g_month)+", "+QString::number(g_year)+")");
                    //qry.exec("UPDATE userCategory SET category1='"+text1+"' WHERE username= '"+username+"' and month="+QString::number(g_month)+" and year="+QString::number(g_year)+"");
                } else if (category3_name != text3){
                    // delete
                    //qry.exec("UPDATE userCategory SET category1='"+text1+"' WHERE username= '"+username+"' and month="+QString::number(g_month)+" and year="+QString::number(g_year)+"");
                    if(!qry.exec("DELETE FROM planning WHERE username='"+username+"' and category='"+category3_name+"' and month="+QString::number(g_month)+" and year="+QString::number(g_year)+"")){
                        qDebug() << qry.lastError().text();
                    }
                    qry.exec("INSERT INTO planning VALUES ('"+username+"', '"+text3+"', 0, 'expense', "+QString::number(g_month)+", "+QString::number(g_year)+")");
                }

                money = ui -> other_money3 -> text();
                money_check = money.toStdString(); // QString -> string
                money_flag = check_money_types(money_check);
                if (money_flag==false){ // checking money is integer?
                    qDebug() << "The input type is not integer.";
                    money = "0";
                }
                qry.exec("UPDATE planning SET money="+money+" WHERE username= '"+username+"' and category='"+text3+"' and month="+QString::number(g_month)+" and year="+QString::number(g_year)+"");
                qry.exec("UPDATE userCategory SET category3='"+text3+"' WHERE username= '"+username+"' and month="+QString::number(g_month)+" and year="+QString::number(g_year)+"");

            } else {
                // delete
                qry.exec("SELECT category3 FROM userCategory WHERE username='"+username+"' and month="+QString::number(g_month)+" and year="+QString::number(g_year)+"");
                qry.next();
                QString category3_name = qry.value(0).toString();
                //qDebug() << category1_name;
                if(category3_name != "no"){
                    qDebug() << category3_name;
                    //qDebug() << text1;
                    qry.exec("DELETE FROM planning WHERE username='"+username+"' and category='"+category3_name+"' and month="+QString::number(g_month)+" and year="+QString::number(g_year)+"");
                }
                qry.exec("UPDATE userCategory SET category3='no' WHERE username= '"+username+"' and month="+QString::number(g_month)+" and year="+QString::number(g_year)+"");
                qDebug() << "check";
            }

            // 16)
            QString text4 = ui->category4->text();
            if(text4 != ""){
                qry.exec("SELECT category4 FROM userCategory WHERE username='"+username+"' and month="+QString::number(g_month)+" and year="+QString::number(g_year)+"");
                qry.next();
                QString category4_name = qry.value(0).toString();
                if(category4_name=="no"){ // first
                    qry.exec("INSERT INTO planning VALUES ('"+username+"', '"+text4+"', 0, 'expense', "+QString::number(g_month)+", "+QString::number(g_year)+")");
                    //qry.exec("UPDATE userCategory SET category1='"+text1+"' WHERE username= '"+username+"' and month="+QString::number(g_month)+" and year="+QString::number(g_year)+"");
                } else if (category4_name != text4){
                    // delete
                    //qry.exec("UPDATE userCategory SET category1='"+text1+"' WHERE username= '"+username+"' and month="+QString::number(g_month)+" and year="+QString::number(g_year)+"");
                    if(!qry.exec("DELETE FROM planning WHERE username='"+username+"' and category='"+category4_name+"' and month="+QString::number(g_month)+" and year="+QString::number(g_year)+"")){
                        qDebug() << qry.lastError().text();
                    }
                    qry.exec("INSERT INTO planning VALUES ('"+username+"', '"+text4+"', 0, 'expense', "+QString::number(g_month)+", "+QString::number(g_year)+")");
                }

                money = ui -> other_money4 -> text();
                money_check = money.toStdString(); // QString -> string
                money_flag = check_money_types(money_check);
                if (money_flag==false){ // checking money is integer?
                    qDebug() << "The input type is not integer.";
                    money = "0";
                }
                qry.exec("UPDATE planning SET money="+money+" WHERE username= '"+username+"' and category='"+text4+"' and month="+QString::number(g_month)+" and year="+QString::number(g_year)+"");
                qry.exec("UPDATE userCategory SET category4='"+text4+"' WHERE username= '"+username+"' and month="+QString::number(g_month)+" and year="+QString::number(g_year)+"");

            } else {
                // delete
                qry.exec("SELECT category4 FROM userCategory WHERE username='"+username+"' and month="+QString::number(g_month)+" and year="+QString::number(g_year)+"");
                qry.next();
                QString category4_name = qry.value(0).toString();
                //qDebug() << category1_name;
                if(category4_name != "no"){
                    qDebug() << category4_name;
                    //qDebug() << text1;
                    qry.exec("DELETE FROM planning WHERE username='"+username+"' and category='"+category4_name+"' and month="+QString::number(g_month)+" and year="+QString::number(g_year)+"");
                }
                qry.exec("UPDATE userCategory SET category4='no' WHERE username= '"+username+"' and month="+QString::number(g_month)+" and year="+QString::number(g_year)+"");
                qDebug() << "check";
            }



            qry.exec("SELECT money FROM planning WHERE username='"+username+"' and month="+QString::number(g_month)+" and year="+QString::number(g_year)+"");
            int predict = 0;
            while(qry.next()){
                predict += qry.value(0).toInt();
            }
            QString money_0 = QString::number(predict);
            ui -> expense_line -> setText(money_0+"₩");
        }
    } else {
        // add dialog
        qDebug() << "you not set planning.";
    }
}


void Planning::on_next_btn_clicked()
{
    // record database
    QSqlQuery qry;
    QString username;
    // i) first find user name
    qry.exec("SELECT user_name FROM userTable WHERE implement='Y'");
    qry.next(); // only 1 orw
    //qDebug() << qry.value(0); // ex) QVariant(QString, "kyujin")
    username = qry.value(0).toString();


    g_month += 1;
    if(g_month == 13){
        g_month = 1;
        g_year+=1;
    }

    // before not set planning
    if(g_year < cur_year){
        before_flag = true;

    } else if (g_year > cur_year){
        before_flag = false;

    } else {
        if(g_month < cur_month){
            before_flag = true;
        } else {
            before_flag = false;
        }
    }

    hide();
    Planning *new_page;
    new_page= new Planning(this);
    new_page->show();
}


void Planning::on_back_btn_clicked()
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
    g_month -= 1;
    if(g_month == 0){
        g_month = 12;
        g_year-=1;
    }

    // before not set planning
    if(g_year < cur_year){
        before_flag = true;

    } else if (g_year > cur_year){
        before_flag = false;

    } else {
        if(g_month < cur_month){
            before_flag = true;
        } else {
            before_flag = false;
        }
    }

    hide();
    Planning *new_page;
    new_page= new Planning(this);
    new_page->show();
}


void Planning::on_go_adding_clicked()
{
    if(before_flag==false){
        qDebug() << "Not yet.";
    } else {
        qDebug() << "Not adding.";
    }
}

