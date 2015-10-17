find_package(Magnum REQUIRED
    MeshTools
    Shaders
    SceneGraph
    Sdl2Application)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CORRADE_CXX_FLAGS}")

find_package (Threads)

find_package(PythonLibs REQUIRED)

find_package(Boost COMPONENTS python3)

include_directories( 
    ${Boost_INCLUDE_DIRS}
    ${PYTHON_INCLUDE_DIRS}
    ${MAGNUM_INCLUDE_DIRS} 
    ${MAGNUM_APPLICATION_INCLUDE_DIRS}
    ${CMAKE_CURRENT_BINARY_DIR}
    ./      # So python interface can find it.
    )

set( LINKED_LIBS 
    ${CMAKE_THREAD_LIBS_INIT}
    ${Boost_LIBRARIES}
    ${PYTHON_LIBRARIES}
    ${MAGNUM_LIBRARIES}
    ${MAGNUM_MESHTOOLS_LIBRARIES}
    ${MAGNUM_SHADERS_LIBRARIES}
    ${MAGNUM_SCENEGRAPH_LIBRARIES}
    ${MAGNUM_APPLICATION_LIBRARIES}
    )

set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin )
set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib )
set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib )

# Set source files
file(GLOB HDRS
    "./*"
    )

file(GLOB SRCS
    "./*"
    )

add_executable(GameEngineTest WIN32 ${HDRS} ${SRCS})

target_compile_features(GameEngineTest PRIVATE cxx_range_for)

target_link_libraries(GameEngineTest 
    ${LINKED_LIBS}
    )

add_library( GameEngine SHARED
    ./python/PythonInterface.hh
    ./python/PythonInterface.cc )

target_link_libraries(GameEngine 
    ${LINKED_LIBS}
    )

target_compile_features(GameEngine PRIVATE cxx_range_for)

# set_target_properties(${LIBRARY_NAME} PROPERTIES POSITION_INDEPENDENT_CODE ON)


# Export compile commands for vim's YCM
set( CMAKE_EXPORT_COMPILE_COMMANDS 1 )
