cmake_minimum_required(VERSION 3.16)
project(Dragon VERSION 1.0.0 LANGUAGES C CXX)
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

add_subdirectory(app)

# FetchContent_Populate(libusb)

# add_subdirectory(libusb)
# add_subdirectory(devices)
add_subdirectory(hlib/freckle)
add_subdirectory(hlib/usb2can)
add_subdirectory(hlib/canQueue)
add_subdirectory(hlib/inverseKinematics)
add_subdirectory(hlib/hexapodMaths)
add_subdirectory(libs/QVirtualPad/qvirtualpad)

target_link_libraries(usb2can PRIVATE canQueue)
# target_link_libraries(devices PRIVATE freckle)
target_link_libraries(Dragon PRIVATE freckle usb2can canQueue inverseKinematics hexapodMaths qvirtualpad)

# qt_add_resources(Dragon resources/resources.qrc)

