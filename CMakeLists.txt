cmake_minimum_required(VERSION 3.1)
project(LVGL9_EMU C)

set(CMAKE_C_STANDARD 11)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

# 设置终端是否可见
#if (WIN32)
#    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-subsystem,windows")
#endif()

# 0 添加宏定义
add_definitions(-DUSE_SDL)
add_definitions(-LV_LVGL_H_INCLUDE_SIMPLE)


# 推荐使用环境变量方式
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

# 1 添加头文件目录

include_directories(C:\\ProgramFiles\\msys64\\mingw64\\include)
include_directories(C:\\ProgramFiles\\msys64\\mingw64\\lib)

include_directories(src)
include_directories(inc)
#include_directories(src/porting)
include_directories(src/porting/sdl)
include_directories(components/lvgl)

# 2 链接其他包
add_subdirectory(components/lvgl)


# 3 添加源文件(递归包含)
FILE(GLOB_RECURSE src_source ./src/*.c )

# 5 编译可执行文件
add_executable(${PROJECT_NAME} ${src_source} main.c
)

# 6 链接库

target_link_libraries(${PROJECT_NAME} lvgl)
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})
