################## HELLO WORLD ##################

# Project configuration
cmake_minimum_required(VERSION 3.0.0)
set(CMAKE_TOOLCHAIN_FILE "../../Managers/vcpkg/scripts/buildsystems/vcpkg.cmake")
project(AATMS
    VERSION 1.1.0
    DESCRIPTION "Advanced Automated Teller Machine System"
    HOMEPAGE_URL "https://github.com/Jed556/AATMS"
    LANGUAGES CXX
)

# Testing
include(CTest)
enable_testing()

# Setup directories
set(FOLDER_NAME ${PROJECT_NAME}-${PROJECT_VERSION}-win64)
set(CMAKE_SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${FOLDER_NAME}/bin)


################## INCLUDE AND LINK ##################

# Set executable output directory
set(MAIN_CPP ${CMAKE_SOURCE_DIR}/main.cpp)
file(GLOB_RECURSE SOURCE CONFIGURE_DEPENDS "src/*.h" "src/*.cpp")
list(REMOVE_ITEM SOURCE ${REMOVE_CMAKE})
add_executable(${PROJECT_NAME} ${SOURCE})

# Link libraries
find_package(unofficial-sqlite3 CONFIG REQUIRED)
find_package(SDL2 CONFIG REQUIRED)
find_package(SDL2_image CONFIG REQUIRED)
find_package(SDL2_ttf CONFIG REQUIRED)
find_package(sdl2-gfx CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME}
    PRIVATE
    unofficial::sqlite3::sqlite3
    # $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
    $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
    $<IF:$<TARGET_EXISTS:SDL2_image::SDL2_image>,SDL2_image::SDL2_image,SDL2_image::SDL2_image-static>
    $<IF:$<TARGET_EXISTS:SDL2_ttf::SDL2_ttf>,SDL2_ttf::SDL2_ttf,SDL2_ttf::SDL2_ttf-static>
    SDL2::SDL2_gfx
)

# Copy resources to build directory  during the process
add_custom_target(copy_files ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/res ${CMAKE_BINARY_DIR}/${FOLDER_NAME}/res
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/database ${CMAKE_BINARY_DIR}/${FOLDER_NAME}/database
    COMMENT "Copying files during build"
)

# Add the custom target as a dependency of the main target
add_dependencies(${PROJECT_NAME} copy_files)

# Set the language for the target
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)


################## PACKAGE ##################

# Setup package
set(CPACK_GENERATOR "ZIP")
set(CPACK_PACKAGE_FILE_NAME "${PROJECT_NAME}-${PROJECT_VERSION}-win64")
set(CPACK_INCLUDE_TOPLEVEL_DIRECTORY OFF)
set(CPACK_PACKAGE_DIRECTORY ${CMAKE_BINARY_DIR}/package)
include(CPack)

# Package resources and libraries
install(DIRECTORY ${CMAKE_SOURCE_DIR}/database/ DESTINATION ${FOLDER_NAME}/database )
install(DIRECTORY ${CMAKE_SOURCE_DIR}/res/ DESTINATION ${FOLDER_NAME}/res )
install(TARGETS ${PROJECT_NAME} DESTINATION ${FOLDER_NAME}/bin)
install(FILES
    $<TARGET_FILE:unofficial::sqlite3::sqlite3> 
    $<TARGET_FILE:SDL2::SDL2>
    $<TARGET_FILE:SDL2_ttf::SDL2_ttf>
    $<TARGET_FILE:SDL2_image::SDL2_image>
    DESTINATION ${FOLDER_NAME}/bin
)


################## CUSTOM TARGETS ##################

# Custom target for auto packing and running
add_custom_target(PackU
    COMMAND echo "Building the project"
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target package
)