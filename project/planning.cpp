#include "planning.h"
#include "ui_planning.h"
#include "secmainwindow.h"
//#include <QScrollArea>

Planning::Planning(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Planning)
{
    ui->setupUi(this);
    QPixmap pix(":/images/Planning.png");
    ui->pic_plan->setPixmap(pix.scaled(375,1376));

}

Planning::~Planning()
{
    delete ui;
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
}

