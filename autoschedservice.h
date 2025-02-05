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
    void set_manp_list();

    void sched_table_update(int start, int end);

    void sched_table_add();

    void sched_table_rm(int row);

    void update_sched_table_contents();
    void clear_sched_table_contents();

private slots:
    void on_listWidget_emps_itemSelectionChanged();

    void on_btn_empUpdate_clicked();

    void on_btn_empAdd_clicked();

    void on_btn_empDupe_clicked();

    void set_timeoff_list();

    void on_btn_empRm_clicked();

    void on_btn_empMoveUp_clicked();

    void on_btn_empMoveDown_clicked();

    void on_btn_schedCreate_clicked();

    void on_btn_schedClear_clicked();

    void on_tableWidget_schedule_itemSelectionChanged();

    void on_btn_schedAssign_clicked();

    void on_comboBox_shiftSelect_currentIndexChanged(int index);

    void on_btn_shiftUpdate_clicked();

    void on_btn_shiftSave_clicked();

    void on_btn_empSave_clicked();

    void on_pushButton_clicked();

    void on_listWidget_timeoff_currentRowChanged(int currentRow);

    void on_btn_timeoffAdd_clicked();

    void on_btn_timeoffUpdate_clicked();

private:
    Ui::autoschedservice *ui;
};
#endif // AUTOSCHEDSERVICE_H
