#include "autoschedservice.h"
#include "ui_autoschedservice.h"

#include <algorithm>                    // Needed for std::min

#include "src/public/time_conv.hpp"

#include "src/classes/Employee.hpp"
#include "src/classes/Manpower.hpp"
#include "src/classes/Schedule.hpp"

#include "src/public/load_json.hpp"
#include "src/public/helpers.hpp"
#include "src/public/scheduler.hpp"


/*
TODO:
    Need to add some string validation to time_to_float()
    CRASH : Add employee -> Duplicate added employee -> Create schedule -> crash

*/

// Create the master vectors of employees and manpower, and the main schedule object.
std::vector<Employee> empvec;
std::vector<Manpower> manpvec;
Schedule schedule;

autoschedservice::autoschedservice(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::autoschedservice)
{
    empvec.reserve(40);
    load_employees(empvec);
    load_manpower(manpvec);
    ui->setupUi(this);

    set_emp_list();

    // Set max values for spin boxes
    ui->spinBox_empDaysMin->setRange(0,5);
    ui->spinBox_empDaysMax->setRange(0,5);
    ui->spinBox_empHoursMin->setRange(0,60);
    ui->spinBox_empHoursMax->setRange(0,60);

    // Makes the availability table evenly spaced horizontally and vertically
    ui->tableWidget_avail->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget_avail->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // Schedule table setup
    ui->tableWidget_schedule->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget_schedule->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // Lets us easily make changes to availabilty table
    for(size_t d = 0; d < 7; d++){
        for(size_t s = 1; s < 5; s++){
            QTableWidgetItem* pCell = new QTableWidgetItem;
            ui->tableWidget_avail->setItem(s, d, pCell);
        }
    }

    // Lets us easily make changes to schedule table
    ui->tableWidget_schedule->setRowCount(empvec.size()+1);
    for(size_t d = 0; d < 8; d++){
        for(size_t e =1; e < empvec.size()+1; e++){
            QTableWidgetItem* pCell = new QTableWidgetItem;
            ui->tableWidget_schedule->setItem(e, d, pCell);
        }
    }

    // Should be done on startup, and whenever any changes are made to employees
    schedule.setup(empvec, manpvec);

    sched_table_update(0, empvec.size());
}

autoschedservice::~autoschedservice()
{
    delete ui;
}

void autoschedservice::set_emp_list(){
    for(size_t i = 0; i < empvec.size(); i++){
        ui->listWidget_emps->addItem(QString::fromStdString(empvec.at(i).get_name()));
    }
}
void autoschedservice::sched_table_update(int start, int end){
    for(int i = start; i < end; i++){
        ui->tableWidget_schedule->item(i+1, 0)->setText(QString::fromStdString(empvec.at(i).get_name()));
    }
}
void autoschedservice::sched_table_add(){
    int row_idx = empvec.size();
    ui->tableWidget_schedule->insertRow(empvec.size());
    for(size_t i = 0; i < 8; i++){
        QTableWidgetItem* pCell = new QTableWidgetItem;
        ui->tableWidget_schedule->setItem(row_idx, i, pCell);
    }
    sched_table_update(row_idx-1, row_idx);
}
void autoschedservice::sched_table_rm(int row){
    ui->tableWidget_schedule->removeRow(row);
}

void autoschedservice::on_listWidget_emps_itemSelectionChanged()
{
    QListWidgetItem* itm = ui->listWidget_emps->currentItem();

    // Set ID val
    int index = ui->listWidget_emps->row(itm);
    ui->lbl_empIdVal->setText(QString::number(empvec.at(index).get_id()));

    // Set name
    ui->lineEdit_empName->setText(QString::fromStdString(empvec.at(index).get_name()));

    // Set role
    if(empvec.at(index).get_role() == "Sales"){
        ui->comboBox_empRole->setCurrentIndex(0);
    } else if(empvec.at(index).get_role() == "Tech") {
        ui->comboBox_empRole->setCurrentIndex(1);
    } else {
        ui->comboBox_empRole->setCurrentIndex(2);
    }

    // Set closer check
    ui->chkBox_empCloser->setChecked(empvec.at(index).is_closer());

    // Set priority value
    ui->spinBox_empPriority->setValue(empvec.at(index).get_priority());

    // Set spinbox values for
    ui->spinBox_empDaysMin->setValue(empvec.at(index).get_days_min());
    ui->spinBox_empDaysMax->setValue(empvec.at(index).get_days_max());
    ui->spinBox_empHoursMin->setValue(empvec.at(index).get_hours_min());
    ui->spinBox_empHoursMax->setValue(empvec.at(index).get_hours_max());

    for(size_t d = 0; d < 7; d++){
        for(size_t s = 0; s < empvec.at(index).get_avail(d).size(); s++){
            float temp_num = empvec.at(index).get_avail(d).at(s);
            QString text;
            if(temp_num != -1){
                text = QString::fromStdString(float_to_time(temp_num));
            } else {
                text = "OFF";
            }
            ui->tableWidget_avail->item(s+1, d)->setText(text);
        }
    }
}

