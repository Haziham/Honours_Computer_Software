set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_CURRENT_SOURCE_DIR}/forms)

qt_add_executable(Dragon
    forms/mainwindow.ui
    src/mainwindow.cpp
    src/main.cpp
    src/jointcontrolwidget.h
    src/jointcontrolwidget.cpp 
    forms/jointcontrolwidget.ui
    resources/resources.qrc
)

target_link_libraries(Dragon PRIVATE Qt6::Widgets)


set_target_properties(Dragon PROPERTIES
    WIN32_EXECUTABLE ON
)
