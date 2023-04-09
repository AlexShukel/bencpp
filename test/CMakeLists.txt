FILE(GLOB TEST_FILES check_correctness/*test.cpp counters/*.test.cpp *.test.cpp)

add_executable(bencppTest ${TEST_FILES})

target_link_libraries(bencppTest GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(bencppTest)
