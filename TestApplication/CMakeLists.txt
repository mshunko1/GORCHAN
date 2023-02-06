cmake_minimum_required(VERSION 3.0.0)
project(TestApplication VERSION 0.1.0)

include(CTest)
enable_testing()

link_directories(${PROJECT_SOURCE_DIR}/../GORCHAN/build)


include_directories(${PROJECT_SOURCE_DIR}/../GORCHAN/ ${PROJECT_SOURCE_DIR}/../GORCHAN/build)

add_executable(TestApplication main.cpp)
 
TARGET_LINK_LIBRARIES(TestApplication GORCHAN)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
