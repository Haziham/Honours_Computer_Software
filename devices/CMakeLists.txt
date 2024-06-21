add_library(devices
    src/joint.cpp
)

target_link_libraries(devices PRIVATE Qt6::Core)
target_include_directories(devices PUBLIC src)
