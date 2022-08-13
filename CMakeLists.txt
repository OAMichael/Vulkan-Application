cmake_minimum_required(VERSION 3.10)

project(Space VERSION 1.0)
cmake_policy(SET CMP0076 NEW)

set(CMAKE_CXX_STANDARD 17)
set(SRC_DIR ./src)
set(COMPILE_OPT -std=c++17 -O2)
set(LINK_OPT -lglfw -lvulkan -ldl -lpthread -lX11 -lXxf86vm -lXrandr -lXi)

add_executable(MyApp.exe ${SRC_DIR}/main.cpp)

target_include_directories(MyApp.exe PUBLIC ${SRC_DIR})

add_library(App ${SRC_DIR}/App.cpp)
target_link_libraries(MyApp.exe PUBLIC App)

add_library(Camera ${SRC_DIR}/Camera.cpp)
target_link_libraries(MyApp.exe PUBLIC Camera)

add_library(Debug ${SRC_DIR}/Debug.cpp)
target_link_libraries(MyApp.exe PUBLIC Debug)

add_compile_options(MyApp.exe ${COMPILE_OPT})
target_link_libraries(MyApp.exe PUBLIC ${LINK_OPT})