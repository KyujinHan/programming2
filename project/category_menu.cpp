#include "category_menu.h"
#include "ui_category_menu.h"
#include "recordplan.h"
#include <QLineEdit>
#include <string>
#include <QFontDatabase>

int currentnum;
int gl_count = 0;

category_menu::category_menu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::category_menu)
{
    ui->setupUi(this);
    QPixmap pix(":/images/categories.png");
    ui->category_pic->setPixmap(pix.scaled(375,812));

    set_frame();

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
    /*
    if (currentnum == 12){
        qry.exec("UPDATE userTable SET category="+QString::number(1)+" WHERE user_name= '"+username+"'");
    }
    */
    qry.exec("UPDATE userTable SET field_num="+field_num+" WHERE user_name= '"+username+"'");
}

void category_menu::set_frame(){
    // record database
    QSqlQuery qry;
    QString username;
    // i) first find user name
    qry.exec("SELECT user_name FROM userTable WHERE implement='Y'");
    qry.next(); // only 1 orw
    //qDebug() << qry.value(0); // ex) QVariant(QString, "kyujin")
    username = qry.value(0).toString();

    // choose month, year
    qry.exec("SELECT set_year, set_month FROM userTable WHERE implement='Y'");
    qry.next();
    int year = qry.value(0).toInt();
    int month = qry.value(1).toInt();
    // make category
    qry.exec("SELECT category1, category2, category3, category4 FROM userCategory WHERE username='"+username+"' and year="+QString::number(year)+" and month="+QString::number(month)+"");
    qry.next();
    QString category1 = qry.value(0).toString();
    QString category2 = qry.value(1).toString();
    QString category3 = qry.value(2).toString();
    QString category4 = qry.value(3).toString();
    // make btn
    gl_count = 0;
    if(category1 != "no"){
        QLabel *label = new QLabel(this);
        QPixmap pix(":/images/Other.png");
        label->setPixmap(pix.scaled(40,40));
        label->setGeometry(48+(gl_count*80), 450, 40, 40);
        label->setObjectName("label_"+QString::number(gl_count));

        // make btn
        QPushButton *btn = new QPushButton(this);
        btn->setStyleSheet("border: 5px; background-color:rgba(255,255,255,0.0)");
        btn->setGeometry(48+(gl_count*80), 450, 40, 60);
        //btn->hide(); // hide
        btn->setObjectName("category_btn_"+QString::number(gl_count));

        // make text
        // Font setting
        QFontDatabase::addApplicationFont(":/font/Noto SansKR-Medium.otf");
        QFont noto("Noto SansKR-Medium", 12, QFont::Medium);

        QLineEdit *text_title = new QLineEdit(this); // title
        text_title->setText(category1);
        text_title->setGeometry(48+(gl_count*80), 494, 50, 20);
        text_title->setStyleSheet("color: rgb(0,0,0); background-color: rgb(255, 255, 255); border: 0px;"); //setStyleSheet("font: 700 9pt '맑은 고딕'; color: rgb(0, 0, 0); background-color: rgb(255, 255, 255); border: 0px");
        text_title -> setFont(noto);
        text_title->setAlignment(Qt::AlignHCenter);
        text_title->setReadOnly(true);
        text_title->setObjectName("text_title_"+QString::number(gl_count));

        //connect button
        QString text_btn = "category_btn_"+QString::number(gl_count);
        QPushButton *category_btn;
        category_btn = findChild<QPushButton*>(text_btn);
        connect(category_btn, &QPushButton::released, this, &category_menu::on_categorybutton);
        btn->setCursor(Qt::OpenHandCursor);
        //btn->setEnabled(false); // not using this time

        gl_count++;


    }
    if(category2 != "no"){
        QLabel *label = new QLabel(this);
        QPixmap pix(":/images/Other.png");
        label->setPixmap(pix.scaled(40,40));
        label->setGeometry(48+(gl_count*80), 450, 40, 40);
        label->setObjectName("label_"+QString::number(gl_count));

        // make btn
        QPushButton *btn = new QPushButton(this);
        btn->setStyleSheet("border: 5px; background-color:rgba(255,255,255,0.0)");
        btn->setGeometry(48+(gl_count*80), 450, 40, 60);
        //btn->hide(); // hide
        btn->setObjectName("category_btn_"+QString::number(gl_count));

        // make text
        // Font setting
        QFontDatabase::addApplicationFont(":/font/Noto SansKR-Medium.otf");
        QFont noto("Noto SansKR-Medium", 12, QFont::Medium);

        QLineEdit *text_title = new QLineEdit(this); // title
        text_title->setText(category2);
        text_title->setGeometry(48+(gl_count*80), 494, 50, 20);
        text_title->setStyleSheet("color: rgb(0,0,0); background-color: rgb(255, 255, 255); border: 0px;"); //setStyleSheet("font: 700 9pt '맑은 고딕'; color: rgb(0, 0, 0); background-color: rgb(255, 255, 255); border: 0px");
        text_title -> setFont(noto);
        text_title->setAlignment(Qt::AlignHCenter);
        text_title->setReadOnly(true);
        text_title->setObjectName("text_title_"+QString::number(gl_count));

        //connect button
        QString text_btn = "category_btn_"+QString::number(gl_count);
        QPushButton *category_btn;
        category_btn = findChild<QPushButton*>(text_btn);
        connect(category_btn, &QPushButton::released, this, &category_menu::on_categorybutton);
        btn->setCursor(Qt::OpenHandCursor);
        //btn->setEnabled(false); // not using this time

        gl_count++;

    }
    if(category3 != "no"){
        QLabel *label = new QLabel(this);
        QPixmap pix(":/images/Other.png");
        label->setPixmap(pix.scaled(40,40));
        label->setGeometry(48+(gl_count*80), 450, 40, 40);
        label->setObjectName("label_"+QString::number(gl_count));

        // make text
        // Font setting
        QFontDatabase::addApplicationFont(":/font/Noto SansKR-Medium.otf");
        QFont noto("Noto SansKR-Medium", 12, QFont::Medium);

        QLineEdit *text_title = new QLineEdit(this); // title
        text_title->setText(category3);
        text_title->setGeometry(48+(gl_count*80), 494, 50, 20);
        text_title->setStyleSheet("color: rgb(0,0,0); background-color: rgb(255, 255, 255); border: 0px;"); //setStyleSheet("font: 700 9pt '맑은 고딕'; color: rgb(0, 0, 0); background-color: rgb(255, 255, 255); border: 0px");
        text_title -> setFont(noto);
        text_title->setAlignment(Qt::AlignHCenter);
        text_title->setReadOnly(true);
        text_title->setObjectName("text_title_"+QString::number(gl_count));

        // make btn
        QPushButton *btn = new QPushButton(this);
        btn->setStyleSheet("border: 5px; background-color:rgba(255,255,255,0.0)");
        btn->setGeometry(48+(gl_count*80), 450, 40, 60);
        //btn->hide(); // hide
        btn->setObjectName("category_btn_"+QString::number(gl_count));

        //connect button
        QString text_btn = "category_btn_"+QString::number(gl_count);
        QPushButton *category_btn;
        category_btn = findChild<QPushButton*>(text_btn);
        connect(category_btn, &QPushButton::released, this, &category_menu::on_categorybutton);
        btn->setCursor(Qt::OpenHandCursor);
        //btn->setEnabled(false); // not using this time

        gl_count++;
    }
    if(category4 != "no"){
        QLabel *label = new QLabel(this);
        QPixmap pix(":/images/Other.png");
        label->setPixmap(pix.scaled(40,40));
        label->setGeometry(48+(gl_count*80), 450, 40, 40);
        label->setObjectName("label_"+QString::number(gl_count));

        // make btn
        QPushButton *btn = new QPushButton(this);
        btn->setStyleSheet("border: 5px; background-color:rgba(255,255,255,0.0)");
        btn->setGeometry(48+(gl_count*80), 450, 40, 60);
        //btn->hide(); // hide
        btn->setObjectName("category_btn_"+QString::number(gl_count));

        // make text
        // Font setting
        QFontDatabase::addApplicationFont(":/font/Noto SansKR-Medium.otf");
        QFont noto("Noto SansKR-Medium", 12, QFont::Medium);

        QLineEdit *text_title = new QLineEdit(this); // title
        text_title->setText(category4);
        text_title->setGeometry(48+(gl_count*80), 494, 50, 20);
        text_title->setStyleSheet("color: rgb(0,0,0); background-color: rgb(255, 255, 255); border: 0px;"); //setStyleSheet("font: 700 9pt '맑은 고딕'; color: rgb(0, 0, 0); background-color: rgb(255, 255, 255); border: 0px");
        text_title -> setFont(noto);
        text_title->setAlignment(Qt::AlignHCenter);
        text_title->setReadOnly(true);
        text_title->setObjectName("text_title_"+QString::number(gl_count));

        //connect button
        QString text_btn = "category_btn_"+QString::number(gl_count);
        QPushButton *category_btn;
        category_btn = findChild<QPushButton*>(text_btn);
        connect(category_btn, &QPushButton::released, this, &category_menu::on_categorybutton);
        btn->setCursor(Qt::OpenHandCursor);
        //btn->setEnabled(false); // not using this time

        gl_count++;
    }


}

