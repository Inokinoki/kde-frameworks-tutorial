add_executable(knotifications_helloworld simple_notification.cpp)

find_package(Qt5 COMPONENTS Core Widgets REQUIRED)
find_package(KF5Notifications)

target_link_libraries(knotifications_helloworld Qt5::Core KF5::Notifications)
