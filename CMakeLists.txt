cmake_minimum_required(VERSION 3.16)

project(assignment8_4__1_QC LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(assignment8_4__1_QC main.cpp
    all_classes.h)

include(GNUInstallDirs)
install(TARGETS assignment8_4__1_QC
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
