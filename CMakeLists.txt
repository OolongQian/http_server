cmake_minimum_required(VERSION 3.10)
project(httpServer)

set(CMAKE_CXX_STANDARD 11)

# find BOOST
find_package(Boost COMPONENTS system thread filesystem REQUIRED)
# find OPENSSL
if(APPLE)
    set(OPENSSL_ROOT_DIR "/usr/local/opt/openssl")
endif()
find_package(OpenSSL)

# add EXECUTABLE
add_executable(httpServer main.cpp server_http.hpp utility.hpp status_code.hpp client_http.hpp server_https.hpp)

# link LIBRARIES
if(OPENSSL_FOUND)
    target_compile_definitions(httpServer INTERFACE HAVE_OPENSSL)
    target_link_libraries(httpServer INTERFACE ${Boost_LIBRARIES} ${OPENSSL_LIBRARIES})
    target_include_directories(httpServer INTERFACE ${OPENSSL_INCLUDE_DIR})
else()
    target_link_libraries(httpServer ${Boost_LIBRARIES})
endif()