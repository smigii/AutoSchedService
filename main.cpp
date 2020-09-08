#include "autoschedservice.h"

//#include <iostream>
//#include <iomanip>
//#include <string>
//#include <vector>

//#include <nlohmann/json.hpp>

//#include "src/classes/Employee.hpp"
//#include "src/classes/Manpower.hpp"
//#include "src/classes/EmpWrapper.hpp"
//#include "src/classes/Schedule.hpp"

//#include "src/public/load_json.hpp"
//#include "src/public/helpers.hpp"
//#include "src/public/scheduler.hpp"

//using json = nlohmann::json;

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    autoschedservice w;
    w.show();
    return a.exec();
}