void category_menu::on_categorybutton(){
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
    ui -> beauty_btn -> setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.3)");


    //ui -> other_btn -> setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.0)");

    QPushButton* buttonSender = qobject_cast<QPushButton*>(sender());
    QString buttonText = buttonSender->objectName();
    QString order;
    order = buttonText.split("_").back();
    //qDebug() << order;

    QPushButton *category_btn;
    for(int i=0; i<gl_count; i++){
        QString text_btn = "category_btn_"+QString::number(i);
        if(i==order.toInt()){
            category_btn = findChild<QPushButton*>(text_btn);
            category_btn->setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.0)");

            // record database
            QSqlQuery qry;
            QString username;
            // i) first find user name
            qry.exec("SELECT user_name FROM userTable WHERE implement='Y'");
            qry.next(); // only 1 orw
            //qDebug() << qry.value(0); // ex) QVariant(QString, "kyujin")
            username = qry.value(0).toString();

            // choose month, year
            qry.exec("SELECT set_year, set_month FROM userTable WHERE implement='Y'");
            qry.next();
            int year = qry.value(0).toInt();
            int month = qry.value(1).toInt();
            // make category
            qry.exec("SELECT category1, category2, category3, category4 FROM userCategory WHERE username='"+username+"' and year="+QString::number(year)+" and month="+QString::number(month)+"");
            qry.next();
            QString category = qry.value(i).toString();

            qry.exec("UPDATE userTable SET custom_category='"+category+"' WHERE user_name= '"+username+"'");

        } else {
            category_btn = findChild<QPushButton*>(text_btn);
            category_btn->setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.3)");
        }
    }

    currentnum = 12;
    check_category(currentnum);
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
    //ui -> other_btn -> setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.3)");

    QPushButton *category_btn;
    for(int i=0; i<gl_count; i++){
        QString text_btn = "category_btn_"+QString::number(i);
        category_btn = findChild<QPushButton*>(text_btn);
        category_btn->setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.3)");
    }

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
    //ui -> other_btn -> setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.3)");
    QPushButton *category_btn;
    for(int i=0; i<gl_count; i++){
        QString text_btn = "category_btn_"+QString::number(i);
        category_btn = findChild<QPushButton*>(text_btn);
        category_btn->setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.3)");
    }

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
    //ui -> other_btn -> setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.3)");
    QPushButton *category_btn;
    for(int i=0; i<gl_count; i++){
        QString text_btn = "category_btn_"+QString::number(i);
        category_btn = findChild<QPushButton*>(text_btn);
        category_btn->setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.3)");
    }

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
    //ui -> other_btn -> setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.3)");

    QPushButton *category_btn;
    for(int i=0; i<gl_count; i++){
        QString text_btn = "category_btn_"+QString::number(i);
        category_btn = findChild<QPushButton*>(text_btn);
        category_btn->setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.3)");
    }

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
    //ui -> other_btn -> setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.3)");
    QPushButton *category_btn;
    for(int i=0; i<gl_count; i++){
        QString text_btn = "category_btn_"+QString::number(i);
        category_btn = findChild<QPushButton*>(text_btn);
        category_btn->setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.3)");
    }

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
    //ui -> other_btn -> setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.3)");
    QPushButton *category_btn;
    for(int i=0; i<gl_count; i++){
        QString text_btn = "category_btn_"+QString::number(i);
        category_btn = findChild<QPushButton*>(text_btn);
        category_btn->setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.3)");
    }

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
    //ui -> other_btn -> setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.3)");
    QPushButton *category_btn;
    for(int i=0; i<gl_count; i++){
        QString text_btn = "category_btn_"+QString::number(i);
        category_btn = findChild<QPushButton*>(text_btn);
        category_btn->setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.3)");
    }

    //currentnum = 6;
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
    //ui -> other_btn -> setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.3)");
    QPushButton *category_btn;
    for(int i=0; i<gl_count; i++){
        QString text_btn = "category_btn_"+QString::number(i);
        category_btn = findChild<QPushButton*>(text_btn);
        category_btn->setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.3)");
    }

    //currentnum = 7;
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
    //ui -> other_btn -> setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.3)");
    QPushButton *category_btn;
    for(int i=0; i<gl_count; i++){
        QString text_btn = "category_btn_"+QString::number(i);
        category_btn = findChild<QPushButton*>(text_btn);
        category_btn->setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.3)");
    }

    //currentnum = 8;
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
    //ui -> other_btn -> setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.3)");
    QPushButton *category_btn;
    for(int i=0; i<gl_count; i++){
        QString text_btn = "category_btn_"+QString::number(i);
        category_btn = findChild<QPushButton*>(text_btn);
        category_btn->setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.3)");
    }

    //currentnum = 9;
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
    //ui -> other_btn -> setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.3)");
    QPushButton *category_btn;
    for(int i=0; i<gl_count; i++){
        QString text_btn = "category_btn_"+QString::number(i);
        category_btn = findChild<QPushButton*>(text_btn);
        category_btn->setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.3)");
    }

    //currentnum = 10;
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
    //ui -> other_btn -> setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.3)");
    QPushButton *category_btn;
    for(int i=0; i<gl_count; i++){
        QString text_btn = "category_btn_"+QString::number(i);
        category_btn = findChild<QPushButton*>(text_btn);
        category_btn->setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.3)");
    }

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


/*
void category_menu::on_other_btn_clicked()
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
    ui -> beauty_btn -> setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.3)");
    ui -> other_btn -> setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.0)");
    currentnum = 12;
    check_category(currentnum);
}
*/
