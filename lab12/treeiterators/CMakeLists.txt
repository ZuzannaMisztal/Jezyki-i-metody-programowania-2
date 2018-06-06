
project(treeiterators)

set(HEDEAR_FILES TreeIterators.h PreOrderTreeIterators.h PostOrderTreeIterators.h ../tree/Tree.h)
set(SOURCE_FILES TreeIterators.cpp PreOrderTreeIterators.cpp PostOrderTreeIterators.cpp ../tree/Tree.cpp)

add_library(libtreeiterators STATIC ${SOURCE_FILES})
target_include_directories(libtreeiterators PUBLIC .)

add_executable(treeiterators ${SOURCE_FILES} main.cpp)

target_link_libraries(treeiterators libtreeiterators)