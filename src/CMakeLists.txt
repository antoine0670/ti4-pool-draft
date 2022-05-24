add_executable(pool_draft main.cpp)

target_link_libraries(pool_draft
	PRIVATE
		"-lstdc++fs"
	)

target_include_directories(pool_draft
	PRIVATE
		"${CMAKE_SOURCE_DIR}/libs"
	)