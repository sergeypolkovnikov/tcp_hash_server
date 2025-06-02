find_package(GTest REQUIRED)

include_directories(${GTEST_INCLUDE_DIRS})
include_directories(..)

add_executable(hasher_tests test.cpp ../hasher.cpp)

target_link_libraries(hasher_tests
    ${GTEST_BOTH_LIBRARIES}
    pthread
    OpenSSL::SSL
    OpenSSL::Crypto
)

add_test(NAME HasherTests COMMAND hasher_tests)