cmake_minimum_required(VERSION 3.0.0)
project(AATMS VERSION 0.0.2)

include(CTest)
enable_testing()

# Set executable output directory
set(MAIN_CPP ${CMAKE_SOURCE_DIR}/src)
add_executable(${PROJECT_NAME} ${MAIN_CPP})

# Setup root directories
set(SDL2_ROOT_DIR ${CMAKE_SOURCE_DIR}/lib/SDL2/x86_64-w64-mingw32)
set(SDL2_IMAGE_ROOT_DIR ${CMAKE_SOURCE_DIR}/lib/SDL2_image/x86_64-w64-mingw32)
set(SDL2_TTF_ROOT_DIR ${CMAKE_SOURCE_DIR}/lib/SDL2_ttf/x86_64-w64-mingw32)
set(JSON_ROOT_DIR ${CMAKE_SOURCE_DIR}/lib/json-develop)
set(OPEN_SSL_ROOT_DIR ${CMAKE_SOURCE_DIR}/lib/openssl-1.1.1u)
set(AATMS_ROOT_DIR ${CMAKE_SOURCE_DIR})

# Setup include directories
include_directories(
    ${AATMS_ROOT_DIR}/include
    ${SDL2_ROOT_DIR}/include/SDL2
    ${SDL2_IMAGE_ROOT_DIR}/include/SDL2
    ${SDL2_TTF_ROOT_DIR}/include/SDL2
    # ${JSON_ROOT_DIR}/include
    # ${OPEN_SSL_ROOT_DIR}/include
)

if(WIN32)
    # Link against libraries
    target_link_libraries(${PROJECT_NAME} PRIVATE
        ${SDL2_ROOT_DIR}/lib/libSDL2.dll.a
        ${SDL2_IMAGE_ROOT_DIR}/lib/libSDL2_image.dll.a
        ${SDL2_TTF_ROOT_DIR}/lib/libSDL2_ttf.dll.a
    )

    target_sources(${PROJECT_NAME} PRIVATE ${MAIN_CPP}/main.cpp)

     # Set the bin folder as the DLL search path
     set_target_properties(${PROJECT_NAME} PROPERTIES VS_DEBUGGER_ENVIRONMENT "PATH=%PATH%;${CMAKE_BINARY_DIR}/bin")
     set_target_properties(${PROJECT_NAME} PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_BINARY_DIR}")
 endif()

# Set the language for the target
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)

# Copy resource files to build directory
file(COPY ${CMAKE_SOURCE_DIR}/res DESTINATION ${CMAKE_BINARY_DIR})

# Add CPack configuration
set(CPACK_PACKAGE_NAME ${PROJECT_NAME})
set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})
set(CPACK_GENERATOR ZIP)
set(CPACK_PACKAGE_DIRECTORY ${CMAKE_BINARY_DIR}/package)

# Specify the files to be included in the package
install(FILES
    ${SDL2_ROOT_DIR}/bin/SDL2.dll
    ${SDL2_IMAGE_ROOT_DIR}/bin/SDL2_image.dll
    ${SDL2_TTF_ROOT_DIR}/bin/SDL2_ttf.dll
    DESTINATION bin
)
install(DIRECTORY ${CMAKE_SOURCE_DIR}/res/ DESTINATION res)
install(TARGETS ${PROJECT_NAME} DESTINATION bin)

# Include CPack module to enable packaging
include(CPack)

# Custom target for auto packing
add_custom_target(PackU
    COMMENT "Packaging the project"
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target package
    # RUN THE EXECUTABLE
    COMMENT "Running the executable"
    COMMAND ${CMAKE_BINARY_DIR}/package/_CPack_Packages/win64/ZIP/${PROJECT_NAME}-${PROJECT_VERSION}-win64/bin/${PROJECT_NAME}.exe
)