void autoschedservice::on_btn_empUpdate_clicked()
{
    if(empvec.size() > 0){

        QListWidgetItem* current_item = ui->listWidget_emps->currentItem();
        int index = ui->lbl_empIdVal->text().toInt();

        // Update name
        std::string new_name = ui->lineEdit_empName->text().toStdString();
        if(new_name != empvec.at(index).get_name()){
            current_item->setText(QString::fromStdString(new_name));
            empvec.at(index).set_name(new_name);
        }

        // Update role
        std::string new_role = ui->comboBox_empRole->currentText().toStdString();
        empvec.at(index).set_role(new_role);

        // Update closer
        bool new_closer = ui->chkBox_empCloser->isChecked();
        empvec.at(index).set_closer(new_closer);

        // Update priority
        unsigned int new_pri = ui->spinBox_empPriority->value();
        empvec.at(index).set_priority(new_pri);

        // Update days/hours
        int new_days_min = ui->spinBox_empDaysMin->value();
        int new_days_max = ui->spinBox_empDaysMax->value();
        int new_hours_min = ui->spinBox_empHoursMin->value();
        int new_hours_max = ui->spinBox_empHoursMax->value();
        empvec.at(index).set_days_min(new_days_min);
        empvec.at(index).set_days_max(new_days_max);
        empvec.at(index).set_hours_min(new_hours_min);
        empvec.at(index).set_hours_max(new_hours_max);

        // Update availability
        for(size_t d = 0; d < 7; d++){
            for(size_t s = 0; s < empvec.at(index).get_avail(d).size(); s++){
                std::string temp_val = ui->tableWidget_avail->item(s+1, d)->text().toStdString();
                empvec.at(index).set_avail(d, s, time_to_float(temp_val));
            }
        }
        // Clear the schedule object
        clear_sched_table_contents();
        // Update the schedule table
        sched_table_update(index, index+1);
    }
}

void autoschedservice::on_btn_empAdd_clicked()
{
    empvec.push_back(Employee(empvec.size(), "New Employee", "None", false, 0,0,0,0, 0));

    for(int d = 0; d < 7; d++){
        std::vector<float> temp;
        for(int s = 0; s < manpvec.at(0).get_num_shifts(d)*2; s++){
            temp.push_back(-1);
        }
        empvec.at(empvec.size()-1).set_avail(d, temp);
    }

    ui->listWidget_emps->addItem(QString::fromStdString(empvec.at(empvec.size()-1).get_name()));
    sched_table_add();

    // Clear the schedule object
    clear_sched_table_contents();
}

void autoschedservice::on_btn_empDupe_clicked()
{
    // If prevents total anarchy
    if(empvec.size() > 0){

        // Get index of selected employee
        int index = ui->lbl_empIdVal->text().toInt();
        // Create temp instance using copy constructor
        Employee temp = empvec.at(index);
        // Set temps id
        temp.set_id(empvec.size());
        temp.set_name(empvec.at(index).get_name() + " (copy)");
        // Poosh it
        empvec.push_back(temp);
        // Update ui list
        ui->listWidget_emps->addItem(QString::fromStdString(empvec.at(empvec.size()-1).get_name()));
        // Add to the schedule table
        sched_table_add();
        // Clear the schedule object
        clear_sched_table_contents();
    }
}

void autoschedservice::on_btn_empRm_clicked()
{
    // Prevents total chaos
    if(empvec.size() > 0){

        // Get index of selected employee
        int index = ui->lbl_empIdVal->text().toInt();

        ui->listWidget_emps->clear();

        // Erase the selected employee
        empvec.erase(empvec.begin()+index);

        // Reset all the ids for employees after the one removed
        if((unsigned long long)index < empvec.size()){
            for(size_t i = index; i < empvec.size(); i++){
                empvec.at(i).set_id(i);
            }
        }
        // Then reset the employee list widget and the schedule table
        set_emp_list();
        sched_table_rm(index+1);

        // After removing item, set the item directly above to be selected.
        // This prevents !CHAOS!
        int new_idx = std::min(index, (int)empvec.size()-1);
        ui->listWidget_emps->setCurrentRow(new_idx);

        // Clear the schedule object
        clear_sched_table_contents();
    }
}

