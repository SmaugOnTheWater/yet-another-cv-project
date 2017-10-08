find_package(dlib REQUIRED)
find_package(OpenCV REQUIRED)
find_package(CGAL REQUIRED)
find_package(Boost COMPONENTS filesystem REQUIRED)

message("Boost ${Boost_LIBRARIES}")

set(SOURCE_FILES Classifier.cpp util.cpp)
add_library(classifierlib ${SOURCE_FILES})
target_include_directories(classifierlib PUBLIC ../../parser)
target_link_libraries(classifierlib ${dlib_LIBRARIES} ${OpenCV_LIBRARIES} ${CGAL_LIBRARY} ${Boost_LIBRARIES} csvparser)

add_executable(classifier main.cpp)
target_link_libraries(classifier classifierlib)
