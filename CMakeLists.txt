cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

project(PoolDraft LANGUAGES CXX VERSION 0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Release)

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS "-Wno-unknown-pragmas")
set(CMAKE_CXX_FLAGS "-g -O3")

include(GNUInstallDirs)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR})

set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${PROJECT_SOURCE_DIR}/cmake")

option(RUN_TESTS "Enable tests" OFF)
option(LINT_CODE "Code linting" OFF)
option(GEN_DOC "Generate documentation" OFF)

configure_file(PoolDraftConfig.h.in PoolDraftConfig.h)

include(FindCPPUNIT)

if (LINT_CODE)
	set(CMAKE_CXX_CLANG_TIDY clang-tidy -checks=,readability-*,modernize-*,performance-*,cppcoreguidelines-* -use-color -header-filter=.h)
endif()

if (GEN_DOC)
	find_package(Doxygen)
	if(Doxygen_FOUND)
		add_subdirectory(docs)
	else()
		message(STATUS "Doxygen not found, not building docs")
	endif()
endif()

# defines targets and sources
add_subdirectory(src)

# enable testing and define tests
if (RUN_TESTS)
	if (CPPUNIT_FOUND)
		enable_testing()
		add_subdirectory(tests)
	else()
		message(STATUS "CppUnit not found, not building tests")
	endif()
endif()