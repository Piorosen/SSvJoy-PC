cmake_minimum_required(VERSION 3.14.1)
SET(PROJECT_NAME SSvJoyPC)
SET(CMAKE_TOOLCHAIN_FILE C:/Users/DoD/Desktop/git/vcpkg/scripts/buildsystems/vcpkg.cmake)
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED       ON)
set(CMAKE_CXX_STANDARD_REQUIRED     ON)
# Serial Port Linrary
include_directories(${CMAKE_SOURCE_DIR}/3rdparty/serial/lib/)
include_directories(${CMAKE_SOURCE_DIR}/include)

find_package(Drogon CONFIG REQUIRED)
find_package(cxxopts CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)

add_executable(${PROJECT_NAME}
    main.cpp
)

add_library(seriallib STATIC 3rdparty/seriallib/lib/serialib.cpp)

# install target and libraries
set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR}/bin)

target_link_libraries(${PROJECT_NAME} PRIVATE 
        seriallib
        Drogon::Drogon
        spdlog::spdlog
        cxxopts::cxxopts
)
