# Name the project
PROJECT(UnitTest)

# ---------------------------------------------------------- Setup build environment
# A warning appeared because minimum version must be
# explicited.
# The warning told me to add this :
cmake_minimum_required(VERSION 2.6)

SET( LIBRARY_OUTPUT_PATH lib )
SET( EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR} )

# ---------------------------------------------------------- Include CppUnit
# Usefull to get CPPUNIT ...
# I would love to find a way to have cppunit
# only required for builds where unit test make sense ...
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake_modules)
FIND_PACKAGE( CPPUNIT REQUIRED )

# ---------------------------------------------------------- Build comstack library
FILE ( 	GLOB_RECURSE ComStackSrc 
		${CMAKE_SOURCE_DIR}/../*.cpp 
)
ADD_LIBRARY( comstack STATIC ${ComStackSrc}	)
include_directories( ${CMAKE_SOURCE_DIR}/.. )

# ---------------------------------------------------------- Build and link
FILE ( 	GLOB_RECURSE TestcaseSrc 
		${CMAKE_SOURCE_DIR}/testcases/*.cpp 
)

ADD_DEFINITIONS( " -DUNITTEST" )

add_executable( test-run ${TestcaseSrc} )
target_link_libraries( test-run comstack cppunit )
