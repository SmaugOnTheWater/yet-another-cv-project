find_package(GTest REQUIRED)

set(SOURCES main.cpp ClassifierTest.cpp)

add_executable(tests ${SOURCES})
target_include_directories(tests PRIVATE ${GTEST_INCLUDE_DIRS})
target_link_libraries(tests classifierlib ${GTEST_BOTH_LIBRARIES} pthread)