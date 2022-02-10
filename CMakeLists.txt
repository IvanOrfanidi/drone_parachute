cmake_minimum_required(VERSION 3.5)

project(drone_parachute VERSION 1.0.0)

configure_file(
  project_version.h.in ${CMAKE_CURRENT_BINARY_DIR}/project_version.h
)

add_compile_options(
  -std=c++17

  -Werror
  -Wall
  -Wextra
  -Wpedantic
)

file(GLOB_RECURSE SOURCES
  src/*.cpp
)

set(BOOST_COMPONENTS
  program_options
  system
  filesystem
)
find_package(Boost COMPONENTS ${BOOST_COMPONENTS} REQUIRED)
find_package(Threads)

add_executable(${PROJECT_NAME} ${SOURCES})


target_include_directories(${PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(${PROJECT_NAME}
  stdc++fs
  ${Boost_LIBRARIES}
  ${CMAKE_THREAD_LIBS_INIT}
)