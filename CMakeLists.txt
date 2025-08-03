cmake_minimum_required(VERSION 3.29)
project(Readify)

set(CMAKE_CXX_STANDARD 14)
find_package(Threads REQUIRED)
add_subdirectory(include/internal)

add_executable(Readify
    main.cpp
        library.h
        library.cpp)
target_link_libraries(Readify csv)