#ifndef AUTOSCHEDSERVICE_H
#define AUTOSCHEDSERVICE_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class autoschedservice; }
QT_END_NAMESPACE

class autoschedservice : public QMainWindow
{
    Q_OBJECT

public:
    autoschedservice(QWidget *parent = nullptr);
    ~autoschedservice();

    void set_emp_list();

private slots:
    void on_listWidget_emps_itemSelectionChanged();

    void on_btn_empUpdate_clicked();

    void on_btn_empAdd_clicked();

private:
    Ui::autoschedservice *ui;
};
#endif // AUTOSCHEDSERVICE_H
