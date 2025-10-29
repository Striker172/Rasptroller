# CMake build script for Rasptroller project
# Usage: cmake -P build.cmake

message(STATUS "Starting build process...")

# Get the current script directory
get_filename_component(PROJECT_DIR ${CMAKE_CURRENT_LIST_DIR} ABSOLUTE)
set(BUILD_DIR "${PROJECT_DIR}/build")

message(STATUS "Project directory: ${PROJECT_DIR}")
message(STATUS "Build directory: ${BUILD_DIR}")

# Create build directory if it doesn't exist
if(NOT EXISTS ${BUILD_DIR})
    message(STATUS "Creating build directory...")
    file(MAKE_DIRECTORY ${BUILD_DIR})
endif()

# Configure the project
message(STATUS "Running CMake configuration...")
execute_process(
    COMMAND ${CMAKE_COMMAND} ..
    WORKING_DIRECTORY ${BUILD_DIR}
    RESULT_VARIABLE CONFIG_RESULT
)

if(NOT CONFIG_RESULT EQUAL 0)
    message(FATAL_ERROR "CMake configuration failed!")
endif()

message(STATUS "Configuration complete!")

# Build the project
message(STATUS "Building project...")
execute_process(
    COMMAND ${CMAKE_COMMAND} --build .
    WORKING_DIRECTORY ${BUILD_DIR}
    RESULT_VARIABLE BUILD_RESULT
)

if(NOT BUILD_RESULT EQUAL 0)
    message(FATAL_ERROR "Build failed!")
endif()

message(STATUS "Build process complete!")
