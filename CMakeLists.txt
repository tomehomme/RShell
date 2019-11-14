CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
ADD_SUBDIRECTORY(googletest)
SET(CMAKE_CXX_STANDARD 11)
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)  
set(Boost_USE_STATIC_RUNTIME OFF)
find_package( Boost REQUIRED COMPONENTS program_options regex )
include_directories( ${Boost_INCLUDE_DIRS} )
 
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    add_executable(rshell  ./src/rshell.cpp)
    ADD_EXECUTABLE(test
    ./unit_tests/unit_test.cpp)
    target_link_libraries(rshell  ${Boost_LIBRARIES})
    target_link_libraries(test  ${Boost_LIBRARIES})
endif()
 
 
 
 
TARGET_LINK_LIBRARIES(test gtest)
TARGET_COMPILE_DEFINITIONS(test PRIVATE gtest_disable_pthreads=ON)
target_link_libraries( rshell ${Boost_PROGRAM_OPTIONS_LIBRARY} ${Boost_REGEX_LIBRARY} )