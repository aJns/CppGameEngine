cmake_minimum_required(VERSION 2.6)

project( GameEngine )

if(UNIX)
    if(EXISTS "/usr/local/lib/OGRE/cmake")

        set(CMAKE_MODULE_PATH "/usr/local/lib/OGRE/cmake/;${CMAKE_MODULE_PATH}")
        set(OGRE_SAMPLES_INCLUDEPATH "/usr/local/share/OGRE/samples/Common/include/") # We could just *assume* that developers uses this basepath : /usr/local

    elseif(EXISTS "/usr/lib/OGRE/cmake")

        set(CMAKE_MODULE_PATH "/usr/lib/OGRE/cmake/;${CMAKE_MODULE_PATH}")
        set(OGRE_SAMPLES_INCLUDEPATH "/usr/share/OGRE/samples/Common/include/") # Otherwise, this one

    else ()
        message(SEND_ERROR "Failed to find module path.")
    endif(EXISTS "/usr/local/lib/OGRE/cmake")
endif(UNIX)

if (CMAKE_BUILD_TYPE STREQUAL "")
    # CMake defaults to leaving CMAKE_BUILD_TYPE empty. This screws up
    # differentiation between debug and release builds.
    set(CMAKE_BUILD_TYPE "RelWithDebInfo" CACHE STRING "Choose the type of build, options are: None (CMAKE_CXX_FLAGS or CMAKE_C_FLAGS used) Debug Release RelWithDebInfo MinSizeRel." FORCE)
endif ()

set(CMAKE_DEBUG_POSTFIX "_d")

set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_BINARY_DIR}/dist")

# Find required packages
find_package(OGRE REQUIRED)

find_package(OIS REQUIRED)

find_package (Threads)

find_package(PythonLibs REQUIRED)

find_package(Boost COMPONENTS ${OGRE_BOOST_COMPONENTS} python3)

set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/dist/bin )
set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib )
set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib )

# Set source files
file(GLOB HDRS
    "./headers/*"
    )

file(GLOB SRCS
    "./source/*"
    )

include_directories( ${OIS_INCLUDE_DIRS}
    ${OGRE_INCLUDE_DIRS}
    ${OGRE_SAMPLES_INCLUDEPATH}
    ${OGRE_Overlay_INCLUDE_DIRS}
    ${Boost_INCLUDE_DIRS}
    ${PYTHON_INCLUDE_DIRS}
    ./headers
    )

add_executable(GameEngineTest WIN32 ./main.cc )

target_compile_features(GameEngineTest PRIVATE cxx_range_for)

target_link_libraries(GameEngineTest 
    ${OGRE_LIBRARIES} 
    ${OIS_LIBRARIES} 
    ${OGRE_Overlay_LIBRARIES}
    ${CMAKE_THREAD_LIBS_INIT}
    ${Boost_LIBRARIES}
    ${PYTHON_LIBRARIES}
    /home/nikulaj/projects/GameEngine/build/lib/libGameEngine.so
    )

add_library( GameEngine SHARED ${HDRS} ${SRCS} )

target_link_libraries(GameEngine 
    ${OGRE_LIBRARIES} 
    ${OIS_LIBRARIES} 
    ${OGRE_Overlay_LIBRARIES}
    ${CMAKE_THREAD_LIBS_INIT}
    ${Boost_LIBRARIES}
    ${PYTHON_LIBRARIES}
    )

target_compile_features(GameEngine PRIVATE cxx_range_for)

if(UNIX)
    install(DIRECTORY ${CMAKE_SOURCE_DIR}/dist/media
        DESTINATION ./
        CONFIGURATIONS ALL
        )

    install(FILES ${CMAKE_SOURCE_DIR}/dist/bin/plugins.cfg
        ${CMAKE_SOURCE_DIR}/dist/bin/resources.cfg
        DESTINATION bin
        CONFIGURATIONS ALL
        )

endif(UNIX)


# Export compile commands for vim's YCM
set( CMAKE_EXPORT_COMPILE_COMMANDS 1 )
