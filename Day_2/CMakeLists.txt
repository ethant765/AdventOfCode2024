cmake_minimum_required(VERSION 3.10)

#name and version project
project(day_two VERSION 1.0)

# set c++ version
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# set bin directory for build executable output
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

# add all source files
file(GLOB_RECURSE SOURCE_FILES
    "src/*.cc"
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

# include header files
target_include_directories(${PROJECT_NAME} PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# add resource files
file(GLOB RESOURCE_FILES
    "src/resources/*"
)
set(RESOURCE_DESTINATION_DIR "$<TARGET_FILE_DIR:${PROJECT_NAME}>")

foreach(RESOURCE ${RESOURCE_FILES})
    get_filename_component(FILENAME ${RESOURCE} NAME)

    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        "${RESOURCE}"
        "${RESOURCE_DESTINATION_DIR}/${FILENAME}"
        COMMENT "Copying resource file: ${FILENAME}"
    )
endforeach()