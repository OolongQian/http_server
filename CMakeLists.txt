cmake_minimum_required(VERSION 3.10)
project(httpServer)

set(CMAKE_CXX_STANDARD 17)

# find BOOST
find_package(Boost COMPONENTS system thread filesystem REQUIRED)
link_libraries(/usr/local/openssl/lib)

# test where is the project source directory in clion cmake.
#message(STATUS "project binary directory: ${PROJECT_BINARY_DIR}")
#message(STATUS "project source directory: ${PROJECT_SOURCE_DIR}")

# compile static library... This is purely hpp file, which can't be compiled into static library.
# this is a pure header file lib.
# add EXECUTABLE

#add_executable(httpServer https_example.cpp server_http.hpp utility.hpp status_code.hpp client_http.hpp server_https.hpp client_https.hpp http_example.cpp)
add_executable(webServer https_example.cpp)
# link LIBRARIES
target_link_libraries(webServer ${Boost_LIBRARIES} pthread crypto ssl)
#endif()