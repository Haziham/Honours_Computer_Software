
set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_CURRENT_SOURCE_DIR}/forms)

qt_add_executable(Dragon
    forms/mainwindow.ui
    forms/jointcontrolwidget.ui
    src/mainwindow.cpp
    src/main.cpp
    src/jointcontrolwidget.cpp 
    src/can.cpp
    resources/resources.qrc
    devices/joint.cpp 
    widgets/qspinboxtimed.cpp
)

set_target_properties(Dragon PROPERTIES
                      RUNTIME_OUTPUT_DIRECTORY_RELEASE ~/bin/ 
)

target_link_libraries(Dragon PRIVATE Qt6::Widgets)

target_include_directories(Dragon PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/devices
    ${CMAKE_CURRENT_SOURCE_DIR}/widgets
)

set_target_properties(Dragon PROPERTIES
    WIN32_EXECUTABLE ON
)
