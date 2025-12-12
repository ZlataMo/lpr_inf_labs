cmake_minimum_required(VERSION 3.10)
project(SFMLProject LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

if(SFML_FOUND)
    message(STATUS "SFML found: ${SFML_INCLUDE_DIR}")
endif()

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/fonts 
     DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

file(GLOB SOURCES "src/*.cpp")

add_executable(main ${SOURCES})

target_include_directories(main PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

target_link_libraries(main sfml-graphics sfml-window sfml-system)