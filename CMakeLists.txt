PROJECT(test CXX) #项目名称


#Cmake最低版本要求
CMAKE_MINIMUM_REQUIRED(VERSION 2.6) 


#允许gdb调试
set(CMAKE_BUILD_TYPE "RELEASE")
set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb")
set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")


#添加C++11支持及其他选项
set(CMAKE_CXX_FLAGS "-std=c++0x ${CMAKE_CXX_FLAGS} -g -ftest-coverage -fprofile-arcs -Wno-deprecated")
#set(CMAKE_CXX_FLAGS "-std=c++0x ${CMAKE_CXX_FLAGS -g -ftest-coverage -fprofile-arcs"})


#添加子目录
#add_subdirectory(dict) 


#head file path，头文件目录
INCLUDE_DIRECTORIES(include)


#当前目录下所有源文件赋给DIR_SRCS
AUX_SOURCE_DIRECTORY(. DIR_SRCS)
#file(GLOB_RECURSE include_HEADES "./*.h")
#file(GLOB_RECURSE test_src "./*.[ch]pp")


## for lib   
#add_library(test_python SHARED ${include_HEADES}


#添加C++11编译选项,但是只有CMAKE 3.1支持
#target_compile_features(test PRIVATE cxx_range_for)


#添加链接库
#target_link_libraries(test xxx)


add_executable(test) 