void autoschedservice::on_btn_empMoveUp_clicked()
{
    int index = ui->lbl_empIdVal->text().toInt();
    if(index > 0){
        std::cout << "\nMOVE UP" << std::endl;
        empvec.at(index).set_id(index-1);
        empvec.at(index-1).set_id(index);

        std::swap(empvec.at(index), empvec.at(index-1));

        ui->listWidget_emps->item(index-1)->setText(QString::fromStdString(empvec.at(index-1).get_name()));
        ui->listWidget_emps->item(index)->setText(QString::fromStdString(empvec.at(index).get_name()));

        sched_table_update( (index-1), (index-1)+2 );

        // Keeps the moved employee selected
        ui->listWidget_emps->setCurrentRow(index-1);

        // Update the schedule object
        schedule.swap_empw(index, index-1);
        update_sched_table_contents();
    }
}

void autoschedservice::on_btn_empMoveDown_clicked()
{
    int index = ui->lbl_empIdVal->text().toInt();
    if(index < (int)empvec.size()-1){
        std::cout << "\nMOVE DN" << std::endl;
        empvec.at(index).set_id(index+1);
        empvec.at(index+1).set_id(index);

        std::swap(empvec.at(index), empvec.at(index+1));

        ui->listWidget_emps->item(index+1)->setText(QString::fromStdString(empvec.at(index+1).get_name()));
        ui->listWidget_emps->item(index)->setText(QString::fromStdString(empvec.at(index).get_name()));

        sched_table_update( (index), (index)+2 );

        // Keeps the moved employee selected
        ui->listWidget_emps->setCurrentRow(index+1);

        // Update the schedule object
        schedule.swap_empw(index, index+1);
        update_sched_table_contents();
    }
}

void autoschedservice::update_sched_table_contents(){
    for(size_t d = 0; d < 7; d++){
        for(size_t e = 0; e < schedule.get_empwvec_size(); e++){
            ui->tableWidget_schedule->item(e+1, d+1)->setText(QString::fromStdString(schedule.get_emp_shift(e, d)));
        }
    }
}
void autoschedservice::clear_sched_table_contents(){
    for(size_t d = 0; d < 7; d++){
        for(size_t e = 0; e < (size_t)ui->tableWidget_schedule->rowCount()-1; e++){
            ui->tableWidget_schedule->item(e+1, d+1)->setText(QString::fromStdString(""));
        }
    }
    schedule.clear();
    schedule.setup(empvec, manpvec);
}
void autoschedservice::on_btn_schedCreate_clicked()
{
    if(schedule.get_empwvec_size() == 0){
        schedule.setup(empvec, manpvec);
    }
    schedule.set_closers();
    schedule.create(manpvec);

    update_sched_table_contents();
}

void autoschedservice::on_btn_schedClear_clicked()
{
    clear_sched_table_contents();
}

void autoschedservice::on_tableWidget_schedule_itemSelectionChanged()
{
    // First clear the combobox
    ui->comboBox_schedAssign->clear();
    // Check to make sure there is a schedule that exists
    if(schedule.get_empwvec_size() > 0){
        int col = ui->tableWidget_schedule->currentColumn();
        int row = ui->tableWidget_schedule->currentRow();
        // Make sure a valid cell is being selected
        if(col > 0 && row > 0){
            ui->comboBox_schedAssign->addItem("Select Shift...");
            // Add the employees shifts to the combo box
            for(size_t s = 0; s < schedule.get_employee(row-1)->get_avail(col-1).size(); s+=2){
                float start_f = schedule.get_employee(row-1)->get_avail(col-1).at(s);
                if(start_f == -1){
                    ui->comboBox_schedAssign->addItem("N/A");
                    continue;
                }
                float end_f = schedule.get_employee(row-1)->get_avail(col-1).at(s + 1);

                std::string start_s = float_to_time(start_f);
                std::string end_s = float_to_time(end_f);

                ui->comboBox_schedAssign->addItem(QString::fromStdString(start_s + "-" + end_s));
            }
            ui->comboBox_schedAssign->addItem("OFF");
        }
    }
}

void autoschedservice::on_btn_schedAssign_clicked()
{
    int shift = ui->comboBox_schedAssign->currentIndex() - 1;

    int row = ui->tableWidget_schedule->currentRow();
    int col = ui->tableWidget_schedule->currentColumn();

    if(shift >= 0){
        std::string shift_str = ui->comboBox_schedAssign->currentText().toStdString();
        if(shift_str != "N/A"){
            schedule.set_emp(row-1, col-1, shift, shift_str);
            update_sched_table_contents();
        }
    }
}
