add_executable(kjobwidgets_helloworld kjob_progress_helloworld.cpp)

find_package(Qt5 COMPONENTS Core Widgets REQUIRED)
find_package(KF5JobWidgets)
find_package(KF5CoreAddons)
find_package(KF5KIO)

target_link_libraries(kjobwidgets_helloworld Qt5::Core KF5::JobWidgets KF5::CoreAddons
    KF5::KIOCore KF5::KIOFileWidgets KF5::KIOWidgets KF5::KIONTLM)
