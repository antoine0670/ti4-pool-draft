set(HEADER_LIST "${TI4_RandomDraft_SOURCE_DIR}/libs/nlohmann/json.hpp")


add_executable(ti4_random randomizer.cpp)

target_link_libraries(ti4_random PRIVATE "-lstdc++fs")

target_include_directories(ti4_random PUBLIC include)

target_compile_features(ti4_random PUBLIC cxx_std_11)


#source_group(
#	TREE "${PROJECT_SOURCE_DIR}/include"
#	PREFIX "Header Files"
#	FILES ${HEADER_LIST})