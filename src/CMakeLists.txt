add_executable(TI4_PoolDraft main.cpp)

target_sources(TI4_PoolDraft
	PRIVATE
		main.cpp
	)

target_link_libraries(TI4_PoolDraft
	PRIVATE
		stdc++fs
	)

target_include_directories(TI4_PoolDraft
	PRIVATE
		"${CMAKE_SOURCE_DIR}/libs"
	)

target_include_directories(TI4_PoolDraft 
	PUBLIC
    	"${PROJECT_BINARY_DIR}"
    )
         
target_compile_options(TI4_PoolDraft
	PRIVATE
		${GTKMM_CFLAGS_OTHER}
	)                