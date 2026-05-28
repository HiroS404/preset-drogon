cmake_minimum_required(VERSION 3.10)
project(preset_api)

set(CMAKE_CXX_STANDARD 17)

find_package(Drogon CONFIG REQUIRED)

file(GLOB CONTROLLER controllers/*.cc)

add_executable(my_api main.cc ${CONTROLLER})

target_link_libraries(my_api PRIVATE Drogon::Drogon)