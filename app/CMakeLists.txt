qt_add_executable(Dragon
    src/mainwindow.ui
    src/mainwindow.cpp
    src/main.cpp
)

target_link_libraries(Dragon PRIVATE Qt6::Widgets)

set_target_properties(Dragon PROPERTIES
    WIN32_EXECUTABLE ON
)