FILE(GLOB TEST_FILES **/*.test.cpp *.test.cpp utils.cpp)

add_executable(bencppTest ${TEST_FILES})

target_link_libraries(bencppTest GTest::gtest_main bencpp)
target_include_directories(bencppTest PUBLIC "${CMAKE_SOURCE_DIR}/src")

include(GoogleTest)
gtest_discover_tests(bencppTest)
