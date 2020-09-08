#include "autoschedservice.h"
#include "ui_autoschedservice.h"

#include <nlohmann/json.hpp>
using json = nlohmann::json;

#include "src/classes/Employee.hpp"
#include "src/classes/Manpower.hpp"
#include "src/classes/EmpWrapper.hpp"
#include "src/classes/Schedule.hpp"

#include "src/public/load_json.hpp"
#include "src/public/helpers.hpp"
#include "src/public/scheduler.hpp"

// Create the employee master vector and fill it with employee data
// from employees.json
std::vector<Employee> empvec;

// Create the manpower master vector and fill it with manpower data
// from manpower.json
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

    // Lets us easily make changes to availabilty table
    for(size_t d = 0; d < 7; d++){
        for(size_t s = 1; s < 5; s++){
            QTableWidgetItem* pCell = new QTableWidgetItem;
            ui->tableWidget_avail->setItem(s, d, pCell);
        }
    }
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

    // Update days/hours
    int new_days_min = ui->spinBox_empDaysMin->value();
    int new_days_max = ui->spinBox_empDaysMax->value();
    int new_hours_min = ui->spinBox_empHoursMin->value();
    int new_hours_max = ui->spinBox_empHoursMax->value();
    empvec.at(index).set_days_min(new_days_min);
    empvec.at(index).set_days_max(new_days_max);
    empvec.at(index).set_hours_min(new_hours_min);
    empvec.at(index).set_hours_max(new_hours_max);

}

void autoschedservice::on_btn_empAdd_clicked()
{
    empvec.push_back(Employee(empvec.size(), "New Employee", "None", false, 0,0,0,0));
    ui->listWidget_emps->addItem(QString::fromStdString(empvec.at(empvec.size()-1).get_name()));
}

void autoschedservice::on_btn_empDupe_clicked()
{
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
}
