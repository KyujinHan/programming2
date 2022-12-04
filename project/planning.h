#ifndef PLANNING_H
#define PLANNING_H

#include <QDialog>

//class QScrollArea;

namespace Ui {
class Planning;
}

class Planning : public QDialog
{
    Q_OBJECT

public:
    explicit Planning(QWidget *parent = nullptr);
    ~Planning();

private slots:
    void on_go_secmain_clicked();

    void on_verticalScrollBar_sliderMoved(int position);

    void on_edit_btn_clicked();

    void set_frame();

    void on_next_btn_clicked();

    void on_back_btn_clicked();

    void on_go_adding_clicked();

private:

    Ui::Planning *ui;
    //QScrollArea *scrollArea;
};

#endif // PLANNING_H
