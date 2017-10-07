project(classifier)

add_subdirectory(src)
add_subdirectory(test)
add_test(NAME MyTest COMMAND Test)