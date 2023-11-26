cmake_minimum_required(VERSION 3.16)
project(Dragon VERSION 1.0.0 LANGUAGES CXX)
include(FetchContent)

FetchContent_Declare(
    libusb
    GIT_REPOSITORY https://github.com/libusb/libusb-cmake.git
    GIT_TAG         "main"
    SOURCE_DIR      "${CMAKE_CURRENT_SOURCE_DIR}/libusb/"
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_PREFIX_PATH "C:/Qt/6.5.3/mingw_64/lib/cmake")

find_package(Qt6 REQUIRED COMPONENTS Widgets)
qt_standard_project_setup()


FetchContent_Populate(libusb)

add_subdirectory(app)
add_subdirectory(libusb)
target_link_libraries(Dragon PRIVATE usb-1.0)
add_subdirectory(devices)
target_link_libraries(Dragon PRIVATE devices)
