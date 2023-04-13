FILE(GLOB TEST_FILES **/*test.cpp)

add_executable(bencppTest ${TEST_FILES})

target_link_libraries(bencppTest GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(bencppTest)
