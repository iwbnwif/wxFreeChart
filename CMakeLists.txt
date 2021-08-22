# Author: YWiyogo
# CMake build for wxFreeChart
#-------------------------------------
# How to build and run the piechartapp:
# 1. Goto wxCharts repo directory
# 2. mkdir cmakebuild && cd cmakebuild
# 3. cmake ..
# 4. make demo
#-------------------------------------

cmake_minimum_required(VERSION 3.11.3)

set(CMAKE_CXX_STANDARD 17)

project(wxFreeCharts)

# Install the wxwidgets library first in your system
# For Fedora30+: sudo dnf install wxGTK3-devel
# For Ubuntu18+: sudo apt install libwxbase3.1-dev libwxgtk3.1-dev
find_package(wxWidgets REQUIRED COMPONENTS core base aui adv)
include(${wxWidgets_USE_FILE})

# include the header directories
include_directories(./include/wx ./include/wx/**)

# Check for wxOVERRIDE macro which is newly defined in the version 3.1
if(COMMAND wxOVERRIDE)
    message(DEBUG "wxOVERRIDE macro exists")
else()
    add_definitions(-DwxOVERRIDE=override) 
endif()

# Extract the common parts in a (internal) static library
file(GLOB LIBRARY_SRCS src/*.cpp src/**/*.cpp src/**/**/*.cpp)
add_library(wxFreeCharts STATIC ${LIBRARY_SRCS})
target_include_directories(wxFreeCharts PUBLIC include )

# Add `samples` targets that enables building the sample programs
# Not built by default. Run `make demo` to build the demo application
# demo
file(GLOB SAMPLE_SRCS sample/*.cpp)
add_executable(demo EXCLUDE_FROM_ALL ${SAMPLE_SRCS})
target_link_libraries(demo wxFreeCharts ${wxWidgets_LIBRARIES})
