#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>
#include <QtDebug>
#include <QFileInfo>
#include "secmainwindow.h"

#include <iostream>
using namespace std;


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_loginButton_clicked();

    void on_signupButton_clicked();

private:
    Ui::MainWindow *ui;
    Secmainwindow *secmain_page;

    // Database
    QSqlDatabase mydb;
};

#endif // MAINWINDOW_H
