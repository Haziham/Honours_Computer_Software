qt_add_executable(Dragon
    src/mainwindow.ui
    src/mainwindow.cpp
    src/main.cpp
    src/jointcontrolwidget.h
    src/jointcontrolwidget.cpp 
    src/jointcontrolwidget.ui
)

target_link_libraries(Dragon PRIVATE Qt6::Widgets)

set_target_properties(Dragon PROPERTIES
    WIN32_EXECUTABLE ON
)
