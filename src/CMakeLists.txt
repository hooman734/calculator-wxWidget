cmake_minimum_required(VERSION 3.7)
project(wx)

set(CMAKE_CXX_STANDARD 17)

set(wxWidgets_ROOT_DIR </usr/bin>)
set(wxWidgets_CONFIGURATION mswu)
find_package(wxWidgets COMPONENTS core base REQUIRED)
include(${wxWidgets_USE_FILE})

set(SOURCE_FILES MainFrame.h MainFrame.cc App.cc App.h MathParser.cpp MathParser.h)
add_executable(FirstC ${SOURCE_FILES})

target_link_libraries(FirstC ${wxWidgets_LIBRARIES})