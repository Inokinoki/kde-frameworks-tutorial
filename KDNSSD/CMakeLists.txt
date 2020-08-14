add_executable(kdnssd-discover-helloworld service_discover.cpp)
add_executable(kdnssd-publish-helloworld service_publish.cpp)

find_package(KF5DNSSD)

target_link_libraries(kdnssd-discover-helloworld KF5::DNSSD)
target_link_libraries(kdnssd-publish-helloworld KF5::DNSSD)
