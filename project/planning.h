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

private:
    Ui::Planning *ui;
    //QScrollArea *scrollArea;
};

#endif // PLANNING_H
