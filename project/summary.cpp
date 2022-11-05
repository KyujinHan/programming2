#include "summary.h"
#include "ui_summary.h"
#include "secmainwindow.h"

summary::summary(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::summary)
{
    ui->setupUi(this);
    QPixmap pix(":/images/summary_page.png");
    ui->summary_pic->setPixmap(pix.scaled(375,812));
}

summary::~summary()
{
    delete ui;
}

void summary::on_go_secpage_clicked()
{
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
}


void summary::on_year_btn_clicked()
{
    ui->month_btn->setStyleSheet("background-color:rgb(255,255,255); font: 700 11pt '맑은 고딕'; color: rgb(0,0,0); border: 0px solid rgb(0,0,0); border-radius: 10px;");
    ui->year_btn->setStyleSheet("background-color:rgb(0,255,0); font: 700 11pt '맑은 고딕'; color: rgb(255,255,255); border: 2px solid rgb(0,0,0); border-radius: 10px;");
    ui->week_btn->setStyleSheet("background-color:rgb(255,255,255); font: 700 11pt '맑은 고딕'; color: rgb(0,0,0); border: 0px solid rgb(0,0,0); border-radius: 10px;");
}


void summary::on_week_btn_clicked()
{
    ui->year_btn->setStyleSheet("background-color:rgb(255,255,255); font: 700 11pt '맑은 고딕'; color: rgb(0,0,0); border: 0px solid rgb(0,0,0); border-radius: 10px;");
    ui->week_btn->setStyleSheet("background-color:rgb(0,255,0); font: 700 11pt '맑은 고딕'; color: rgb(255,255,255); border: 2px solid rgb(0,0,0); border-radius: 10px;");
    ui->month_btn->setStyleSheet("background-color:rgb(255,255,255); font: 700 11pt '맑은 고딕'; color: rgb(0,0,0); border: 0px solid rgb(0,0,0); border-radius: 10px;");
}

