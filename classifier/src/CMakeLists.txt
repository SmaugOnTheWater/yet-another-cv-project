find_package(dlib REQUIRED)
find_package(OpenCV REQUIRED)

set(SOURCE_FILES Classifier.cpp)
add_library(classifierlib ${SOURCE_FILES})
target_include_directories(classifierlib PUBLIC ../../parser)
target_link_libraries(classifierlib ${dlib_LIBRARIES} ${OpenCV_LIBRARIES} csvparser)

add_executable(classifier main.cpp)
target_link_libraries(classifier classifierlib)