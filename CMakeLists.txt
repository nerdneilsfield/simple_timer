cmake_minimum_required(VERSION 3.10)

# Not ideal to use this global variable, but necessary to make sure
# that tooling and projects use the same version
set(CMAKE_CXX_STANDARD 17)

# strongly encouraged to enable this globally to avoid conflicts between
# -Wpedantic being enabled and -std=c++20 and -std=gnu++20 for example
# when compiling with PCH enabled
set(CMAKE_CXX_EXTENSIONS OFF)


# Note: by default ENABLE_DEVELOPER_MODE is True
# This means that all analysis (sanitizers, static analysis)
# is enabled and all warnings are treated as errors
# if you want to switch this behavior, change TRUE to FALSE
set(ENABLE_DEVELOPER_MODE TRUE CACHE BOOL "Enable 'developer mode'")

# Change this to false if you want to disable warnings_as_errors in developer mode
set(OPT_WARNINGS_AS_ERRORS_DEVELOPER_DEFAULT TRUE)

set(BUILD_EXAMPLE TRUE)
set(BUILD_TEST OFF)

project(
        SimpleTimer
        VERSION 0.0.1
        DESCRIPTION "A very simple c++ timer"
        HOMEPAGE_URL "https://github.com/nerdneilsfield/simple_timer"
        LANGUAGES CXX
      )

add_library(SimpleTimer INTERFACE)
target_include_directories(SimpleTimer INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
add_library(SimpleTimer::SimpleTimer ALIAS SimpleTimer)

if(BUILD_EXAMPLE)
add_executable(simple_timer_example example/basic_example.cpp)
target_link_libraries(simple_timer_example PRIVATE SimpleTimer::SimpleTimer)
endif()