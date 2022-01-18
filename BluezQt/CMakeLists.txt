
add_executable(bluezqt-helloworld service_init.cpp)


find_package(Qt5 COMPONENTS Widgets DBus REQUIRED)
find_package(KF5BluezQt)

target_link_libraries(bluezqt-helloworld KF5::BluezQt Qt5::DBus)
