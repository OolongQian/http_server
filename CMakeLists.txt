cmake_minimum_required(VERSION 3.10)
project(httpServer)

set(CMAKE_CXX_STANDARD 11)

# find BOOST
find_package(Boost COMPONENTS system thread filesystem REQUIRED)
#find_package(OpenSSL COMPONENTS crypto ssl REQUIRED)
#add_definitions(-D BOOST_NETWORK_ENABLE_HTTPS)
#include_directories(${OPENSSL_INCLUDE_DIR})
# find OPENSSL
#if(APPLE)
#    set(OPENSSL_ROOT_DIR "/usr/local/opt/openssl")
#endif()
#find_package(OpenSSL)

#target_compile_options(httpServer PRIVATE -fexceptions)

#add_compile_options(-I ~/usr/local/ssl/include)
#add_compile_options(-L ~/usr/local/ssl/lib)
#add_compile_options(-lboost_system)
#add_compile_options(-lssl)
#add_compile_options(-lcrypto)
#add_compile_options(-ldl)
#add_compile_options(-lpthread)

# add EXECUTABLE
add_executable(httpServer main.cpp server_http.hpp utility.hpp status_code.hpp client_http.hpp)

# link LIBRARIES
#if(OPENSSL_FOUND)
#    target_compile_definitions(httpServer INTERFACE HAVE_OPENSSL)
#    target_link_libraries(httpServer INTERFACE ${Boost_LIBRARIES} ${OPENSSL_LIBRARIES})
#    target_include_directories(httpServer INTERFACE ${OPENSSL_INCLUDE_DIR})
#else()
#${OpenSSL_LIBRARIES}
target_link_libraries(httpServer ${Boost_LIBRARIES})
#endif()