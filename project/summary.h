#ifndef SUMMARY_H
#define SUMMARY_H

#include <QDialog>

// summary page class
namespace Ui {
class summary;
}

class summary : public QDialog
{
    Q_OBJECT

public:
    explicit summary(QWidget *parent = nullptr);
    ~summary();

private slots:
    void on_go_secpage_clicked();

private:
    Ui::summary *ui;
    // Secmainwindow *secmain_page;
};


#endif // SUMMARY_H
