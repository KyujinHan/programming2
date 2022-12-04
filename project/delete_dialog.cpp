#include "delete_dialog.h"
#include "ui_delete_dialog.h"

delete_Dialog::delete_Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::delete_Dialog)
{
    ui->setupUi(this);
}

delete_Dialog::~delete_Dialog()
{
    delete ui;
}

void delete_Dialog::on_yesButton_clicked(){

}
