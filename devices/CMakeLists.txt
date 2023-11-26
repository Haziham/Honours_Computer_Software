add_library(devices
    src/rc_car.cpp
    src/rc_car.h
)

target_link_libraries(devices PRIVATE Qt6::Core)
target_include_directories(devices PUBLIC src)
