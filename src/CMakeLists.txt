cmake_minimum_required(VERSION 3.14)
project(tcp_hash_server)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Boost REQUIRED COMPONENTS system)
find_package(OpenSSL REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})
include_directories(${OPENSSL_INCLUDE_DIR})

add_executable(tcp_hash_server
    tcp_hash_server.cpp
    server.cpp
    hasher.cpp
    session.cpp
)

target_link_libraries(tcp_hash_server
    ${Boost_LIBRARIES}
    OpenSSL::SSL
    OpenSSL::Crypto
    pthread
)

enable_testing()
add_subdirectory(test)