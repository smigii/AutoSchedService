QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

RC_ICONS = icons/icon.ico

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
INCLUDEPATH += include/nlohmann_json/

SOURCES += \
    main.cpp \
    autoschedservice.cpp \
    src/public/time_conv.cpp \
    src/classes/Employee.cpp \
    src/classes/EmpWrapper.cpp \
    src/classes/Schedule.cpp \
    src/classes/Manpower.cpp

HEADERS += \
    autoschedservice.h \
    src/public/helpers.hpp \
    src/public/time_conv.hpp \
    src/public/load_json.hpp \
    src/public/scheduler.hpp \
    src/classes/Employee.hpp \
    src/classes/EmpWrapper.hpp \
    src/classes/Schedule.hpp \
    src/classes/Manpower.hpp

FORMS += \
    autoschedservice.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
