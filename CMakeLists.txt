cmake_minimum_required(VERSION 2.8)

# Set a variable for commands below
set( PROJECT_NAME  comstacklib )

# Define your Arduino board (below is for Arduino Uno)
set( ${PROJECT_NAME}_BOARD uno )
set( ${PROJECT_NAME}_PORT  /dev/ttyACM0 )

set( ARDUINO_SDK_PATH "/devel/arduino" )
set( ARDUINO_SDK_VERSION 1.0.3 )

set( CMAKE_SOURCE_DIR /devel/git-repos/arduino-cmake )
set( CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/cmake/ArduinoToolchain.cmake)

SET( LIBRARY_OUTPUT_PATH ../../lib )

project( ${PROJECT_NAME} C CXX)

FILE ( GLOB StackSrc *.cpp )

FILE ( GLOB StackHdr *.h )

if (SLIM)
	message( STATUS "Build slim comstack variant" )

    SET(CFLAGS "${CXXFLAGS} -DSLIM_FRAME")
    SET(CXXFLAGS "${CXXFLAGS} -DSLIM_FRAME")

    generate_arduino_library( comstack-slim
        SRCS  ${StackSrc}
        HDRS  ${StackHdr} 
        BOARD uno
    )

else (SLIM)
	message( STATUS "Build fat comstack variant" )

    generate_arduino_library( comstack-fat
        SRCS  ${StackSrc}
        HDRS  ${StackHdr} 
        BOARD uno
    )

endif (SLIM)
  