find_package(Magnum REQUIRED
    SceneGraph
    Sdl2Application)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CORRADE_CXX_FLAGS}")
include_directories(
    )

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

include_directories( 
    ${Boost_INCLUDE_DIRS}
    ${PYTHON_INCLUDE_DIRS}
    ${MAGNUM_INCLUDE_DIRS} 
    ${MAGNUM_APPLICATION_INCLUDE_DIRS}
    ./headers
    )

add_executable(GameEngineTest WIN32 ./main.cc )

target_compile_features(GameEngineTest PRIVATE cxx_range_for)

target_link_libraries(GameEngineTest 
    ${CMAKE_THREAD_LIBS_INIT}
    ${Boost_LIBRARIES}
    ${PYTHON_LIBRARIES}
    ${MAGNUM_LIBRARIES}
    ${MAGNUM_SCENEGRAPH_LIBRARIES}
    ${MAGNUM_APPLICATION_LIBRARIES}
    /home/nikulaj/projects/GameEngine/build/lib/libGameEngine.so
    )

add_library( GameEngine SHARED ${HDRS} ${SRCS} )

target_link_libraries(GameEngine 
    ${CMAKE_THREAD_LIBS_INIT}
    ${Boost_LIBRARIES}
    ${PYTHON_LIBRARIES}
    ${MAGNUM_LIBRARIES}
    ${MAGNUM_SCENEGRAPH_LIBRARIES}
    ${MAGNUM_APPLICATION_LIBRARIES}
    )

target_compile_features(GameEngine PRIVATE cxx_range_for)



# Export compile commands for vim's YCM
set( CMAKE_EXPORT_COMPILE_COMMANDS 1 )
