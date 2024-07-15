set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_CURRENT_SOURCE_DIR}/forms)

qt_add_executable(Dragon
    forms/mainwindow.ui
    src/mainwindow.cpp
    src/main.cpp
    src/jointcontrolwidget.cpp 
    src/can.cpp
    forms/jointcontrolwidget.ui
    resources/resources.qrc
    devices/joint.cpp
)


target_link_libraries(Dragon PRIVATE Qt6::Widgets)

target_include_directories(Dragon PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/devices
)

set_target_properties(Dragon PROPERTIES
    WIN32_EXECUTABLE ON
)
