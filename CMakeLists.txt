cmake_minimum_required(VERSION 3.15)

project(TI4_RandomDraft
		VERSION 0.0
		DESCRIPTION "A TI4 random pool draft generation tool"
		LANGUAGES CXX)

if(CMAKE_PROJECT_NAME STREQUAL TI4_RandomDraft)
	set(CMAKE_CXX_STANDARD 11)
	set(CMAKE_CXX_STANDARD_REQUIRED True)

	set(CMAKE_CXX_EXTENSIONS OFF)

	set_property(GLOBAL PROPERTY USE_FOLDERS ON)

	# include(Ctest)

	find_package(Doxygen)
  	if(Doxygen_FOUND)
    	add_subdirectory(docs)
  	else()
    	message(STATUS "Doxygen not found, not building docs")
  	endif()
endif()

include(FetchContent)
if(${CMAKE_VERSION} VERSION_LESS 3.14)
  include(cmake/add_FetchContent_MakeAvailable.cmake)
endif()

add_subdirectory(src)