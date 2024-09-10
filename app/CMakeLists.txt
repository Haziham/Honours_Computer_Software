
set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_CURRENT_SOURCE_DIR}/forms)

qt_add_executable(Dragon
    forms/mainwindow.ui
    forms/jointcontrolwidget.ui
    forms/jointlistitem.ui
    forms/spinslider.ui
    forms/legcontrolwidget.ui
    src/mainwindow.cpp
    src/main.cpp
    src/can.cpp
    src/JointsList.cpp
    widgets/jointlistitem.cpp
    resources/resources.qrc
    devices/joint.cpp   
    devices/leg.cpp
    devices/QJoint.cpp
    devices/QLeg.cpp
    devices/hexapod.cpp
    devices/QHexapod.cpp
    widgets/qspinboxtimed.cpp
    widgets/qcomboboxtimed.cpp
    widgets/jointlistwidget.cpp
    widgets/legcontrolwidget.cpp 
    widgets/spinslider.cpp 
    widgets/controlwidget.cpp
    widgets/jointcontrolwidget.cpp 
    widgets/legpushbutton.cpp

)

set_target_properties(Dragon PROPERTIES
                      RUNTIME_OUTPUT_DIRECTORY_RELEASE ~/bin/ 
)
find_package(Qt5 COMPONENTS Core REQUIRED)
target_link_libraries(Dragon PRIVATE Qt6::Widgets)

target_include_directories(Dragon PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/devices
    ${CMAKE_CURRENT_SOURCE_DIR}/widgets
)

set_target_properties(Dragon PROPERTIES
    WIN32_EXECUTABLE ON
)
