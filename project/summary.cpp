#include "summary.h"
#include "ui_summary.h"
#include "secmainwindow.h"

summary::summary(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::summary)
{
    ui->setupUi(this);
    QPixmap pix(":/images/BackgroundFinal.png");
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

