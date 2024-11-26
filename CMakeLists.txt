cmake_minimum_required(VERSION 3.16)

project(appgeolocator VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.4 REQUIRED COMPONENTS Quick Sql Location Test)
qt_standard_project_setup()

add_subdirectory(3rdparty/googletest)
enable_testing()

add_subdirectory(src)
add_subdirectory(tests)


# include(GNUInstallDirs)
# install(TARGETS appgeolocator
#     BUNDLE DESTINATION .
#     LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
#     RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
# )
