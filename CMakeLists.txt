#设置cmake的版本
cmake_minimum_required(VERSION 3.0)

#设置项目名称
project(MainProject)

#设置cmake的创建类型
set(CMAKE_SYSTEM_NAME Linux )  #系统名称

#根据BUILD传参，选择编译工具链
set(BUILD "x86" CACHE STRING "select build CPU type")
#判断外部是否用cmake .. -DBUILD=arm进行值传入
if(BUILD STREQUAL arm)
    set(CMAKE_BUILD_PROCESSOR arm) #编译生成的程序为arm平台的程序
    set(CMAKE_C_COMPILER /usr/bin/arm-linux-gnueabihf-gcc) #指定交叉编译工具链的路径
    message(this is arm platform)
else()
    message(this is x86 platform)
endif()

#set CMAKE_C_FLAGS
#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -o2 -Wall")
add_compile_options(-g -Wall)
set(CMAKE_BUILD_TYPE Debug)


#指定头文件路径
include_directories(Core/Inc/User Core/Inc/BSP Core/Inc/Peripheral Core/Inc/System)

#指定源文件的路径，并赋值给变量 VAR_SRC
aux_source_directory(Core/Src/BSP VAR_SRC1)
aux_source_directory(Core/Src/Peripheral VAR_SRC2)
aux_source_directory(Core/Src/System VAR_SRC3)
aux_source_directory(Core/Src/User VAR_SRC4)


#指定编译生成的二进制程序为main
add_executable(main ${VAR_SRC1} ${VAR_SRC2} ${VAR_SRC3} ${VAR_SRC4})

#指定编译生成的二进制程序保存到bin目录下
set(EXECUTABLE_OUTPUT_PATH ../bin)

#添加以下语句，以完成多线程编译
TARGET_LINK_LIBRARIES(main pthread)

