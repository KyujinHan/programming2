#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QPixmap>
#include <cctype>
#include <string>
#include <QDir>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPixmap pix(":/images/signup.jpg");
    /*
    QPixmap pix(":/images/BackgroundFinal.png");
    ui->label_pic->setPixmap(pix.scaled(375,812));
    */

    // get path
    //qDebug() << QDir::currentPath();
    //QString path_q = QDir::currentPath();
    //path_q = path_q + "/project_data.db";
    //string path = path_q.toStdString();
    //string ab_path = path + "/project_data.db";
    //cout << ab_path;

    // Database
    mydb = QSqlDatabase::addDatabase("QSQLITE"); // database make object
    if(QSysInfo::productType()=="osx"){ // mac
        mydb.setDatabaseName("../../../project_data.db"); // database name
    } else { //arm or window
        mydb.setDatabaseName("./project_data.db"); // database name
    }

    if(!mydb.open()){
        ui -> check_label -> setText("Not connected database"); // label is objectName
    } else {
        ui -> check_label -> setText("Connected database");
    }
    ui -> line_username -> setStyleSheet("border: 0px; background-color:rgba(255,255,255,0.0)");

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_loginButton_clicked()
{
    // database and login
    QString username;
    username = ui -> line_username -> text();
    // user login
    QSqlQuery qry;
    int count=0;
    if(qry.exec("SELECT user_name FROM userTable WHERE user_name= '"+username+"'")){
        while(qry.next()){ // check person (we expected 1)
            count++;
        }
    } else {
        qDebug() << qry.lastError().text();
        return;
    }

    if (count==1){
        // Login user checking process
        qry.exec("UPDATE userTable SET implement='Y' WHERE user_name= '"+username+"'");
        qry.exec("UPDATE userTable SET implement='N' WHERE user_name!= '"+username+"'");

        // page move
        hide();
        secmain_page = new Secmainwindow(this);
        secmain_page->show(); // show next page
    }else{
        ui -> check_label -> setText("There is no person name");
    }
}

bool check_no_alpha(string user){
    // It is empty
    if(user.size()==0){
        return true;
    }

    for (char i : user){
        if (!isalpha(i)){
            return true;
        }
    }
    return false;
}

void MainWindow::on_signupButton_clicked()
{
    // database and sign up
    QString username;
    username = ui -> line_username -> text();
    string user = username.toStdString(); // Qstring -> string
    bool flag = check_no_alpha(user); // true or flase
    if (flag){ // check alphabet name
        ui -> check_label -> setText("It is not alpha");
    } else{
        QSqlQuery qry;
        int count = 0; // counting
         ui -> check_label -> setText(username);
        if (qry.exec("SELECT user_name FROM userTable WHERE user_name='"+username+"'")){ // SELECT * FROM ~~
            while(qry.next()){
                count++; // check person (we expected 0)
            }
        } else{
            qDebug() << qry.lastError().text();
            return;
        }

        // Check unique person
        if (count == 0){
            qry.exec("INSERT INTO userTable (user_name) VALUES ('"+username+"')"); // adding new person
            ui -> check_label -> setText("Completed sign up!!");
        } else {
            ui -> check_label -> setText("There is same person name!"); // username will unique.
        }

        /*
        hide();
        secmain_page = new Secmainwindow(this);
        secmain_page->show(); // show next page
        */
    }
}

